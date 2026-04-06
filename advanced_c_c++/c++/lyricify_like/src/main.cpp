#include <LayerShellQt/Window>
#include <QApplication>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug> // 引入 QDebug 用于排错
#include <QLabel>
#include <QRegularExpression>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class LyricWidget : public QWidget {
  Q_OBJECT

public:
  explicit LyricWidget(QWidget *parent = nullptr) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(800, 140);
    winId();

    if (LayerShellQt::Window *lsWindow =
            LayerShellQt::Window::get(windowHandle())) {
      lsWindow->setLayer(LayerShellQt::Window::LayerTop);
      lsWindow->setAnchors(LayerShellQt::Window::AnchorBottom);
      lsWindow->setMargins({0, 0, 0, 60});
      lsWindow->setKeyboardInteractivity(
          LayerShellQt::Window::KeyboardInteractivityNone);
    }

    QWidget *bgWidget = new QWidget(this);
    bgWidget->setStyleSheet(
        "background-color: rgba(20, 20, 20, 180); border-radius: 20px;");
    QVBoxLayout *bgLayout = new QVBoxLayout(bgWidget);
    bgLayout->setSpacing(5);
    bgLayout->setContentsMargins(20, 15, 20, 15);

    m_currentLabel = new QLabel("搜索播放器中...", this);
    m_currentLabel->setStyleSheet(
        "color: white; font-size: 32px; font-weight: bold;");
    m_currentLabel->setAlignment(Qt::AlignCenter);

    m_nextLabel = new QLabel("灵动词岛 v3.0 (Waylrc 模式)", this);
    m_nextLabel->setStyleSheet(
        "color: rgba(255, 255, 255, 100); font-size: 20px;");
    m_nextLabel->setAlignment(Qt::AlignCenter);

    bgLayout->addWidget(m_currentLabel);
    bgLayout->addWidget(m_nextLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(bgWidget);

    // 暴力轮询：每 50 毫秒执行一次完整的数据抓取和渲染
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LyricWidget::forceSync);
    timer->start(50);
  }

private:
  QLabel *m_currentLabel;
  QLabel *m_nextLabel;
  QString m_activePlayer;

  void forceSync() {
    // 1. 寻找玩家
    if (!isPlayerValid(m_activePlayer)) {
      m_activePlayer = findFirstPlayer();
      if (m_activePlayer.isEmpty()) {
        updateUI("无音乐播放", "");
        return;
      }
    }

    // 2. 建立连接
    QDBusInterface player(m_activePlayer, "/org/mpris/MediaPlayer2",
                          "org.mpris.MediaPlayer2.Player",
                          QDBusConnection::sessionBus());
    if (!player.isValid()) {
      m_activePlayer.clear();
      return;
    }

    // 3. 极速获取时间 (微秒转毫秒)
    qint64 currentPosMs = 0;
    QVariant posVar = player.property("Position");
    if (posVar.isValid()) {
      currentPosMs = posVar.toLongLong() / 1000;
    } else {
      // 如果拿不到时间，说明这个播放器废了，强制换一个
      m_activePlayer.clear();
      return;
    }

    // 4. 获取 Metadata 并进行暴力解包
    QDBusMessage reply =
        player.call("Get", "org.mpris.MediaPlayer2.Player", "Metadata");
    if (reply.type() == QDBusMessage::ReplyMessage &&
        reply.arguments().count() > 0) {
      QVariant variant =
          qvariant_cast<QDBusVariant>(reply.arguments().at(0)).variant();
      processRawData(variant, currentPosMs);
    }
  }

  bool isPlayerValid(const QString &serviceName) {
    if (serviceName.isEmpty())
      return false;
    return QDBusConnection::sessionBus().interface()->isServiceRegistered(
        serviceName);
  }

  // 寻找任意一个存活的播放器 (优先找 vutron，找不到就随便抓一个)
  QString findFirstPlayer() {
    QDBusInterface dbus("org.freedesktop.DBus", "/org/freedesktop/DBus",
                        "org.freedesktop.DBus", QDBusConnection::sessionBus());
    QDBusReply<QStringList> reply = dbus.call("ListNames");
    if (reply.isValid()) {
      QString fallback = "";
      for (const QString &name : reply.value()) {
        if (name.startsWith("org.mpris.MediaPlayer2.")) {
          if (name.contains("vutron", Qt::CaseInsensitive)) {
            return name; // 优先返回 vutron
          }
          fallback = name;
        }
      }
      return fallback;
    }
    return QString();
  }

  void processRawData(const QVariant &metadataVar, qint64 currentPosMs) {
    QVariantMap map;
    if (metadataVar.canConvert<QDBusArgument>()) {
      metadataVar.value<QDBusArgument>() >> map;
    } else if (metadataVar.canConvert<QVariantMap>()) {
      map = metadataVar.value<QVariantMap>();
    }

    // 暴力查找歌词字段
    QString lrcText;
    if (map.contains("lyric"))
      lrcText = map.value("lyric").toString();
    else if (map.contains("lyrics"))
      lrcText = map.value("lyrics").toString();
    else if (map.contains("mpris:lyrics"))
      lrcText = map.value("mpris:lyrics").toString();
    else if (map.contains("xesam:lyrics"))
      lrcText = map.value("xesam:lyrics").toString();

    if (lrcText.isEmpty()) {
      QString title = map.value("xesam:title").toString();
      updateUI(title, "此歌曲未提供内置滚动歌词");
      return;
    }

    // 实时解析出当前句和下一句
    extractAndShowLyric(lrcText, currentPosMs);
  }

  // 每一帧都重新解析一次，这是最稳妥的无状态做法
  void extractAndShowLyric(const QString &lrcRaw, qint64 currentPosMs) {
    QRegularExpression re("\\[(\\d{2,3}):(\\d{2})\\.(\\d{2,3})\\](.*)");
    QRegularExpressionMatchIterator i = re.globalMatch(lrcRaw);

    QString currentLyric = "";
    QString nextLyric = "";
    qint64 lastMatchedTime = -1;

    // 暴力遍历所有行，找到最后一行时间小于等于当前时间的
    while (i.hasNext()) {
      QRegularExpressionMatch match = i.next();
      int min = match.captured(1).toInt();
      int sec = match.captured(2).toInt();
      int ms = match.captured(3).toInt();
      if (match.captured(3).length() == 2)
        ms *= 10;

      qint64 lineTimeMs = min * 60000 + sec * 1000 + ms;
      QString text = match.captured(4).trimmed();

      if (text.isEmpty())
        continue;

      if (lineTimeMs <= currentPosMs) {
        // 这个时间还没过，更新当前高亮的歌词
        currentLyric = text;
        lastMatchedTime = lineTimeMs;
      } else {
        // 一旦遇到大于当前时间的行，这就是下一句！找完收工。
        nextLyric = text;
        break;
      }
    }

    // 如果找不到当前句（比如在前奏），就显示默认信息
    if (currentLyric.isEmpty()) {
      currentLyric = "♪♪♪";
      // 尝试提取第一句歌词作为预告
      QRegularExpressionMatch firstMatch = re.match(lrcRaw);
      if (firstMatch.hasMatch()) {
        nextLyric = firstMatch.captured(4).trimmed();
      }
    }

    updateUI(currentLyric, nextLyric);
  }

  void updateUI(const QString &current, const QString &next) {
    // 为了防止不必要的 UI 刷新导致闪烁，仅在内容变化时才 setText
    if (m_currentLabel->text() != current) {
      m_currentLabel->setText(current);
    }
    if (m_nextLabel->text() != next) {
      m_nextLabel->setText(next);
    }
  }
};

int main(int argc, char *argv[]) {
  qputenv("QT_QPA_PLATFORM", "wayland");
  QApplication app(argc, argv);
  qRegisterMetaType<QVariantMap>();
  LyricWidget widget;
  widget.show();
  return app.exec();
}

#include "main.moc"

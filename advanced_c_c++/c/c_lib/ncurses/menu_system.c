#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

// 定义菜单选项
const char *choices[] = {"1. List Files (ls -al)", "2. Ping Google (3 times)",
                         "3. Show Disk Usage (df -h)", "4. Exit"};
int n_choices = sizeof(choices) / sizeof(char *);

// 打印菜单的辅助函数
void print_menu(WINDOW *menu_win, int highlight) {
  int x = 2, y = 2;
  box(menu_win, 0, 0);                      // 画边框
  mvwprintw(menu_win, 0, 2, " Main Menu "); // 标题

  for (int i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) { /* 高亮当前选中的项 */
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    y++;
  }
  wrefresh(menu_win);
}

// 执行命令并在窗口中显示的函数
void run_command(WINDOW *out_win, const char *cmd) {
  // 1. 清理旧内容
  wclear(out_win);
  box(out_win, 0, 0);
  mvwprintw(out_win, 0, 2, " Output Log ");
  wrefresh(out_win);

  // 2. 使用 popen 打开管道读取命令输出
  FILE *fp = popen(cmd, "r");
  if (fp == NULL) {
    mvwprintw(out_win, 1, 1, "Failed to run command");
    wrefresh(out_win);
    return;
  }

  // 3. 逐行读取输出并打印到 ncurses 窗口
  char path[1024];
  int line = 1;
  while (fgets(path, sizeof(path), fp) != NULL) {
    mvwprintw(out_win, line++, 1, "%s", path);

    // 简单的自动滚动逻辑：如果行数超过窗口高度，重新刷新边框
    // (注：这只是简单演示，严谨的滚动需要用 pads 或 scrollok)
    if (line >= getmaxy(out_win) - 1) {
      line = 1; // 简单覆盖回顶部（实际开发建议用 scrollok）
      wclear(out_win);
      box(out_win, 0, 0);
    }

    wrefresh(out_win); // 实时刷新看到动态效果
    napms(50);         // 稍微停顿一下，让你看清刷新过程（可选）
  }

  pclose(fp);

  mvwprintw(out_win, line, 1, ">> Done. Press any key...");
  wrefresh(out_win);
  wgetch(out_win); // 等待用户看完
}

int main() {
  // --- 初始化 ncurses ---
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0); // 隐藏光标

  // --- 获取屏幕尺寸 ---
  int height, width;
  getmaxyx(stdscr, height, width);

  // --- 创建两个窗口 ---
  // 菜单窗口：占左边一半
  WINDOW *menu_win = newwin(height, width / 2, 0, 0);
  keypad(menu_win, TRUE); // 允许在这个窗口捕获方向键

  // 输出窗口：占右边一半
  WINDOW *output_win = newwin(height, width / 2, 0, width / 2);

  // 初始化显示
  refresh();
  int highlight = 1;
  int choice = 0;
  int c;

  // --- 主循环 ---
  while (1) {
    print_menu(menu_win, highlight);

    // 绘制输出窗口的空边框作为占位
    box(output_win, 0, 0);
    mvwprintw(output_win, 0, 2, " Output Log ");
    wrefresh(output_win);

    c = wgetch(menu_win); // 等待输入

    switch (c) {
    case KEY_UP:
      if (highlight == 1)
        highlight = n_choices;
      else
        --highlight;
      break;
    case KEY_DOWN:
      if (highlight == n_choices)
        highlight = 1;
      else
        ++highlight;
      break;
    case 10: // Enter 键
      choice = highlight;
      break;
    default:
      break;
    }

    // 处理用户的选择
    if (choice != 0) {
      if (choice == 4)
        break; // 退出

      // 根据选择执行不同命令
      switch (choice) {
      case 1:
        run_command(output_win, "ls -al --color=never");
        break;
      case 2:
        run_command(output_win, "ping -c 3 google.com");
        break;
      case 3:
        run_command(output_win, "df -h");
        break;
      }

      // 执行完后重置，继续循环
      choice = 0;
      // 如果执行完命令需要清空输出框，可以在这里调用 wclear(output_win)
    }
  }

  // --- 退出清理 ---
  clrtoeol();
  refresh();
  endwin();
  return 0;
}

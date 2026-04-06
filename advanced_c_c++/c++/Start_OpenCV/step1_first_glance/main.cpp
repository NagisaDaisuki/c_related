#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  // 1. 睁开眼睛：0代表系统默认的第一个摄像头
  cv::VideoCapture cap(0);

  // 如果摄像头没有插好，或者被别的程序占用了，要报错
  if (!cap.isOpened()) {
    std::cerr << "报错：无法打开摄像头！" << std::endl;
    return -1;
  }

  cv::Mat frame; // “魔法数组”，用来装每一帧图片

  // 2. 死循环：疯狂地看
  while (true) {
    cap >> frame; // 核心动作：从摄像头里“抽”一张图片出来塞进 frame 里
    if (frame.empty()) {
      break; // 如果抽出来是空的说明摄像头断开，跳出循环
    }

    // 3. 把这张照片弹出一个窗口显示出来
    cv::imshow("Hello OpenCV - Press 'q' to quit.", frame);

    // 4. 关键保命机制：等30毫秒，这期间键盘按下小写的'q'，就打断死循环
    if (cv::waitKey(50) == 'q') {
      break;
    }
  }

  return 0; // 退出程序时，cap会自动释放摄像头，不需要手动关
}

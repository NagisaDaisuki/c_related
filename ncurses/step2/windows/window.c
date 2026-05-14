#include <ncurses.h>

int main(void) {
  // int ch;
  initscr();            // 初始化 窗口, 开启 curses 模式
  raw();                // 禁止行缓冲
  keypad(stdscr, TRUE); // 开启功能键响应模式
  noecho();             // 当执行 getch() 函数时关闭键盘回显

  WINDOW *win =
      newwin(10, 30, 5, 5); // 创建一个高 10，宽 30，起始坐标(5,5)的窗口
  wprintw(win, "Hi There !!!");
  wrefresh(win);

  getch();
  endwin();
  return 0;
}

#include <ncurses.h>

int main(void) {
  int ch;
  initscr();            // 开始 curses 模式
  raw();                // 禁用行缓冲
  keypad(stdscr, TRUE); // 开启功能键响应模式
  noecho();             // 当执行 getch() 函数时关闭键盘回显
  printw("Type any character to see it in bold\n");
  ch = getch(); // 如果没有调用 raw() 函数，必须按下enter键才可以执行下面的程序

  if (ch == KEY_F(1)) // 如果没有调用 keypad() 初始化，将不会执行这条语句
    printw("F1 Key pressed.");

  else {
    printw("The pressed key is:");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }
  refresh(); // 将缓冲区的内容打印到显示器上
  getch();   // 等待用户输入
  endwin();  // 结束 curses 模式
  return 0;
}

#include <ncurses.h>
#include <locale.h>
#include <string.h>

int main() {
    // 1. CRITICAL: Set locale to support UTF-8/Wide characters
    setlocale(LC_ALL, "");

    // 2. Initialize ncurses
    initscr();              // Start curses mode
    cbreak();               // Disable line buffering (pass input directly)
    noecho();               // Don't echo keystrokes to the screen
    curs_set(0);            // Hide the cursor

    // 3. Get screen dimensions
    int height, width;
    getmaxyx(stdscr, height, width);

    // 4. Draw a box (border) around the screen
    box(stdscr, 0, 0);

    // 5. Prepare Chinese strings
    const char *title = "欢迎使用 (Welcome)";
    const char *msg = "按任意键退出... (Press any key)";

    // 6. Calculate center position (approximate for UTF-8)
    // Note: strlen returns bytes, not visual width. 
    // For perfect centering of Chinese, we usually calculate wide char width,
    // but here we estimate for simplicity.
    int x_title = (width - strlen(title)) / 2; 
    int y_title = height / 2 - 1;

    int x_msg = (width - strlen(msg)) / 2;
    int y_msg = height / 2 + 1;

    // 7. Print text (mvprintw moves cursor then prints)
    // Using bold attribute for the title
    attron(A_BOLD);
    mvprintw(y_title, x_title, "%s", title);
    attroff(A_BOLD);

    mvprintw(y_msg, x_msg, "%s", msg);

    // 8. Refresh screen to show changes
    refresh();

    // 9. Wait for user input
    getch();

    // 10. Clean up
    endwin();

    return 0;
}

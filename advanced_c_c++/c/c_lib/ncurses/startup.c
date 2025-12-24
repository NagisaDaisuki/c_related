#define _XOPEN_SOURCE 600
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

// Helper function to print centered text
void print_centered(int row, const char* text) {
    // Convert multibyte string to wide string to calculate display width
    // 1. Get the required size
    size_t len = mbstowcs(NULL, text, 0);
    if (len == (size_t)-1) return; // Invalid string

    // 2. Allocate memory for wide string
    wchar_t *wtext = malloc((len + 1) * sizeof(wchar_t));
    if (!wtext) return;

    // 3. Convert
    mbstowcs(wtext, text, len + 1);

    // 4. Calculate display width using wcswidth
    int width = wcswidth(wtext, len);
    
    // 5. Clean up
    free(wtext);

    if (width < 0) return; // Error in width calculation

    // Get screen dimensions
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Print at centered position
    mvprintw(row, (cols - width) / 2, "%s", text);
}

int main() {
    // Set locale to support UTF-8 (Chinese characters)
    setlocale(LC_ALL, "");

    // Initialize ncurses
    initscr();
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    keypad(stdscr, TRUE);   // Enable special keys (F1, arrows, etc.)
    curs_set(0);            // Hide the cursor

    // Enable mouse events: report all mouse events including position
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    int rows, cols;
    getmaxyx(stdscr, rows, cols); // Get screen dimensions

    // Use the helper function to print centered text automatically
    print_centered(rows / 2 - 1, "欢迎使用ncurses库文件");
    print_centered(rows / 2 + 1, "点击任意区域继续");

    refresh();

    // Event loop
    int ch;
    MEVENT event;
    while((ch = getch()) != ERR) {
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                // Mouse event detected (click, press, etc.)
                break;
            }
        } else {
            // Any keyboard key pressed
            break;
        }
    }

    // Clean up and exit
    endwin();
    return 0;
}
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    // 1. Must set the locale, otherwise wide characters won't output correctly
    setlocale(LC_ALL, "");

    // 2. Define a wide character (single Chinese character)
    wchar_t ch = L'中';

    // 3. Define a wide string
    wchar_t *str = L"你好，世界 (Hello World)";

    // 4. Use wprintf to print
    wprintf(L"Single char: %lc\n", ch);
    wprintf(L"Wide string: %ls\n", str);

    // 5. Check size
    wprintf(L"Size of wchar_t: %zu bytes\n", sizeof(wchar_t));

    return 0;
}

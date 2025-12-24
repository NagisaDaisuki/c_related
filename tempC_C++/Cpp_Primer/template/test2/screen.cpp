#include "screen.h"
#include <iostream>

int main()
{
    Screen<5,5> scr('c');
    Screen<5,5> scr2;

    // output src to the screen
    std::cout << scr;
    // input contents to the src
    std::cin >> scr2;
    // test input
    std::cout << scr2;

    return 0;
}
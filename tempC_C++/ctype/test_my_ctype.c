#include <stdio.h>
#include "my_ctype.h"

void test_char(int c) {
    printf("--- Testing character: '%c' (ASCII: %d) ---\n", c, c);
    printf("my_isspace:   %d\n", my_isspace(c));
    printf("my_isdigit:   %d\n", my_isdigit(c));
    printf("my_islower:   %d\n", my_islower(c));
    printf("my_isupper:   %d\n", my_isupper(c));
    printf("my_isalpha:   %d\n", my_isalpha(c));
    printf("my_isalnum:   %d\n", my_isalnum(c));
    printf("my_isxdigit:  %d\n", my_isxdigit(c));
    printf("my_iscntrl:   %d\n", my_iscntrl(c));
    printf("my_ispunct:   %d\n", my_ispunct(c));
    printf("my_isgraph:   %d\n", my_isgraph(c));
    printf("my_isprint:   %d\n", my_isprint(c));
    printf("my_tolower:   '%c'\n", my_tolower(c));
    printf("my_toupper:   '%c'\n", my_toupper(c));
    printf("\n");
}

int main() {
    test_char(' ');
    test_char('\n');
    test_char('7');
    test_char('a');
    test_char('Z');
    test_char('f');
    test_char('F');
    test_char('!');
    test_char('\t');
    test_char(127);

    return 0;
}

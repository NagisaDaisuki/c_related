#include "my_ctype.h"

int my_isspace(int c)
{
    return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

int my_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int my_islower(int c)
{
    return (c >= 'a' && c <= 'z');
}

int my_isupper(int c)
{
    return (c >= 'A' && c <= 'Z');
}

int my_isalpha(int c)
{
    return (my_islower(c) || my_isupper(c));
}

int my_isalnum(int c)
{
    return (my_isalpha(c) || my_isdigit(c));
}

int my_isxdigit(int c)
{
    return (my_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

int my_iscntrl(int c)
{
    return ((c >= 0 && c <= 31) || c == 127);
}

int my_isgraph(int c)
{
    return (c >= 33 && c <= 126);
}

int my_ispunct(int c)
{
    return (my_isgraph(c) && !my_isalnum(c));
}

int my_isprint(int c)
{
    return (my_isgraph(c) || c == ' ');
}

int my_tolower(int c)
{
    if (my_isupper(c))
    {
        return c + ('a' - 'A');
    }
    return c;
}

int my_toupper(int c)
{
    if (my_islower(c))
    {
        return c - ('a' - 'A');
    }
    return c;
}
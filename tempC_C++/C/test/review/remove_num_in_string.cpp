#include <cstdlib>
#include <iostream>

void deletedigit(char *p);
int my_is_alpha(char c);

int main(void) {
  char s[30];
  std::cin >> s;
  deletedigit(s);
  std::cout << s;
  return EXIT_SUCCESS;
}

int my_is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
void deletedigit(char *p) {
  char *ptr_slow, *ptr_fast;
  ptr_slow = ptr_fast = p;

  while (*ptr_fast != '\0') {
    if (my_is_alpha(*ptr_fast)) {
      *ptr_slow = *ptr_fast;
      ptr_slow++;
    }
    ptr_fast++;
  }
  *ptr_slow = '\0';
}

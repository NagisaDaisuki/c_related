#include "calc.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void goodbye(void) { printf("\nExiting Calculator... Goodbye!\n"); }

void handle_sigint(int sig) {
  (void)sig;
  keep_running = 0;
}

int main(void) {
  if (atexit(goodbye) != 0)
    return 1;
  // signal(SIGINT, handle_sigint);
  // use sigaction instead of signal to handle interrupt to jump out scanf
  // while executing scanf and function keeps hang on with sleep
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = handle_sigint;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("sigaction");
    return 1;
  }

  printf("Interactive Calculator Started.\nPress Ctrl+C to exit.\n\n");

  double num1, num2, result;
  char op;

  while (keep_running) {
    printf("> ");
    fflush(stdout);
    int items_read = scanf("%lf %c %lf", &num1, &op, &num2);

    if (items_read == EOF && errno == EINTR)
      break;
    if (!keep_running)
      break;
    if (items_read != 3) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      if (c == EOF)
        break;
      printf("Invalid input format. Try: 10 + 20\n");
      continue;
    }
    switch (op) {
    case '+':
      result = add(num1, num2);
      break;
    case '-':
      result = sub(num1, num2);
      break;
    case '*':
      result = mul(num1, num2);
      break;
    case '/':
      result = div_op(num1, num2);
      break;
    default:
      printf("Unknown operator: %c\n", op);
      continue;
    }
    printf("%.2f\n", result);
  }
  return 0;
}

/*
 *  C11标准 引入的一个类型C++中的函数重载或模板功能的特性（原理完全不同）
 *  _Genercic 核心原理
 *
 *  简单来说，_Generic 就像是一个 “编译时的 switch-case 语句”，
 *  但它判断的不是值，而是 类型。
 *  它根据传入表达式的类型，在编译阶段将代码替换为对应的结果（通常是函数名）。
 *
 *  _Gereric(控制表达式,
 *    类型1: 结果1,
 *    类型2: 结果2,
 *    default: 默认结果
 *  )
 *
 *  C语言底层依然不支持两个同名函数。
 *  _Generic 的魔法在于：通过宏(Macro)包裹_Generic，将统一的调用映射到不同的
 *  底层函数上。
 * */

#include <stdio.h>

// step1: define different underlying function
void print_int(int x) { printf("Integer: %d\n", x); }

void print_double(double x) { printf("Double: %lf\n", x); }

void print_string(const char *x) { printf("String: %s\n", x); }

// step2: define the _Generic selector Macro
#define print(X)                                                               \
  _Generic((X),                                                                \
      int: print_int,                                                          \
      double: print_double,                                                    \
      const char *: print_string,                                              \
      char *: print_string,                                                    \
      default: print_int)(X)

// step3: use overload function
int main(void) {
  print(42);
  print(3.14);
  print("Hello");
  return 0;
}

#include <cctype>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 辅助函数：定义运算符的优先级
// 优先级越高，数字越大。乘除优先于加减。
int getPriority(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0; // '(' 压在栈底时，优先级最低，保护栈内的其他元素不被轻易弹走
}

int main() {
  string infix;
  // OJ 常见套路：读取输入直到结束
  if (cin >> infix) {
    stack<char> opStack; // 专门用来存放操作符和括号的栈
    string postfix = ""; // 用来存放最终输出的逆波兰式

    for (char ch : infix) {
      // 规则 1：如果是字母（操作数），直接无脑输出
      if (isalpha(ch)) {
        postfix += ch;
      }
      // 规则 2：如果是左括号，直接压栈，开启一个"结界"
      else if (ch == '(') {
        opStack.push(ch);
      }
      // 规则 3：如果是右括号，疯狂弹栈，直到把对应的左括号炸出来
      else if (ch == ')') {
        while (!opStack.empty() && opStack.top() != '(') {
          postfix += opStack.top();
          opStack.pop();
        }
        // 把那个作为结界的左括号也弹掉，但不要放进输出里
        if (!opStack.empty() && opStack.top() == '(') {
          opStack.pop();
        }
      }
      // 规则 4：如果是运算符（+ - * /），准备进栈进行"权利斗争"
      else {
        // 核心法则：如果栈顶的老大比新来的你“强”或“一样强”（优先级 >=），
        // 老大就得先出栈去干活。直到栈顶的人比你弱，你才能安稳坐上去。
        while (!opStack.empty() &&
               getPriority(opStack.top()) >= getPriority(ch)) {
          postfix += opStack.top();
          opStack.pop();
        }
        opStack.push(ch); // 斗争结束，新操作符进栈
      }
    }

    // 规则 5：字符串扫描完了，把栈里剩下的所有老弱病残操作符全赶出来
    while (!opStack.empty()) {
      postfix += opStack.top();
      opStack.pop();
    }

    // 打印最终结果
    cout << postfix << endl;
  }

  return 0;
}

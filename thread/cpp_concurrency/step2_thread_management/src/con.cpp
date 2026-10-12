#include "con.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
// #include <vector>

namespace detach_test {
// 用来模拟每个文档的编辑状态
std::atomic<bool> is_editing{true};

// 模拟获取文件名
std::string get_filename_from_user() {
  static int doc_count = 1;
  return "Document_" + std::to_string(doc_count++) + ".txt";
}

// 模拟真正的编辑逻辑
void open_document_and_display_gui(const std::string &filename) {
  std::cout << "[线程 " << std::this_thread::get_id() << "] 正在打开文档："
            << filename << std::endl;
  // 模拟 GUI 初始化耗时
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// 模拟检查用户是否完成编辑
bool done_editing() {
  // 演示，每次调用都返回 false，让线程一直循环；
  // 实际开发中会检查用户是否点击了关闭或保存
  return false;
}

UserCommand get_user_input() {
  // 模拟用户不断打开新文档
  return {UserCommand::OPEN_NEW, ""};
}

// 模拟处理普通输入
void process_user_input(const UserCommand &cmd) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// 核心函数 edit_document
void edit_document(const std::string &filename) {
  open_document_and_display_gui(filename);

  // 分离线程无法被 join，这里用一个循环模拟持续运行
  // 分离线程绝对不能访问主线程栈上的局部变量
  while (!done_editing()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

} // namespace detach_test

void ns_func::do_something(unsigned int i) { std::cout << " " << i << " \n"; }

void ns_func::do_something_in_child_thread() {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
  std::cout << "[子线程] 任务执行完毕" << std::endl;
}
// 模拟主线程中可能抛出异常的函数
void ns_func::do_something_in_current_thread() {
  std::cout << "[主线程] 开始执行可能抛出异常的任务..." << std::endl;
  // 模拟抛出异常
  throw std::runtime_error("模拟主线程发生严重错误!");
  std::cout << "[主线程]这行代码不会被执行。" << std::endl;
}

void background_task::operator()() const {
  background_task::do_something();
  background_task::do_something_else();
}

void background_task::do_something() const {
  std::cout << "do_something_else" << " " << id << "\n";
}

void background_task::do_something_else() const {
  std::cout << id << " do_something\n";
}

thread_guard::~thread_guard() {
  if (t.joinable()) {
    t.join();
  }
}

void func::operator()() {
  for (unsigned j = 0; j < 10000; ++j) {
    ns_func::do_something(i);
  }
}

void oops() {
  int some_local_state = 0;
  func my_func((some_local_state));
  std::thread my_thread(my_func);
  my_thread.join(); // 不等待线程结束
                    // 新线程可能还在运行
  // my_thread.join();
  // 会更好,保证调用子线程函数的函数不会因为资源释放导致未定义行为
}

void f() {
  int some_local_state = 0;
  func my_func{some_local_state};
  std::thread t{ns_func::do_something_in_child_thread};
  try {
    // 尝试执行主线程的任务，这里会抛出异常
    ns_func::do_something_in_current_thread();

    // 如果没有抛出异常，这里会执行正常 join
    t.join();
  } catch (const std::exception &e) {
    // 捕获到异常，准备提前离开
    if (t.joinable()) {
      t.join();
    }

    // 处理完子线程后，将异常重新抛出，让上层知道出错了
    throw;
  }

  // 正常情况的 join
  if (t.joinable()) {
    t.join();
  }
}

void f_thread_guard() {

  int some_local_state = 0;
  func my_func{some_local_state};
  std::thread t{ns_func::do_something_in_child_thread};
  thread_guard g(t);
  // 用RAII 把创建好的线程对象作为引用绑定，然后在对象析构时自动执行 join
  // try {
  //   // 尝试执行主线程的任务，这里会抛出异常
  //   ns_func::do_something_in_current_thread();

  //   // 如果没有抛出异常，这里会执行正常 join
  //   t.join();
  // } catch (const std::exception &e) {
  //   // 捕获到异常，准备提前离开
  //   if (t.joinable()) {
  //     t.join();
  //   }

  //   // 处理完子线程后，将异常重新抛出，让上层知道出错了
  //   throw;
  // }

  // // 正常情况的 join
  // if (t.joinable()) {
  //   t.join();
  // }
}

void f_detach() {
  std::cout << "[主线程] 编辑器启动。" << std::endl;

  // 模拟主线程的事件循环
  int loop_count = 0;
  while (loop_count < 3) { // 让主线程循环三次
    detach_test::UserCommand cmd = detach_test::get_user_input();

    if (cmd.type == detach_test::UserCommand::OPEN_NEW) {
      std::string new_name = detach_test::get_filename_from_user();

      // 1. 创建新线程，去执行 edit_document
      std::thread t(detach_test::edit_document, new_name);

      // 2. 分离线程
      t.detach();

      // 断言：detach后，t 不再与任何线程关联
      if (!t.joinable()) {
        std::cout << "[主线程] 成功分离线程，继续处理其他任务。" << std::endl;
      }
    } else {
      detach_test::process_user_input(cmd);
    }

    loop_count++;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟主线程的等待
  }
  std::cout << "[主线程] 编辑器主循环结束，准备退出..." << std::endl;

  // 重要提示：如果此时主线程（main）直接
  // return，所有分离的后台线程会被强制杀死。
  // 在真实的生产环境中，你需要某种机制（如全局标志位、条件变量）来通知后台线程安全退出，
  // 或者保证主线程不会早于后台线程退出。
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "程序退出。" << std::endl;
}

// 子线程函数
void transfer_var(int i, const std::string &s) {
  std::cout << i << ": " << s << std::endl;
}

void tv_test(int some_param) {
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  // std::thread t(transfer_var, 3, buffer);
  //  tv_test可能会在char* 像 std::string 隐式类型转换时
  //  结束，从而导致未定义的行为。
  std::thread t(transfer_var, 3, std::string(buffer));
  t.detach();
}

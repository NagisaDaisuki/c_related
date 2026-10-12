#pragma once // 防止头文件被重复包含
#include <string>
#include <thread>
namespace detach_test {

// 模拟获取文件名
std::string get_filename_from_user();

// 模拟真正的编辑逻辑
void open_document_and_display_gui(const std::string &filename);

// 模拟检查用户是否完成编辑
bool done_editing();

// 模拟获取用户输入的命令
struct UserCommand {
  enum Type { OPEN_NEW, TYPE_TEXT, SAVE, EXIT } type;
  std::string data;
};

UserCommand get_user_input();

// 模拟处理普通输入
void process_user_input(const UserCommand &cmd);

// 核心函数 edit_document
void edit_document(const std::string &filename);
} // namespace detach_test

namespace ns_func {
// 声明 do_something do_something_in_current_thread do_something_in_child_thread
void do_something(unsigned int i);
void do_something_in_child_thread();
void do_something_in_current_thread();
} // namespace ns_func

class background_task {
public:
  background_task(int id) : id(id) {}

  void operator()() const;

private:
  int id;
  void do_something() const;
  void do_something_else() const;
};

class thread_guard {
  std::thread &t;

public:
  explicit thread_guard(std::thread &t_) : t(t_) {}
  ~thread_guard();
  thread_guard(thread_guard const &) = delete; // 拷贝构造函数为 delete
  thread_guard &
  operator=(thread_guard const &) = delete; // 拷贝赋值操作为 delete
};

struct func {
  int &i;
  func(int &i_) : i(i_) {}
  void operator()(); // 只声明不写函数体
};

void oops();

void f();

void f_thread_guard();

void f_detach();

void transfer_var(int i, const std::string &s);

void tv_test(int some_param);

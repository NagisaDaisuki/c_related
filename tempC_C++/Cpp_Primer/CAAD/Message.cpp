#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <memory>

/*
    实现电子邮件的分类保存
      -定义两个类分别为Message和Folder
      分别表示电子邮件消息和消息目录

      -每个Message对象可以出现在多个Folder中
      但是，任意给定的Message的内容只有一个副本

      -如果一条Message的内容被改变，则我们从它所在的任何Folder
      来浏览此Message时，都会看到改变后的结果
      （只要Message的位置变动或值改变）
                                    
      -------------
      |           |
      |  Message  | 消息文本
  --- |           |<-|
  |   -------------  |
  |   -------------  |           
  |-->|           |---
      |  Folder   |
   |->|           |----
   |  -------------   |
   |                  |
   |                  |
   |  -------------   |
   |  |           |<--- 
   |  |  Message  |
   ---|           | 消息文本
      -------------
      

*/
/*
    Message类提供Save和Remove操作
    来向一个给定的Folder 添加一条Message或是从中删除一条Message
    
    创建操作：指明消息内容，但是不会指出Folder,为了将一条Message放到一个特定Folder
    中，必须调用Save

    销毁操作：销毁Message以及所有指向Message的folder指针

    拷贝操作：副本和原对象是不同的Message对象，但两个Message对象都出现在相同的folder
    中。拷贝操作包括消息内容和Folder指针set的拷贝

    赋值操作：左侧Message对象的内容会被右侧Message对象的内容所替代
    更新Folder集合，原来包含左侧message对象的Folder将Message删除

*/



class Message;

void swap(Message&,Message&);

class Folder
{
    friend class Message;
    friend void swap(Message&,Message&);
public:
  Folder(){}
  Folder(const Folder&);
  Folder& operator=(const Folder&);
  ~Folder(){}
  void addMsg(const Message*);
  void remMsg(const Message*);
  
private:
  std::set<Message*> folders;

};

Folder::Folder(const Folder& f) : folders(f.folders)
{} 

Folder& Folder::operator=(const Folder& rhs)
{
  if(this != &rhs)
  {
    folders = rhs.folders; //set的拷贝赋值运算符
  }
  return *this;
}

void Folder::addMsg(const Message* m)
{
  if(m)
  {
    folders.insert(m);
  }
}

void Folder::remMsg(const Message* m)
{
  folders.erase(m);
}


class Message
{
  friend class Folder;
  friend void swap(Message&,Message&);
public:
  //folder被隐式初始化为空集合
  explicit Message(const std::string &str = "") : contents(str){}
  //拷贝控制成员，用来管理指向本Message的指针
  Message(const Message&); //拷贝构造函数
  Message& operator=(const Message&); //拷贝赋值运算符
  Message& operator=(Message); //swap重载版本
  ~Message();           //析构函数
  //从给定Folder集合中添加/删除本Message
  void save(Folder&);
  void remove(Folder&);
private:
  std::string contents;         //实际文本消息
  std::set<Folder*> folders;    //包含本Message的folder
  //拷贝构造函数，拷贝赋值运算符和析构函数所使用的工具函数(良构)
  //将本Message添加到指向参数的Folder中
  void add_to_Folders(const Message&);
  //从folders中的每个Folder中删除message
  void remove_from_Folders();
};

//save 和 remove成员
void Message::save(Folder &f)
{
    folders.insert(&f); //将给定的Folder添加到我们的folder列表中
    f.addMsg(this);     //将本Message添加到f的Message集合中
}
109%
void Message::remove(Folder &f)
{
    folders.erase(&f);  //删除
    f.remMsg(this);
}

//Message 类的拷贝控制成员
//将本Message添加到指向m的Folder中
void Message::add_to_Folders(const Message &m)
{
    for(auto f : m.folders)
      f->addMsg(this); //将左侧运算对象添加到m对象的folder中
}

//调用string类和set类的拷贝构造函数
/*
  1.拷贝右侧运算对象Message中的成员到本对象
  2.为本Message对象添加右侧运算对象folders的成员
*/
Message::Message(const Message &m) :
    contents(m.contents),folders(m.folders)
{
    add_to_Folders(m);
}


//Message的析构函数
/*
  当一个Message被销毁时，我们必须从指向此message的folder中删除它
  ，拷贝赋值运算符也要执行此操作
*/

void Message::remove_from_Folders()
{
    for(auto f : this->folders)
      f->remMsg(this); 
}

Message::~Message()
{
    remove_from_Folders();
    //编译器会自动调用set的析构函数释放分配的folder内存
}

Message& Message::operator=(const Message &rhs)
{
    //通过先删除指针再插入它们来处理自赋值情况
    remove_from_Folders(); //更新已有folder
    contents = rhs.contents; //从rhs拷贝消息内容
    folders = rhs.folders; //从rhs拷贝folder指针
    add_to_Folders(rhs);
    return *this;
}

//Message 中的swap函数
void swap(Message& lhs,Message& rhs)
{
    using std::swap; //在本例中严格来说并不需要
    //将每个消息的指针从它(原来)所在的Folder中删除
    for(auto f : lhs.folders)
      f->remMsg(&lhs);
    for(auto f : rhs.folders)
      f->remMsg(&rhs);
    //交换contents和folder指针set
    swap(lhs.contents,rhs.contents); //swap(string&,string&);
    swap(lhs.folders,rhs.folders);  //swap(set&,set&);
    //将每个Message的指针添加到它的Folder中
    for(auto f : lhs.folders)
      f->addMsg(&lhs);
    for(auto f : rhs.folders)
      f->addMsg(&rhs);
      
}
Message& Message::operator=(Message rhs)
{
  swap(*this,rhs);
  return *this;
}

int main(void)
{

    return EXIT_SUCCESS;
}

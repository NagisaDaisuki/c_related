#include "Message.h"
#include <iostream>

void swap(Message &lhs,Message &rhs)
{
    using std::swap;
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();
    
    swap(lhs.folders,rhs.folders);
    swap(lhs.contents,rhs.contents);
    
    lhs.add_to_folders(lhs);
    rhs.add_to_folders(rhs);

}

//Message implementation

void Message::save(Folder &f)
{
    addFldr(&f); //use existing function to avoid duplicate code.
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    remFldr(&f); //use existing function to avoid duplicate code.
    f.remMsg(this);
}

void Message::add_to_folders(const Message &m)
{
    for(auto f : m.folders)
      f->addMsg(this);   
}

Message::Message(const Message &m)
  : contents(m.contents),folders(m.folders)
{
    add_to_folders(m);
}

void Message::remove_from_Folders()
{
    for(auto f : folders)
      f->remMsg(this);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message& rhs)
{
    remove_from_Folders(); //先删除左侧运算对象(this),保证拷贝安全
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs); //add_to_folders函数为rhs的folders中的folder添加本对象
    return *this;    
}

void Message::print_debug()
{
    std::cout << contents << std::endl;
}

// Folder Implememtation

void swap(Folder &lhs,Folder &rhs)
{
    using std::swap;
    lhs.remove_from_Message();
    rhs.remove_from_Message();

    swap(lhs.msgs,rhs.msgs);
    
    lhs.add_to_Message(lhs);
    rhs.add_to_Message(rhs);
    
}

void Folder::add_to_Message(const Folder &f)
{
     for(auto m : msgs)
       m->addFldr(f);
}

Folder::Folder(const Folder &f)
  : msgs(f.msgs)
{
    add_to_Message(f);
}

void Folder::remove_from_Message()
{
    for(auto m : msgs)
      m->remFldr(this);
}
Folder::~Folder()
{
    remove_from_Message();
}

Folder& Folder::operator=(const Folder& rhs)
{
    remove_from_Message();
    msgs = rhs.msgs;
    add_to_Message(rhs);
    return *this;
}

void Folder::print_debug()
{
    for(auto m : msgs)
      std::cout << m->contents << " "; 
    std::cout << std::endl;
}

int main()
{
  return 0;
}




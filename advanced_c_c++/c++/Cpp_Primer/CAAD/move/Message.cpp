#include "Message.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

void Message::add_to_folders(const Message& f)
{
    for(auto f : f.folders)
      f.addMsg(this);
    std::cout << "added message to folders" << std::endl;
}

void Message::remove_from_folders()
{
    for(auto f : this->folders)
      f.remMsg(this);
    std::cout << "removed message from folders" << std::endl;
}

Message::Message(const Message& m)
  : contents(m.contents),folders(m.folders)
{
    add_to_folders(m);
}

Message& Message::operator=(const Message& rhs)
{
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

void Message::move_folders(Message* m)
{
    folders = std::move(m->folders);
    for(auto f : folders)
    {
        f->remMsg(m);
        f->addMsg(this);
    }
    m->folders.clear();
}

Message::Message(Message&& m) : contents(std::move(m.contents))
{
    move_folders(&m);
}

Message& Message::operator=(Message&& rhs)
{
    if(this != rhs) 
    {
        remove_from_folders();
        contents = std::move(rhs.contents);
        move_folders(rhs);
    }
    std::cout << "Message members moved" << std::endl;
    return *this;
}

//folder Implementation

void swap(Folder& lhs,)




int main()
{

    return 0;
}

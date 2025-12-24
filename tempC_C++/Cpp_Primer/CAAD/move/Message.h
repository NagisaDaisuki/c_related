#ifndef _msg
#define _msg

#include <string>
#include <set>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class Folder;

class Message
{
    friend void swap(Message&,Message&);
    friend void swap(Folder&,Folder&);
    friend class Folder;
public:
    explicit Message(const std::string &str= "") : contents(str){}
    Message(const Message&);
    Message& operator=(const Message&);
    Message(Message&&);
    Message& operator=(Message&&);
    ~Message();

private:
    void add_to_folders(const Message&);
    void remove_from_folders();

    void addFldr(Folder& f){ folders.insert(&f); }
    void remFldr(Folder& f){ folders.erase(&f); }

    void move_folders(Message*);
private:
    std::string contents;
    std::set<Folder*> folders;
};

class Folder
{
    friend void swap(Message&,Message&);
    friend void swap(Folder&,Folder&);
    friend class Message;
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    Folder(Folder&&);
    Folder& operator=(Folder&&);
    ~Folder();
private:
    void add_to_message(const Folder&);
    void remove_from_message();
    void addMsg(Message& m){ folders.insert(&m); }
    void remMsg(Message& m){ folders.erase(&m); }
private:
    std::set<Message*> folders;
};

#endif

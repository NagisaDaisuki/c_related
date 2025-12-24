#ifndef PHONE_H
#define PHONE_H

#include <vector>
#include <string>
#include <algorithm> 

class Contact
{
  public:
    Contact(std::string name,std::string number) : 
      name(name),number(number){}
  std::string getName() const { return name; }
  std::string getNumber() const { return number; }

  private:
    std::string name;
    std::string number;
};

class PhoneBook
{
  public:
    // 添加联系人
    void addContact(const Contact& contact);
    // 显示所有联系人
    void displayContacts() const;
    // 根据姓名搜索联系人
    void searchContactByName(const std::string& name) const;
    
  private:
    std::vector<Contact> contacts;
};

#endif

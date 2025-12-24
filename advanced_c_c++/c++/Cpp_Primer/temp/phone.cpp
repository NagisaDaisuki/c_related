#include "phone.h"
#include <iostream>
#include <algorithm>
void PhoneBook::addContact(const Contact& contact)
{
  contacts.push_back(contact);
}

void PhoneBook::displayContacts() const 
{
  std::cout << "Contacts: " << std::endl;
  for(const auto& contact : contacts)
    std::cout << contact.getName() << ": " << contact.getNumber() << "." 
      << std::endl;
}

// 根据姓名搜索联系人
void PhoneBook::searchContactByName(const std::string& name) const 
{
  std::cout << "Search results for: " << name << ": " << std::endl;
  auto found = std::find_if(contacts.begin(),contacts.end(),
            [&name](const Contact& contact){
              return contact.getName() == name;
            });
  if(found != contacts.end())
  {
    std::cout << found->getName() << ": " << found->getNumber() << std::endl; 
  }
  else 
  {
    std::cout << "Contact not found." << std::endl;
  }
}



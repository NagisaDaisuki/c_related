#include <iostream>
#include "phone.h"

int main()
{
  PhoneBook phoneBook;
  
  // 添加几个联系人
  phoneBook.addContact(Contact("Alice","111111"));
  phoneBook.addContact(Contact("Bob","222222"));
  phoneBook.addContact(Contact("Charlie","333333"));

  // 显示所有联系人
  phoneBook.displayContacts();

  // 搜索联系人
  phoneBook.searchContactByName("Bob");

  return 0;
}

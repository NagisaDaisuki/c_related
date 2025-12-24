#include "quote.h"

Quote::Quote(const Quote& q) : bookNo(q.bookNo),price(q.price) {
    std::cout << "Quote copy constructor called" << std::endl;
}

Quote& Quote::operator=(const Quote& rhs)
{
  if(*this != rhs)
  {
    bookNo = rhs.bookNo;
    price = rhs.price;
  }
  std::cout << "Quote copy called" << std::endl;
  return *this;
}

Quote::Quote(Quote&& q) noexcept : bookNo(std::move(q.bookNo)),price(std::move(q.price))
{
  std::cout << "Quote move constructor called" << std::endl;
}

Quote& Quote::operator=(Quote&& rhs) noexcept
{
  if(*this != rhs)
  {
      bookNo = std::move(rhs.bookNo);
      price = std::move(rhs.price);
  }
  std::cout << "Quote move called" << std::endl;
  return *this;
}


void Quote::debug() const
{
    std::cout << "data members of this class:\n"
              << "bookNo= " << this->bookNo << " "
              << "price= " << this->price << " ";
}

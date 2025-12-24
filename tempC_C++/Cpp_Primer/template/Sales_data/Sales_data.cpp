#include "Sales_data.h"

Sales_data::Sales_data(std::istream& is)
{
  is >> *this;
}

double Sales_data::avg_price() const 
{
  if(units_sold)
    return revenue/units_sold;
  else 
    return 0;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
  units_sold += rhs.units_sold;
  revenue += rhs.units_sold;
  return *this;
}

Sales_data 
operator+(const Sales_data &lhs,const Sales_data &rhs)
{
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}

std::istream& operator>>(std::istream& is,Sales_data &item)
{
  double price;
  is >> item.bookNo >> item.units_sold >> price;
  if(is)
    item.revenue = item.units_sold * price;
  item = Sales_data();
  return is;
}

std::ostream& operator<<(std::ostream& os,const Sales_data& item)
{
  os << item.isbn() << " " << item.units_sold << " "
    << item.revenue << " " << item.avg_price();
  return os;
}

std::istream& read(std::istream& is,Sales_data& item)
{
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price; 
  item.revenue = price * item.units_sold;
  return is;
}

std::ostream& print(std::ostream& os,const Sales_data& item)
{
  os << item.isbn() << " " << item.units_sold << 
    " " << item.revenue << " " << item.avg_price();
  return os;
}

Sales_data add(const Sales_data &lhs,const Sales_data &rhs)
{
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}


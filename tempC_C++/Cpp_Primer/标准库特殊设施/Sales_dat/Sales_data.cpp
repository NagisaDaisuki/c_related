#include "Sales_data.h"
#include <iostream>

using std::istream; 
using std::ostream;

Sales_data::Sales_data(std::istream& is)
{
    read(is,*this);
}

double 
Sales_data::avg_price() const 
{
  if(units_sold)
    return revenue / units_sold;
  else 
    return 0;
}

// add the value of the given Sales_data into this object 
Sales_data& 
Sales_data::combine(const Sales_data& rhs)
{
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

// =Sales_data 
Sales_data& Sales_data::operator =(const Sales_data& rhs)
{
  this->bookNo = rhs.bookNo;
  this->revenue = rhs.revenue;
  this->units_sold = rhs.units_sold;
  
  return *this;
}

// =string
Sales_data &Sales_data::operator =(const std::string& rhs)
{
  *this = Sales_data(rhs);
  return *this;
}

Sales_data& Sales_data::operator +=(const Sales_data& rhs)
{
  this->revenue += rhs.revenue;
  this->units_sold += rhs.units_sold;
  
  return *this;
}

Sales_data  
add(const Sales_data& lhs,const Sales_data& rhs)
{
  Sales_data sum = lhs;
  sum.combine(rhs);
  return sum;
}

// transactions contain ISBN,number of copies sold,and sales price 
std::istream& 
read(std::istream& is,Sales_data &item)
{
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;
  return is;
}

std::ostream& 
print(std::ostream& os,const Sales_data& item)
{
  os << item.isbn() << " " << item.units_sold 
    << " " << item.revenue << " " << item.avg_price();
  return os;
}

std::ostream& 
operator <<(std::ostream& os,const Sales_data& item)
{
  os << item.isbn() << " " << item.units_sold << " "
    << item.revenue << " " << item.avg_price();
  return os;
}

std::istream& 
operator >>(std::istream& is,Sales_data& s)
{
  double price;
  is >> s.bookNo >> s.units_sold >> price;
  
  // if successful,write into the object,give the object default state otherwise
  if(is)
    s.revenue = s.units_sold * price;
  else 
    s = Sales_data();
  
  return is;
}





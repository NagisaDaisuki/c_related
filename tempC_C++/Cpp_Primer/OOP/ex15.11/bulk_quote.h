#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "disc_quote.h"

class Bulk_quote : public Disc_quote
{
  public:
    using Disc_quote::Disc_quote; //继承直接基类的构造函数
    //Bulk_quote() = default;
    Bulk_quote(const std::string& b,double p,std::size_t q,double disc) : 
       Disc_quote(b,p,q,disc) {}

    Bulk_quote(const Bulk_quote& b) : Disc_quote(b)
    {
      std::cout << "Bulk_quote copy constructor called" << std::endl;
    }

    double net_price(std::size_t n) const override;
    void debug() const override;
   //private:
   // std::size_t min_qty = 0;
   // double discount = 0.0;
};

#endif

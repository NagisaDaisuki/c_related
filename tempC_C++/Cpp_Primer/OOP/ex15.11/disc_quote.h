#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H

#include "quote.h"

class Disc_quote : public Quote
{
  friend bool operator!=(const Disc_quote& lhs,const Disc_quote& rhs);
  public:
    Disc_quote();
    Disc_quote(const std::string& b,double p,std::size_t q,double d) :
      Quote(b,p),quantity(q),discount(d) {}
    Disc_quote(const Disc_quote& d) : Quote(d),quantity(d.quantity),discount(d.discount)
    {
        std::cout << "Disc_quote copy constructor called" << std::endl;
    }
    Disc_quote& operator=(const Disc_quote& rhs)
    {
      if(*this != rhs)
      {
          Quote::operator=(rhs);
          this->quantity = quantity;
          this->discount = discount;
      }
      std::cout << "Disc_quote copy called" << std::endl;
      return *this;
    }
    Disc_quote(Disc_quote&& q) : Quote(std::move(q)),quantity(std::move(q.quantity)),discount(std::move(q.discount))
    {
      std::cout << "Disc_quote move constructor called" << std::endl;
    }
    Disc_quote& operator=(Disc_quote&& rhs)
    {
      if(*this != rhs)
      {
        Quote::operator=(std::move(rhs));
        this->quantity = std::move(rhs.quantity);
        this->discount = std::move(rhs.discount);
      }
      std::cout << "Disc_quote move called" << std::endl;
      return *this;
    }

    virtual double net_price(std::size_t n) const override = 0;

  protected:
    std::size_t quantity;
    double      discount;
};

bool inline
operator !=(const Disc_quote& lhs,const Disc_quote& rhs)
{
    return  Quote(lhs) != Quote(rhs)
            &&
            lhs.quantity != rhs.quantity
            &&
            lhs.discount != rhs.discount;
}

#endif

#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

class Quote{
    friend bool operator!=(const Quote& lhs,const Quote& rhs);
  public:
    Quote() = default;
    Quote(const std::string& b,double p) : 
      bookNo(b),price(p){}

    Quote(const Quote&);
    Quote& operator=(const Quote&);
    Quote(Quote&&) noexcept;
    Quote& operator=(Quote&&) noexcept;

    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const;

    virtual ~Quote() = default;
  private:
    std::string bookNo;
  protected:
    double price = 0.0;
};

bool inline 
operator !=(const Quote& lhs,const Quote& rhs)
{
    return  lhs.bookNo != rhs.bookNo 
            &&
            lhs.price != rhs.price;
}

#endif

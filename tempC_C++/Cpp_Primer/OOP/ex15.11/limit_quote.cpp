#include "limit_quote.h"

void Limit_quote::debug() const
{
    Quote::debug();
    std::cout << "max_qty= " << this->quantity << " "
              << "discount= " << this->discount << " ";
}

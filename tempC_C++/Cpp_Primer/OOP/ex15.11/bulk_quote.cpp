#include "bulk_quote.h"

double Bulk_quote::net_price(std::size_t n) const
{
    return n * price * (n >= quantity ? 1 - discount : 1);
}

void Bulk_quote::debug() const
{
    //执行特定版本的debug,如果直接调用debug可能会陷入死循环
    Quote::debug(); //作用域运算符
    std::cout << "min_qty= " << this->quantity << " " 
              << "discount= " << this->discount << " ";
}

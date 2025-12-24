#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include "quote.h"
#include "bulk_quote.h"
#include "limit_quote.h"
#include "disc_quote.h"

void print_debug(const Quote& q);

double print_total(std::ostream& os,const Quote& item,size_t n);

int main()
{
    /*Quote q("aaa",10.60);
    Bulk_quote bq("bbb",111,10,0.3);
    Limit_quote lq("ccc",222,10,0.3);
    
    //Not dynamic binding!
    Quote& r = q; //这里已经确定了引用的类型
    r.debug();
    std::cout << "\n";
    r = bq;
    r.debug();
    std::cout << "\n";
    r = lq;
    r.debug();
    std::cout << "\n";
    
    std::cout << "============\n";

    //dynamic binding!
    print_debug(q);
    std::cout << "\n";
    print_debug(lq);
    std::cout << "\n";
    print_debug(bq);
    std::cout << "\n";

    std::vector<Quote> vecQ;
    vecQ.push_back(bq);
    
    int num = 0;
    
    //从控制台读取整数，直到遇到文件结束符或非整数输入为止
    std::cout << "Enter integers (press Ctrl + D on Unix/Linux,Ctrl + Z on Windows to end input):\n";
    //std::copy(std::istream_iterator<int>(std::cin), //
    //          std::istream_iterator<int>(),
    //          std::back_inserter(num));
    std::cin >> num;
    
    std::cout << "you bought " << num << (num > 1 ? " goods." : " good.")
            << "the price is: ";
    double price = vecQ.begin()->net_price(num);
    std::cout << price << '.' << std::endl;
    */

    std::vector<Quote> v;
    for(unsigned i = 0;i != 10;++i)
      v.push_back(Bulk_quote("sss",i * 10.1,10,0.3));

    double total = 0;
    for(const auto& b : v)
      total += b.net_price(20);

    std::cout << total << std::endl;
    
    std::cout << "====" << std::endl;
    
    std::vector<std::shared_ptr<Quote>> pv;
    
    for(unsigned i = 0;i != 10;i++)
      pv.push_back(std::make_shared<Bulk_quote>(Bulk_quote("sss",i * 10.1,10,0.3)));

    double total_p = 0;
    
    for(auto p : pv)
      total_p += p->net_price(20);

    std::cout << total_p << std::endl;

    return 0;

}

double prit_total(std::ostream& os,const Quote& item,size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
      << "# sold: " << n << " total due: " << ret << std::endl;

    return ret;
}

void print_debug(const Quote &q)
{
    q.debug();
}

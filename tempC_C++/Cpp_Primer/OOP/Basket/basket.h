#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>

#include "quote.h"
#include "bulk_quote.h"
#include "disc_quote.h"
#include "limit_quote.h"


/*
    对于C++面向对象编程来说，一个悖论是我们无法直接使用对象进行面向
    对象编程。相反，我们必须使用指针和引用。因为指针会增加程序的复杂性
    所以我们经常定义一些辅助的类来处理这种复杂情况
*/

class Basket
{
public:
    //Basket 使用合成的默认构造函数和拷贝控制成员
    void add_Item(const std::shared_ptr<Quote> &sale)
    {
        items.insert(sale);
    }
    //隐藏指针
    /*
      basket 的用户仍然必须处理动态内存
      原因是add_item需要接受一个shared_Ptr参数
      用户不得不按照如下形式编写代码
      Basket bsk;
      bsk.add_item(std::make_shared<Quote>("123",45));
      bsk.add_item(std::make_shared<Quote>("345",45,3,.15));
      
      重新定义add_item 使得它接受一个Quote对象而非shared_ptr 
      新版本的add_item 将负责处理内存分配
      定义两个版本，一个拷贝给定对象，一个移动对象
    */
    void add_Item(const Quote& sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); } //拷贝给定的对象
    void add_Item(Quote&& sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); } //移动给定的对象

    //打印每本书的总价和购物篮中所有书的总价
    double total_receipt(std::ostream&) const;
private:
    //该函数用于比较shared_ptr,multiset成员会用到它
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    { return lhs->isbn() < rhs->isbn(); }
    //multiset 保存多个报价，按照compare成员排序
    std::multiset<std::shared_ptr<Quote>,decltype(compare)*> items{compare};
   
};

#include "basket.h"

double Basket::total_receipt(std::ostream& os) const 
{
    double sum = 0.0; // 保存实时计算出的总价格
    //iter指向ISBN相同的一批元素中的第一个
    //upper_bound 返回一个迭代器，该迭代器指向这批元素的尾后位置
    for(auto  iter = items.cbegin();
              iter != items.cend();
              iter = items.upper_bound(*iter)) //调用upper_bound函数可以跳过与当前关键字相同的所有元素A
                                               //upper_bound 返回的是一个迭代器，该迭代器指向所有与iter
                                               //关键字相等的元素中最后一个元素的下一位置
    {
        sum += print_total(os,**iter,items.count(*iter));
    }
    
}

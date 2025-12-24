#include <iostream>
#include <memory>
#include <string>
#include <vector>

void test()
{
    //当创建一个weak_ptr时，要用一个shared_Ptr来初始化它
    std::shared_ptr<int> p = std::make_shared<int>(42);
    std::weak_ptr<int> p1 = p; //p1和p共享对象
    std::weak_ptr<int> p2(p1); //p2与p1指向相同的对象

    //由于对象可能不存在，我们不能使用weak_ptr直接访问对象
    //而必须调用lock。此函数检查weak_ptr指向的对象是否仍然存在
    //如果存在，lock返回一个指向共享对象的shared_ptr
    //如果不存在，lock返回一个空指针
    if(std::shared_ptr<int> p3 = p2.lock()) //如果p2的共享对象存在条件为true,反之为false
    {}  

    /*
        weak_ptr的几种操作
        weak_ptr的拷贝和赋值
        w = p //p可以是一个shared_ptr或weak_ptr类型
                //赋值后w与p共享同一个对象
        w.reset() //将w置为空
        w.use_count() //与w共享对象的shared_Ptr数量
        w.expired() //若w.use_count()为0,返回true,否则返回false
        
        w.lock() //如果expired为true返回一个空shared_ptr 
                    //否则返回w指向对象的shared_Ptr
    */
    
}

int main()
{
    /*
        weak_ptr 是一种不控制所指向对象生存期的智能指针
        它指向由一个shared_ptr 管理的对象
        
        将一个weak_ptr 绑定到一个shared_ptr 不会改变shared_ptr
        的引用计数

        一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放
        即使weak_ptr指向对象，对象也还是会被释放。

        因此，weak_ptr的名抓住了这种指针“弱”共享对象的特点
    */
    
    return 0;
}

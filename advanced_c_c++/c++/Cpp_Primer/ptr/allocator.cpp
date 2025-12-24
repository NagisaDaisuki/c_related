#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>

void test()
{
    std::string* const p = new std::string[10]; //构造10个空string
    std::string s;
    std::string* q = p;
    while(std::cin >> s && q != p + 10)
    {
        *q++ = s; //将从用户控制台捕获的输入存入q中
    }

    const size_t size = q - p; //获取我们读取string的个数
    //将数组释放
    delete[] p;

}
void test01()
{
    
    std::allocator<std::string> alloc;
    
    std::string s;
    std::string* p = alloc.allocate(10);
    std::string* q = p;
    while(std::cin >> s && q != p + 10)
    {
        alloc.construct(q++,s); //*q++ = s;
        //++q;
    }
    const size_t size = q - p; //输入的string个数
    
    while(q != p)
        alloc.destroy(q--);
    alloc.deallocate(p,10);
}



void my_alloc()
{
    /*
        allocator类
        new 有一些灵活性上的局限
        其中一方面表现在它将内存分配和对象构造组合在了一起，类似的，delete将对象析构和内存释放组合在了一起
        在分配单个对象时，通常希望内存分配和对象初始化组合在一起。因为在这种情况下，我们几乎肯定知道对象应有什么值

        但是当分配一大块内存时，我们通常计划在这块内存上按需构造对象
        我们需将内存分配和对象构造分离
        -这意味着我们可以分配大块内存，但只在真正需要时才真正执行对象创建操作
    
    

        标准allocator类定义在头文件memory中，它帮助我们将内存分配和对象构造分离开来
        它提供一种类型感知的内存分配方法    
        它分配的内存是原始的、未构造的
        类似vector，allocator是一个模板。为了定义一个allocator对象，必须指明这个allocator可以分配的对象类型
        当一个allocator对象分配内存时，它会根据给定的对象类型来确定恰当的内存大小和对齐位置
        
    */
    const int n = 10;
    std::allocator<std::string> alloc; //可以分配string的allocator对象
    auto const p = alloc.allocate(n); //分配n个未初始化的string
    //这个allocate调用为n个string分配了内存


    /*
        标准库allocator类及其算法
        allocator<T> a
        p = a.allocate(n)
        a.deallocate(p,n) 
        a.construct(p,args)
        a.destroy(p)
    */

    /*
        allocator分配未构造的内存

    */
    auto q = p; //q指向最后构造的元素之后的位置
    alloc.construct(q++); //*q为空字符串
    alloc.construct(q++,10,'c'); //*q为cccccccccc
    alloc.construct(q++,"hi"); //*q为hi

    //还未构造对象的情况下就使用原始内存是错误的
    std::cout << *p << std::endl;
    //std::cout << *q << std::endl; //q++移动到下一个位置，当前内存还未进行构造

    /*
        当我们用完对象后，必须对每个构造的元素调用destroy来销毁它们
        函数destroy接受一个指针，对指向的对象执行析构函数
    */

    while(q != p)
        alloc.destroy(--q); //destroy 接受一个指针参数s
    //对q进行析构操作，操作真string

    //一旦元素被销毁后，就可以重新使用这部分内存保存其他string,也可以将其归还给系统
    //释放内存通过deallocate操作
    alloc.deallocate(p,n); //将分配的所有string全部释放

    /*
        传递给deallocate的指针不能为空,且必须指由allocate分配的内存
        而且传递给deallocate的大小参数必须与调用allocate分配内存时提
        供的大小参数具有一样的值
    */

    /*
        拷贝和填充未初始化内存的算法
            标准库还为allocator类定义了两个伴随算法，可以在未初始化内存中创建对象
            这些函数都定义在memory中
        
        uninitialized_copy(b,e,b2); //从迭代器b和e指出的输入范围中拷贝元素到迭代器b2指定的 *未构造的原始内存中*
        uninitialized_copy_n(b,n,b2);  //从迭代器b指向的元素开始，拷贝n个元素到b2开始的内存中
        uninitialized_fill(b,e,t); //在迭代器b和e指定的原始内存范围中创建对象，对象的值均为t的拷贝
        uninitialized_fill(b,n,t); //从迭代器b指向的内存开始创建n个对象，b必须指向足够大的未构造的原始内存
        
        
    */

    std::vector<int> vec = {0,2,4,5,7,10};
    std::allocator<std::vector<int>> alloc1;
    std::vector<int>* pstr = alloc1.allocate(vec.size() * 2);
    auto quo = std::uninitialized_copy(vec.begin(),vec.end(),pstr);
    //通过拷贝vec中的元素来构造从pstr开始的元素
    std::uninitialized_fill_n(quo,vec.size(),42);
    //将剩余的元素初始化为42
    alloc1.deallocate(pstr,vec.size() * 2);

}

int main()
{

    return 0;
}
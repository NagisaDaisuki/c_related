#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>


void unique_ptr_test()
{
    /*
        某个时刻只能有一个unique_ptr指向一个给定对象
        当unique_ptr被销毁时，它所指向的对象也被销毁

        与shared_ptr不同，没有类似make_shared()的标准库函数返回一个unique_ptr
        当需要定义一个unique_ptr时，需要将其绑定到一个new返回的指针上

        类似于shared_ptr unique_ptr 初始化必须采用直接初始化的方式


    */
    {
        std::unique_ptr<int> uni(new int); //默认初始化
        std::unique_ptr<int> uni1(new int(42)); //值初始化
    }
    //每一个unique_ptr都具有独占所有权的语义，所以unique_ptr不支持普通的拷贝或赋值操作
    std::string *str = new std::string("hello world");
    std::unique_ptr<std::string> str1(str); //将一个new返回的指针绑定到该unique_ptr上

    //std::unique_ptr<std::string> str2(str1);   unique_ptr不支持拷贝操作
    //std::unique_ptr<std::string> str2 = str1;  unique_ptr不支持赋值操作
    
    //Call to deleted constructor of 'std::unique_ptr<std::string>' (aka 'unique_ptr<basic_string<char>>')clang(ovl_deleted_init)
    

    //unique_ptr常用操作
    
      //1.创建和初始化
        std::unique_ptr<int> ptr1(new int); //创建一个指向int的unique_ptr
        std::unique_ptr<int> ptr2 = std::make_unique<int>(); //使用make_unique创建unique_ptr
        //std::unique_ptr<int> ptr3 = ptr1;
      //2.移动所有权
        std::unique_ptr<int> sourecePtr(new int(42));
        std::unique_ptr<int> destPtr = std::move(sourecePtr);
      //3.访问指针
        //通过get()成员函数可以获取原始指针
        int* rawPtr = destPtr.get(); //
      //4.解引用操作符
        //可以向原始指针一样使用解引用操作符'*'和箭头操作符'->'
        int value = *destPtr;
      //5.检查是否为空
        //可以使用nullptr或者get()函数来检查unique_ptr是否为空
        if(destPtr)
        {
          //unique_ptr不为空
        }

        if(destPtr.get() != nullptr)
        {
          //unique_ptr不为空
        }

      //6.释放所有权
        //通过release()函数可以释放unique_ptr 对指针的所有权，并返回指针
        //使得unique_ptr不再管理该指针
        int* releasedPtr = destPtr.release(); 
      //7.重置指针
        //通过reset()函数可以重置'unique_ptr',它可以接受一个新的指针或者不带参数
        //将unique_ptr置为空
        destPtr.reset(); //重置为nullptr
        destPtr.reset(new int); //重置为新的指针
      //8.自定义删除器
        //可以在创建'unique_ptr'时提供自定义删除器，用于替代默认的delete操作
        std::unique_ptr<int,std::function<void(int*)>> customPtr \
                (new int,[](int *ptr){
                    delete ptr;
                 });
      //其他将所有权转移的方法
        std::unique_ptr<int> p1(ptr1.release()); //release返回值指针类型为内置指针类型
        //且release函数将ptr1指针置空
        std::unique_ptr<int> p2(new int(100)); //C++14 std::make_unique<T>()
        std::unique_ptr<int> p3(p2.release()); //将p2所有权转移到p3并置p2指针为空
        
      
    //传递unique_ptr参数和返回unique_ptr
        //不能拷贝unique_ptr有一个例外情况：我们可以
        //拷贝或赋值一个将要被销毁的unique_ptr。最常见的例子是从函数返回一个unique_ptr

        
}

std::unique_ptr<int> clone(int p)
{
  return std::unique_ptr<int>(new int(p));
}

//还可以返回一个局部对象拷贝
std::unique_ptr<int> clone_locality(int p)
{
  std::unique_ptr<int> m(new int(p));
  return m;
}

int main()
{
    unique_ptr_test();    
    return 0;
}

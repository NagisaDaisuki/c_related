#include <iostream>
#include <memory>
#include <vector>
#include <string>
/*
    动态分配数组
    
*/

int get_size()
{
    return 10;
}

void mem_alloc()
{
    //为了让new分配一个对象数组，我们要在类名之后跟一对方括号
    int* pia = new int[get_size()];
    //方括号中的大小必须是整型，但不必是常量(普通数组中方括号的数字必须是常量)

    //也可以用一个表示数组的类型别名
    //typedef int myArr[42];  //using myArr = int[42];
    using myArr = int[42];
    int* pia1 = new myArr;  //分配一个42个int的数组，p指向第一个int

    //分配一个数组会得到一个元素类型的指针
    //Warning:动态数组并不是数组类型，而是一个指针

    //初始化动态分配对象的数组
    /*
        默认new分配的对象都是默认初始化的
        可以对数组中的元素进行值初始化，方法是在
        大小后跟一对空括号
    */

    int* pia2 = new int[10]; //未初始化 
    int* pia3 = new int[10](); //默认初始化

    std::string* pia4 = new std::string[10]; //空string
    std::string* pia5 = new std::string[10](); //空string

    //在新标准中，还可以提供一个元素初始化器的花括号列表
    
    //10个int分别用列表中对应的初始化器初始化
    int* pia6 = new int[10]{0,1,2,3,4,5,6,7,8,9};
    //10个string，前四个用给定的初始化器初始化，剩余的进行值初始化
    std::string* psa = new std::string[10]{"a","an","the",std::string(3,'x')};
    
    //释放内存(在退出函数之前)
    delete[] pia;
    delete[] pia1;
    delete[] pia2;
    delete[] pia3;
    delete[] pia4;
    delete[] pia5;
    delete[] pia6;
    delete[] psa;
    
    
    /*
        智能指针和动态数组
            标准库提供了一个可以管理new分配的数组的unique_ptr版本。为了用一个unique_ptr管理动态数组
            我们必须在对象类型后面跟一对空方括号        
    */

    //up指向一个包含10个未初始化int的数组
    std::unique_ptr<int[]> up(new int[10]); //值初始化
    up.release(); //自动用delete[]销毁其指针

    //可以使用下表运算符访问unique_Ptr分配的数组元素
    
    /*
        与unique_Ptr不同，shared_Ptr不支持管理动态数组。如果希望使用shared_ptr管理一个动态数组
        必须提供自己的删除器
    */ 
    std::shared_ptr<int> sp(new int[10],[](int *p){
        delete[] p; //自己定义的删除器        
    });
    sp.reset(); //使用自己提供的lambda删除器释放数组,使用delete[]

    //shared_Ptr 不支持直接管理动态数组的操作,这一特性会影响如何访问数组中的元素
    
    for(size_t i = 0;i != 10;i++)
    {
        *(sp.get() + i) = i; //通过调用get获取原指针，通过变量进行递增操作，最后解引用指针为数组内元素赋值
    }

}
int main()
{
    mem_alloc();
    std::vector<int>* myVec = new std::vector<int>(); //默认初始化
    delete myVec;

    return EXIT_SUCCESS;   
}

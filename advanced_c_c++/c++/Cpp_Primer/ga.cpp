/*
  泛型算法结构
*/
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <numeric>
#include <utility>
                                                                                                                          

class Test
{
  public:
    Test(){}
    ~Test(){}
  public:
    void Texture()
    {
        /*
          任何算法最基本的特性是它要求迭代器提供那些操作
          
          -第二种算法分类的方式是按照是否读写或是重排序列
          中的元素来分类
          -算法还共享一组参数传递规范和一组命名规范

          -------------------------------------------------------

          迭代器是按照他们所提供的操作来分类的，而这种分类形成另一种层次
          
          -除了输出迭代器之外，一个高层类别的迭代器支持低层类别迭代器的所有操作
          

          -------------------------------------------------------
          
          C++标准指明了泛型和数值算法的每个迭代器参数的最小类别

          -对于向一个算法传递错误类别的迭代器的问题，很多编译器不会给出任何警告或者提示

          -------------------------------------------------------



          */
          

          /*
            算法形参模式

            -在任何其他算法的分类之上，还有一组参数规范
            -理解这些参数规范对学习新算法很有帮助
            -通过理解参数的含义，可以将注意力集中在算法所做的操作上
   
            -大多数算法具有如下四种形式之一
            
            alg(beg,end,other args);
            alg(beg,end,dest,other args);
            alg(beg,end,beg2,other args);
            alg(beg,end,beg2,end2,other args);
            -几乎所有算法都接受一个输入范围(输入序列)


            --接受单个目标(dest)迭代器的算法
              dest参数是一个表示算法可以写入的目的位置的迭代器
              *算法假定(assume): 按其需要写入数据，不管写入多少个元素都是安全的
              (向输出迭代器写入数据的算法都假定目标空间足够容纳写入的空间)
            
              dest常见的情况是被绑定到一个插入迭代器或是一个ostream_iterator迭代器上
              插入迭代器会将新元素添加到容器当中，因而保证空间是足够的(保证不会出现拷贝问题)
              ostream_iterator会将数据写入到一个输出流，同样不用担心写入元素的数量
              

            --接受第二个输入序列的算法
              接受单独的beg2或者接受beg2和end2的算法用这些迭代器表示第二各输入范围
              这些算法通常使用第二个范围中的元素与第一个输入范围结合来进行一些运算
              
              单独的beg2算法假定从beg2开始的序列与beg和end表示的序列范围至少一样大

          */
          
          /*
            算法命名规范

            -除了参数规范，算法还遵循一套命名和重载规范
             这些规范诸如：如何提供一个操作代替默认的<或==运算符
             以及算法是将输出数据写入输入序列还是一个分离的目标位置等问题
            

            --一些算法使用重载形式传递一个谓词
              接受谓词参数来代替<=或==运算符的算法，以及那些不接受额外参数的算法
              通常都是重载(overload)的函数。函数的一个版本用元素类型的运算符来比较函数
              另一个版本接受一个谓词参数来代替<=和==
                unique(beg,end); //使用==运算符来比较元素
                unique(beg,end,comp); //使用comp来比较元素
                
            --_if版本的算法
              接受一个元素值的算法通常有另一个不同名的(不是重载的)版本
              该版本接受一个谓词代替元素值(args)。接受谓词参数的算法
              都有附加的_if前缀(prefix)
              find(beg,end,val); //查找输入范围中val第一次出现的位置
              find_if(beg,end,pred); //查找第一个令pred为真的元素



            --区分拷贝元素的版本和不拷贝的版本
              默认情况下，重排元素的算法将重排后的元素写回给定的输入序列中
              这些算法还要提供另一个版本，将元素写到一个指定的输出目的的位置
              
              这些写到额外目的空间的算法都在名字后面附加一个_copy
              reverse(beg,end); //反转输入范围中元素的顺序
              reverse_copy(beg,end,dest); //将元素按逆序拷贝到dest

              一些算法同时提供_copy和_if版本，这些版本接受一个目的位置迭代器和一个谓词
              //从v1中删除奇数元素
              remove_if(v1.begin(),v1.end(),[](int i){return i % 2;});
              remove_copy_if(v1.begin(),v1.end(),back_inserter(v2),[](int i){return i % 2;});


          */





          /*
            特定容器算法
            
            与其他容器不同，链表类型list和forward_list定义了几个成员函数形式的算法
            而且它们定义了独有的sort,merge,remove,reverse和unique
            (通用版本的sort要求随即访问迭代器，因此不能用于list和forward_list)
            因为这两个类型分别提供双向迭代器和前向迭代器
            
            其他通用算法用于list和forward_list的代价太高，所以最好使用容器自带算法


            --链表类型还定义了splice算法，此算法是链表数据结构所特有的
              因此不需要通用版本


            链表特有的操作会改变底层容器
            因为通用的算法是不会去操作容器元素的，所以链表结构的特殊之处由此显露

            

          */
}
private:
};

int main()
{
  int is_ok = EXIT_FAILURE;
  
  //测试remove和replace
  std::vector<int> v1 = {1,2,3,4,5,6,7,8,9};
  std::vector<int> v2;

  //remove_if
  //std::remove_if(v1.begin(),v1.end(),[](int i){return i % 2;}); //从v1中删除元素
  std::remove_copy_if(v1.begin(),v1.end(),std::back_inserter(v2),[](int i){return i % 2;}); //将操作后的序列插入到v2中
  
  std::cout << "遍历v1: " << std::endl;
  for(const auto v : v1)
  {
    std::cout << v << ' ';  
  }
  std::cout << "\n";
  
  std::cout << "遍历v2: " << std::endl;
  for(const auto v : v2)
  {
    std::cout << v << ' ';  
  }


  

  is_ok = EXIT_SUCCESS;
  return is_ok;
}


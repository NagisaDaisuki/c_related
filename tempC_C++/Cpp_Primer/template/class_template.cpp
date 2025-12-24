#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

// 类模板是用来生成类的蓝图的。与函数模板不同
// 编译器不能为类模板推断模板参数类型

// 一对一友好关系
// 前置声明: 在blob 中生声明友元所需要的
template<typename T> class BlobPtr;
template<typename T> class Blob;
template<typename T> 
  bool operator==(const Blob<T>&,const Blob<T>&);

/*
  令模板自己的类型参数成为友元
  template<typename T> class Bar
  {
    friend T;
  };

  模板类型别名
  typedef Blob<std::string> StrBlob;
  //模板类已经被实例化，为一个类型名
  但Blob<T>是一个类模板，未被实例化，不能成为模板类型别名

  c++11 新标准允许我们为类模板定义一个类型别名
  template<typename T>using Twin = std::pair<T,T>;
  
  Twin<std::string> authors; //authors 是一个pair<std::string,std::string>
  
  当定义一个模板类型别名时，可以固定一个或多个模板参数
  template<typename T> using partNo = std::pair<T,unsigned>;
  partNo<std::string> books; //books 是一个 pair<std::string,unsigned>
  partNo<Students> kids; // kids 是一个 pair<Students,unsigned>
*/

template<typename T> class Blob{
  friend class BlobPtr<T>;
  friend bool operator==(const Blob<T>&, const Blob<T>&);

  public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    //构造函数
    Blob();
    Blob(std::initializer_list<T> il);
    
    template<typename Iterator>
    Blob(Iterator b,Iterator e);
    
    //Blob中的元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    //添加和删除元素
    void push_back(const T &t) { data->push_back(t); }
    //移动版本
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    //元素访问
    T& back();
    T& operator[](size_type i);
  private:
    std::shared_ptr<std::vector<T>> data;
    //若data[i]无效，则抛出msg
    void check(size_type i,const std::string& msg) const;

};

// 类模板的名字不是一个类型名
// 类模板用来实例化类型，而一个实例化的类型总是包含模板参数的

// 与其他任何类相同，我们可既可以在类模板内部，也可以在类模板外部为其
// 定义成员函数，**且定义在类模板内的成员函数被隐式声明为内联函数**

// 类外定义成员函数

//接收两个迭代器的构造函数
template<typename T>
template<typename Iterator>
Blob<T>::Blob(Iterator b,Iterator e) : data(std::make_shared<std::vector<T>>(b,e)){}

// check 和元素访问成员
// 模板类成员函数类外定义带上模板参数列表
template<typename T>
void Blob<T>::check(size_type i,const std::string &msg) const 
{
    if(i >= data->size())
      throw std::out_of_range(msg);
}
// 模板类加上尖括号和里面的模板参数


// 下标运算符和 back函数
template<typename T>
T& Blob<T>::back()
{
  check(0,"back on empty Blob");
  return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
  check(i,"subscript out of range");
  return (*data)[i];
}

// 在原StrBlob中类中，这些运算符返回srting& 。而模板版本则返回一个引用
// 指向用来实例化的Blob的版本

// pop_back 函数 与原strblob的成员几乎相同
template<typename T>
void Blob<T>::pop_back()
{
    check(0,"pop_back on empty Blob");
    data->pop_back();
}

// 与其他任何定义在类模板外的成员一样，构造函数的定义要以模板参数开始
template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()){}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) : 
  data(std::make_shared<std::vector<T>>(il)){}


// 在类代码内简化模板类名的使用

template<typename T>
class BlobPtr
{
  public:
    BlobPtr() : curr(0){}
    BlobPtr(Blob<T> &a,size_t sz = 0) : 
      wptr(a.data),curr(sz){}
    T& operator*()const 
    {
      auto p = check(curr,"dereference past end");
      return (*p)[curr]; //(*p)为本对象指向的vector
    }
    //前置递增和递减
    BlobPtr operator++();
    BlobPtr operator--();
    //后置递增和递减
    BlobPtr operator++(int);
    BlobPtr operator--(int);
  private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<T>> check(std::size_t,const std::string&) const;
    //保存一个weak_ptr，表示底层vector可能被销毁
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
    
};


template<typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t n,
                                              const std::string& msg) const
{
    std::shared_ptr<std::vector<T>> p = wptr.lock();
    if(p && n > p->size())
      return p;
    throw std::logic_error(msg);
}

// 在类模板外定义其成员时，必须记住，我们并不在类的作用域中，
// 直到遇到类名才表进入类的作用域
template<typename T>
BlobPtr<T> BlobPtr<T>::operator++()
{
    ++*this;
    BlobPtr ret = *this;
    return ret;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--()
{
  ++*this;
  BlobPtr ret = *this;
  return ret;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
  BlobPtr ret = *this;
  ++*this;
  return ret;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
  BlobPtr ret = *this;
  ++*this;
  return ret;
}

// 类模板的static成员
// 与任何其他类相同，类模板可以声明static成员
template<typename T>
class Foo
{
  public:
    static std::size_t count() { return ctr; }
  private:
    static std::size_t ctr;
};


// 默认模板实参
// 在c++11新标准中可以为函数和类模板提供默认实参
// 更早的c++标准只支持为类模板提供默认实参

//重写compare 默认使用标准库less函数对象模板
template<typename T,typename F = std::less<T>>
int compare(const T& v1,const T& v2,F f = F())
{
    if(f(v1,v2)) return -1;
    if(f(v2,v1)) return 1;
    return 0;
}


// 成员模板
// 一个类可以包含本身是模板的成员函数
// 这种成员被称为成员模板
// 成员模板不能是虚函数

// 定义一个类似于unique_ptr 使用的默认删除器
class DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr) :
      os(s){}

    //与任何函数模板相同，T的类型由编译器推断
    template<typename T> void operator()(T* p) const 
    { os << "deleting unique_ptr" << std::endl; delete p; }
private:
    std::ostream &os;
  
};


// 可以用这个类代替 delete
void test01()
{
    double *p = new double;
    DebugDelete d; //可像delete表达式一样使用的对象
    d(p); // 释放 p
    int* ip = new int;
    //在一个临时DebugDelete对象上调用 operator()(int*)
    DebugDelete()(ip);
    
}
// 可以将DebugDelete 用作unique_ptr 删除器
void test02()
{
    // 销毁p指向的对象
    // 实例化DebugDelete::operator()<int>(int*);
    std::unique_ptr<int,DebugDelete> p(new int,DebugDelete());
    // 销毁sp指向的对象
    // 实例化DebugDelete::operator()<string>(string*)
    std::unique_ptr<std::string,DebugDelete> sp(new std::string(),DebugDelete());

    // unique_ptr 的析构函数会调用 DebugDelete的调用运算符
}

// 类模板的成员模板
// 对于类模板，我们也可以为其定义成员模板
// 在此情况下，类和成员各自有自己的、独立的模板参数




int main()
{
    //实例化类模板
    // 当使用一个类模板时，我们必须提供额外信息
    // 我们现在知道这些额外信息是**显式模板实参(explicit template argument)列表**

    Blob<int> ia;
    Blob<int> ia2 = {0,1,2,3,4};

    //类模板成员函数的实例化
    // 默认情况下，一个类模板的成员函数只有当程序用到它时才进行实例化
    Blob<int> squares = {0,1,2,3,4,5,6,7,8}; //实例化接受初始化列表的构造函数
    // 实例化Blob<int>::size() const
    for(size_t i = 0;i != squares.size();++i)
      squares[i] = i * i; //实例化Blob<int>::operator[](size_t)

    //所有三个对象共享相同的Foo<int>::ctr 和 Foo<int>::count成员
    Foo<int> f1,fi2,fi3;
    auto ct = Foo<int>::count();
    ct = f1.count();
    //ct = Foo::count(); //错误，使用那个模板实例的count (instance) (instanciate)
    // use of class Foo requires template arguments

    // 和其他成员函数一样，一个static成员函数只有在使用时才会实例化
    return 0;
}

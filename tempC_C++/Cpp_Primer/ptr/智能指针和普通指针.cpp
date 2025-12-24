#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

//strBlobPtr的创建不会影响一个StrBlob所指向的对象的生存期
//但是可以防止用户访问一个不再存在的vector的企图

class StrBlobStr;

class StrBlob //使用智能指针对可变长数组进行动态内存分配
{
    friend class StrBlobPtr;
    //返回指向首元素和尾后元素的StrBlobPtr
    
    public:
        //类型别名
        typedef std::vector<std::string>::size_type size_type;
        //两个构造函数
        StrBlob();
        StrBlob(std::initializer_list<std::vector<std::string>> il);
        //数组大小和判断数组是否为空
        size_type size();
        bool empty();
        //元素访问
        std::string& front();
        const std::string& front_const();
        std::string& back();
        const std::string& back_const();
        //插入和弹出元素
        void push_back(const std::string& t);
        void pop_back();
    private: //私有属性
        void check(std::size_t i,const std::string& msg) const;     
        std::shared_ptr<std::vector<std::string>> data;
        
};

StrBlob::StrBlob() : data(nullptr){}
StrBlob::StrBlob(std::initializer_list<std::vector<std::string>> il)
    : data(std::make_shared<std::vector<std::string>>(il)){}

void StrBlob::check(std::size_t i,const std::string& msg) const
{
    if(i > data->size())
        throw std::out_of_range(msg);
}

std::vector<std::string>::size_type StrBlob::size() {return data->size();}
bool StrBlob::empty() {return data->empty();}


//如果抛出异常，函数会提前结束
std::string& StrBlob::front()
{
    check(0,"access to front failed!");
    return data->front();
}

const std::string& StrBlob::front_const()
{
    check(0,"access to const front failed!");
    return const_cast<std::string&>(data->front());
}

std::string& StrBlob::back()
{
    check(0,"access to back failed!");
    return data->back();
}

const std::string& StrBlob::back_const()
{
    check(0,"access to const back failed!");
    return const_cast<std::string&>(data->back());
}

//可变长数组不需要检测下标是否溢出
void StrBlob::push_back(const std::string& t)
{
    data->push_back(t);   
}

void StrBlob::pop_back()
{
    check(0,"pop_back on empty StrBlob");
    data->pop_back();
}


class StrBlobPtr
{
    public:
        StrBlobPtr();
        StrBlobPtr(StrBlob& a,size_t sz = 0);
        std::string& deref() const;
        StrBlobPtr& incr();
    private:
        //若检查成功，check返回一个指向vector的shared_ptr
        std::shared_ptr<std::vector<std::string>> 
            check(std::size_t i,const std::string& msg) const;
        //保存一个wptr,意味着底层vector可能被销毁
        std::weak_ptr<std::vector<std::string>> wptr;
        //保存在vector中的位置
        std::size_t curr;
};

StrBlobPtr::StrBlobPtr() : curr(0){}
StrBlobPtr::StrBlobPtr(StrBlob& a,size_t sz = 0) : wptr(a.data),curr(sz){}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i,const std::string& msg) const
{
    auto ret = wptr.lock();
    if(!ret) //判断智能指针指向的对象是否还存在
        throw std::runtime_error("unbound StrBlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr,"dereference");
    return (*p)[curr];   
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr,"increment past end of StrBlobPtr");
    ++curr;
    return *this;
}







int main()
{
    return 0;
}
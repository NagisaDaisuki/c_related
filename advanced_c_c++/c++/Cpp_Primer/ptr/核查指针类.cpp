#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>


class StrBlobPtr;

class StrBlob{

    friend class StrBlobPtr;
    //返回指向首元素和和尾后元素的StrBlobPtr
    StrBlobPtr begin() {return StrBlobPtr(*this);} 
    StrBlobPtr end() {
        auto ret = StrBlobPtr(*this,data->size());
        return ret;
    }
    public:
        typedef std::vector<std::string>::size_type size_type;
        StrBlob();
        StrBlob(std::initializer_list<std::string> il);
        size_type size() const {return data->size();}
        bool empty() const {return data->empty();}
        //添加和删除元素
        void push_back(const std::string& t) {data->push_back(t);}
        void pop_back();
        //元素访问
        std::string& front();
        const std::string& front_const();
        std::string& back();
        const std::string& back_const();
    private:
        void check(size_type i,const std::string& msg) const;
        std::shared_ptr<std::vector<std::string>> data; 
        //如果data[i]不合法，抛出一个异常

};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>()){}
StrBlob::StrBlob(std::initializer_list<std::vector<std::string>> il) 
    : data(std::make_shared<std::vector<std::string>>(il)){}


void StrBlob::check(size_type i,const std::string& msg) const 
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    check(0,"front on empty StrBlob");
    return data->front();
}

const std::string& StrBlob::front_const()
{
    check(0,"front_const on empty StrBlob");
    return const_cast<const std::string&>(data->front());
}

std::string& StrBlob::back()
{
    check(0,"back on empty StrBlob");
    return data->back();
}

const std::string& StrBlob::back_const()
{
    check(0,"back_const on empty StrBlob");
    return const_cast<std::string&>(data->back());
}

void StrBlob::pop_back()
{
    check(0,"pop_back on empty StrBlob");
    data->pop_back();
}

/*------------------------------------------------------------------*/

class StrBlobPtr{
    public:
        StrBlobPtr() : curr(0){}
        StrBlobPtr(StrBlob& a,size_t sz = 0) : 
            wptr(a.data),curr(sz){} //这里要访问StrBlob需要使用友元
        std::string& deref() const;
        StrBlobPtr& incr();
    private:
        //若检查成功，check返回一个指向vector的shared_Ptr
        std::shared_ptr<std::vector<std::string>>
            check(std::size_t i,const std::string&) const;
        //保存一个weak_ptr，意味着底层vector可能被销毁
        std::weak_ptr<std::vector<std::string>> wptr;
        std::size_t curr; //在数组中的当前位置 
        
};

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i,const std::string &msg) const
{
    auto ret = wptr.lock(); //判断指向的对象是否还存在
    if(!ret)
    {
        throw std::runtime_error("unbound StrBlobPtr");
    }
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
    //如果curr已经指向容器的尾后位置，就不能递增它
    check(curr,"increment past end of StrBlobPtr");
    ++curr;
    return *this;
}



int main()
{
    /*
        核查指针类
        
    */
    return 0;
}
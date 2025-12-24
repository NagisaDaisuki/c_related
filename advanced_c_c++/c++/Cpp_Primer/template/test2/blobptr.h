#ifndef BLOBPTR_H
#define BLOBPTR_H

#include "Blob.h"
#include <memory>
#include <stdexcept>
#include <vector>

template<typename > class BlobPtr;

template<typename T> 
bool operator ==(const BlobPtr<T>& lhs,const BlobPtr<T>& rhs);

template<typename T>
bool operator <(const BlobPtr<T>& lhs,const BlobPtr<T>& rhs);


template<typename T> class BlobPtr{
    friend bool operator == <T>(const BlobPtr<T>& lhs,const BlobPtr<T>& rhs);
    friend bool operator < <T>(const BlobPtr<T>& lhs,const BlobPtr<T>& rhs);

public: 
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T> &a,std::size_t sz = 0) : 
        wptr(a.data),curr(sz){}
    
    T& operator*() const 
    {
        auto p = check(curr,"dereference past end");
        return (*p)[curr];
    } 

    // prefix
    BlobPtr& operator++();
    BlobPtr& operator--();

    // postfix
    BlobPtr operator++(int);
    BlobPtr operator--(int);
    
private: 
    // returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<T>> check(std::size_t,const std::string&) const;

    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;

};

// prefix
template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
    check(curr,"increment past end of StrBlob");
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
    check(curr,"decrement past begin of StrBlob");
    --curr;
    return *this;
}

// postfix
template<typename T> 
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    auto ret = *this;
    ++*this;
    return ret;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    auto ret = *this;
    --*this;
    return ret;
}

template<typename T> bool operator ==(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
    if(lhs.wptr.lock() != rhs.wptr.lock())
        throw std::runtime_error("ptrs to different Blobs!");
    return lhs.i == rhs.i;

}

template<typename T> bool operator <(const BlobPtr<T> &lhs,const BlobPtr<T> &rhs)
{
    if(lhs.wptr.lock() != rhs.wptr.lock())
        throw std::runtime_error("ptrs to different Blobs!");
    return lhs.i < rhs.i;
}

#endif

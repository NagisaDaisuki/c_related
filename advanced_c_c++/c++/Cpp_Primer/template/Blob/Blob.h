#ifndef BLOB_H
#define BLOB_H

#include <memory>
#include <stdexcept>
#include <vector>


template<typename T> 
class Blob
{
    public:
        typedef T value_type;
        typedef typename std::vector<T>::size_type size_type;
        
        // Constructors
        Blob();
        Blob(std::initializer_list<T> il);

        // Constructor taking two iterators
        template<typename It>
        Blob(It b, It e);

        // Number of elements in the blob
        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }

        void push_back(const T& t) { data->push_back(t); }
        void push_back(T&& t) { data->push_back(std::move(t)); }  
        void pop_back();

        // element access
        T& back();
        T& operator[](size_type i);

        const T& back() const;
        const T& operator[](size_type i) const;

    private:
        std::shared_ptr<std::vector<T>> data;
        void check(size_type i, const std::string &msg) const;
};

// default constructor
template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>())
{}

// constructor taking initializer_list 
template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) 
: data(std::make_shared<std::vector<T>>(il)) 
{}

// constructor taking two iterators
template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b,e))
{}

template<typename T>
void Blob<T>::check(size_type i,const std::string& msg) const 
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T>
T& Blob<T>::back()
{
    check(0,"back on empty blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i,"subscript out of range"); 
    return (*data)[i];
}

template<typename T>
const T& Blob<T>::back() const
{
    return (const T&)back();
} 

template<typename T>
const T& Blob<T>::operator[](size_type i) const 
{
    return (const T&)operator[](i);
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0,"pop_back on empty Blob");
    data->pop_back();
}



#endif

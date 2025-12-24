#ifndef VEC_H
#define VEC_H

#include <memory>
#include <initializer_list>

template<typename T> 
class Vec
{
    public:
        template<typename X> using My_pair = std::pair<X,X>; //为类模板pair定义一个类型别名 My_pair
        
        Vec() : element(nullptr),first_free(nullptr),cap(nullptr){} 
        Vec(std::initializer_list<T> l);
        Vec(const Vec& v);
        ~Vec();
        Vec& operator=(const Vec& rhs);
        //members 
        void push_back(const T& t);
        
        std::size_t size() const { return first_free - element; }
        std::size_t capacity() const { return cap - element; }

        T* begin() const { return element; }
        T* end() const { return first_free; }

        void reserve(std::size_t n);

        void resize(std::size_t n);
        void resize(std::size_t n,const T& t);
    
    private:
        // data members
        T* element;
        T* first_free;
        T* cap;

        std::allocator<T> alloc;

        // utilities
        void reallocate();
        void chk_n_alloc() { if(size() == capacity()) reallocate(); } 
        void free();
        
        void wy_alloc_n_move(std::size_t n);
        
        std::pair<T*,T*> alloc_n_copy(T* b,T* e);        
};

// copy constructor 
template<typename T> 
Vec<T>::Vec(const Vec &v)
{
    std::pair<T*,T*> newData = alloc_n_copy(v.begin(),v.end());

    element = newData.first;
    first_free = cap = newData.second;
}

// constructor that takes initializer_list
template<typename T> 
Vec<T>::Vec(std::initializer_list<T> l)
{
    // allocate memory as large as l.size()
    T* const newData = alloc.allocate(l.size());
    
    // copy elements from l to the address allocated
    T* p = newData;
    for(const auto &t : l)
        alloc.construct(p++,t);

    // build data structure 
    element = newData;
    first_free = cap = element + l.size();
}

// operator =
template<typename T>
Vec<T>& Vec<T>::operator =(const Vec& rhs)
{
    // allocate and copy first to protect against self_assignment
    std::pair<T*,T*> newData = alloc_n_copy(rhs.begin(),rhs.end());

    // destroy and deallocate 
    free();
    
    // update data structure 
    element = newData.first;
    first_free = cap = newData.second;

    return *this;
} 


// destrtuctor 
template<typename T>
Vec<T>::~Vec()
{
    free();   
}

// push_back 
template<typename T>
void Vec<T>::push_back(const T &t)
{
    chk_n_alloc();
    alloc.construct(first_free++,t);
}

// reserve 
template<typename T> 
void Vec<T>::reserve(std::size_t n)
{
    // if n too small ,just return without doing anything 
    if(n <= capacity()) return;

    // allocate new memory and move data from old address to the new one
    wy_alloc_n_move(n);   
}

// resize(1

template<typename T> 
void Vec<T>::resize(std::size_t n)
{
    resize(n,T()); //调用第二个resize
}

// resize(2
template<typename T> 
void Vec<T>::resize(std::size_t n,const T& t)
{
    if(n < size())
    {
        //destroy the range [element+n,first_free) using destructor
        for(auto p = element + n;p != first_free;)
            alloc.destroy(p++);
        //update first_free to point to the new address
        first_free = element + n;
    }
    else if(n > size())
    {
        for(auto i = size();i != n;++i)
            push_back(t);
    }
}

template<typename T>
std::pair<T*,T*> 
Vec<T>::alloc_n_copy(T* b,T* e)
{
    // calculate the size needed and allocate space accordingly
    T *data = alloc.allocate(e - b);
    return { data,std::uninitialized_copy(b,e,data) };
    // the return value of uninitialized_copy is the Iterator to the element past the last element copied
    // 指向最后一个拷贝元素之后一个迭代器
}

template<typename T>
void Vec<T>::free()
{
    // if not nullptr
    if(element)
    {
        // destroy it in reverse order 
        for(auto p = first_free;p != element;)
            alloc.destroy(--p);

        alloc.deallocate(element,capacity()); //在删除完内存上存在的元素后释放内存   
    }
}


// wy_alloc_n_move(std::size_t n)

template<typename T>
void Vec<T>::wy_alloc_n_move(std::size_t n)
{
    // allocate as required 
    std::size_t newCapacity = n;
    T* newData = alloc.allocate(newCapacity);
    
    // move the data from old place to the new one
    T* dest = newData;
    T* old = element;
    for(std::size_t i = 0;i != size();i++)
        alloc.construct(dest++,std::move(*old++));

    free();

    // update data structure 
    element = newData;
    first_free = dest;
    cap = element + newCapacity;
}

template<typename T>
void Vec<T::reallocate()
{
    // calculate the new capacity required
    std::size_t newCapacity = size() ? 2 * size() : 1;

    // allocate and move old data to the new space
    wy_alloc_n_move(newCapacity);
}

#endif

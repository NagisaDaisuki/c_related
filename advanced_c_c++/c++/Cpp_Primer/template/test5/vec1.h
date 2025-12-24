#ifndef VEC_H
#define VEC_H

#include <memory>
#include <vector>

template<typename T>
class Vec{
  
public:
    Vec() : element(nullptr),first_free(nullptr),cap(nullptr){}
    Vec(std::initializer_list<T> l);
    Vec(const Vec& v);
    Vec& operator=(const Vec& v);
    ~Vec();
    
    void push_back(const T& t);
    
    template<typename... Args>
    void emplace_back(Args... args);
    
    T* begin() const { return element; }
    T* end() const { return first_free; }
    
    std::size_t size() const { return first_free - element; }
    std::size_t capacity() const { return cap - element; }
    
private:
    T* element;
    T* first_free;
    T* cap;
    
    std::allocator<T> alloc;

    void reallocate();
    void reserve(std::size_t n);
    void resize(std::size_t n);
    void resize(std::size_t n,const T& t);
    
    void chk_n_alloc(){ if(size() == capacity()) reallocate(); }
    
    void wy_n_alloc_move(std::size_t n);
    std::pair<T*,T*> alloc_n_copy(T* b,T* e);
    void free();
};

template<typename T>
Vec<T>::Vec(const Vec& v)
{
  std::pair<T*,T*> newData = alloc_n_copy(v.begin(),v.end());
  element = newData.first;
  first_free = cap = newData.second;
}

template<typename T>
Vec<T>::Vec(std::initializer_list<T> l)
{
  T* Data = alloc.allocate(l.size());
  T* p = Data;
  for(const auto& e : l)
    alloc.construct(p++,e);
  element = Data;
  first_free = cap = p;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec& v)
{
  std::pair<T*,T*> newData = alloc_n_copy(v.begin(),v.end());
  free();
  element = newData.first;
  first_free = cap = newData.second;
}

template<typename T>
Vec<T>::~Vec()
{
  free();
}

template<typename T>
void Vec<T>::push_back(const T& t)
{
  chk_n_alloc();
  alloc.construct(first_free++,t);
}

template<typename T>
template<typename... Args>
void Vec<T>::emplace_back(Args... args)
{
  chk_n_alloc();
  alloc.construct(first_free++,std::forward<Args>(args)...);
}

template<typename T>
std::pair<T*,T*> Vec<T>::alloc_n_copy(T* b,T* e)
{
  T* Data = alloc.allocate(e - b);
  return { Data,std::uninitialized_copy(b,e,Data) };
}

template<typename T>
void Vec<T>::reserve(std::size_t n)
{
  if(n <= capacity())
    return;
  wy_n_alloc_move(n);
}

template<typename T>
void Vec<T>::reallocate()
{
  std::size_t newcapacity = size() ? size() * 2 : 1;
  wy_n_alloc_move();
}

template<typename T>
void Vec<T>::resize(std::size_t n)
{
  resize(n,T());
}

template<typename T>
void Vec<T>::resize(std::size_t n,const T& t)
{
  if(n < size())
  {
      for(auto& p = element + n;p != first_free;)
        alloc.destroy(p++);
      // alloc.deallocate(element + n,n);
      first_free = element + n;
  }
  else
  {
    for(std::size_t num = size(); num != n;num++)
      push_back(t);
  }
}

template<typename T>
void Vec<T>::free()
{
  if(element)
  {
    for(auto& p = element; p != first_free;)
      alloc.destroy(p++);
    alloc.deallocate(element,capacity());
  }
}

template<typename T>
void Vec<T>::wy_n_alloc_move(std::size_t n)
{
  std::size_t newcapacity = n;
  T* Data = alloc.allocate(n);
  T* p = Data;
  
  T* dest = Data;
  T* beg = element;
  for(std::size_t s = 0; s != size();s++)
    alloc.construct(dest++,std::move(*beg++));
  free();

  element = Data;
  first_free = dest;
  cap = Data + newcapacity;
}









#endif 

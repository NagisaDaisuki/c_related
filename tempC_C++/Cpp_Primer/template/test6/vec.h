//#include <iostream>
//#include <string>
#include <memory> 
#include <vector>
#include <initializer_list> 
template<typename T>
class Vec 
{
  public:
    Vec() : element(nullptr),first_free(nullptr),cap(nullptr){}
    Vec(std::initializer_list<T> l);
    Vec(const Vec& v);
    Vec& operator=(const Vec& v);
    ~Vec();

    // operation
    void push_back(const T& t);

    template<typename... Args>
    void emplace_back(Args&&... args);

    T* begin() const { return element; }
    T* end() const { return first_free; }

    std::size_t size() const { return first_free - element; }
    std::size_t capacity() const { return cap - element; }
    
    void reserve(std::size_t n);
    void resize(std::size_t n);
    void resize(std::size_t n,const T& t);

  private:
    T* element;
    T* first_free;
    T* cap;
    
    std::allocator<T> alloc;
    
    // utilities 
    void reallocate();
    void chk_n_alloc() { if(size() == capacity()) reallocate();}
    void free();
    void wy_alloc_n_move(std::size_t n);
    
    std::pair<T*,T*> alloc_n_copy(T* b,T* e);

};

template<typename T>
Vec<T>::Vec(std::initializer_list<T> l)
{
    T* data = alloc.allocate(l.size());
    T* p = data;

    //for(auto& n = l.begin();n != l.end();)
    //  alloc.construct(p++,*n++);
    for(const auto& t : l)
      alloc.construc(p++,t);
    element = data;
    first_free = cap = p; // first_free = cap = element + l.size();
}

template<typename T>
Vec<T>::Vec(const Vec& v)
{
  std::pair<T*,T*> newdata = alloc_n_copy(v.begin(),v.end());
  
  element = newdata.first;
  first_free = cap = newdata.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec& v)
{
    std::pair<T*,T*> newdata = alloc_n_copy(v.begin(),v.end());
    free();
    element = newdata.first;
    first_free = cap = newdata.second;
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
void Vec<T>::emplace_back(Args&&... args)
{
  chk_n_alloc();
  alloc.construct(first_free,std::forward<Args>(args)...);
}

template<typename T>
void Vec<T>::reserve(std::size_t n)
{
  if(n <= capacity())
    return;
  wy_alloc_n_move(n);
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
      first_free = element + n;
  }
  else if(n > size())
  {
      for(auto i = size(); i != n;i++)
        push_back(t);
  }
}

template<typename T>
std::pair<T*,T*> 
Vec<T>::alloc_n_copy(T* b,T* e)
{
  T* data = alloc.allocate(e - b);
  return { data,std::uninitialized_copy(b,e,data) };
}


template<typename T>
void Vec<T>::free()
{
  if(element)
  {
    for(auto& p = element;p != first_free;)
      alloc.destroy(p++);
    alloc.deallocate(capacity());
  }
}

template<typename T>
void Vec<T>::wy_alloc_n_move(std::size_t n)
{
  std::size_t newcapacity = n;
  T* data = alloc.allocate(newcapacity);
  
  T* dest = data;
  T* beg = element;
  for(;beg != first_free;beg++)
    alloc.construct(data++,);
}

template<typename T>
void Vec<T>::reallocate()
{
  std::size_t newCapacity = size() ? 2 * size() : 1;
  wy_alloc_n_move(newCapacity);
}







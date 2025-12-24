#pragma once
#include <functional>
#include "delete.hpp"

/*
    花括号初始化和括号初始化的区别
    (brace initialization and parenthesis initialization)

    花括号初始化在某些情况下具有更严格的初始化规则
    如果提供的值不能被转换为目标类型，则会导致编译错误
    -花括号可以避免隐式类型转换带来的潜在问题

    使用花括号初始化时，编译器会尝试匹配列表初始化(list initialization)
    的构造函数。如果不存在相匹配的构造函数，编译器会尝试使用其他初始化方法
*/

namespace cp5
{
    template<typename T>
    class SharedPointer;

    template<typename T>
    auto swap(SharedPointer<T>& lhs,SharedPointer<T>& rhs)
    {
        using std::swap;
        swap(lhs.ptr,rhs.ptr);
        swap(lhs.ref_count,rhs.ref_count);
        swap(lhs.deleter,rhs.deleter);
    }
    
    template<typename T>
    class SharedPointer
    {
        public:
            // Default Ctor
            SharedPointer() 
                : ptr{ nullptr },ref_count{ new std::size_t(1) },deleter{ cp5::Delete{} }
                {}
            
            // Ctor that takes raw pointer 
            explicit SharedPointer(T* raw_ptr)
                : ptr{ raw_ptr },ref_count{ new std::size_t(1) },deleter{ cp5::Delete{} }
                {}
            
            // Copy Ctor
            SharedPointer(SharedPointer const& other)
                : ptr{ other.ptr },ref_count{ other.ref_count },deleter{ other.deleter }  
            {
                ++*ref_count;
            }

            // Move Ctor
            SharedPointer(SharedPointer &&other) noexcept
                : ptr{ other.ptr },ref_count{ other.ref_count },deleter{ std::move(other.deleter) }
                {
                    other.ptr = nullptr;
                    other.ref_count = nullptr;
                }
            
            // Copy assignment 
            SharedPointer& operator=(SharedPointer const& rhs) 
            {
                // increment first to ensure safty for self_assignment
                ++*rhs.ref_count;
                decrement_and_destroy();
                ptr = rhs.ptr, ref_count = rhs.ptr, deleter = rhs.deleter;
                return *this;
            }

            // Move assignment 
            SharedPointer& operator=(SharedPointer && rhs)
            {
                cp5::swap(*this,rhs);
                rhs.decrement_and_destroy();
                return *this;
            }

            // Conversion operator 
            operator bool() const
            {
                return ptr ? true : false;
            }

            // Dereference 
            T& operator*() const 
            {
                return *ptr;
            }

            // Arrow 
            T* operator->() const 
            {
                return &*ptr;
            }

            // Use count
            auto use_count() const 
            {
                return *ref_count;
            }

            // get underlying pointer 
            auto get() const 
            {
                return ptr;
            }

            // check if the unique user 
            auto unique() const 
            {
                return 1 == *ref_count;
            }

            auto swap(SharedPointer& rhs)
            {
                cp5::swap(*this,rhs);
            }

            auto reset()
            {
                decrement_and_destroy();
            }

            auto reset(T* pointer)
            {
                if(ptr != pointer)
                {
                    decrement_and_destroy();
                    ptr = pointer;
                    ref_count = new std::size_t(1);
                }
            }

            auto reset(T* pointer, const std::function<void(T*)>& d)
            {
                reset(pointer);
                deleter = d;
            }

            // Dtor 
            ~SharedPointer()
            {
                decrement_and_destroy();
            }
        private:
            T* ptr;
            std::size_t* ref_count;
            std::function<void(T*)> deleter;

            auto decrement_and_destroy()
            {
                if(ptr && 0 == --*ref_count)
                    delete ref_count,deleter(ptr);
                else if(!ptr)
                    delete ref_count;
                ref_count = nullptr;
                ptr = nullptr; //避免dangling pointer
            }
    };
}
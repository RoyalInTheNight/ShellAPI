#ifndef ARRAY_CORE
#define ARRAY_CORE

#include <iostream>
#include <exception>
#include <core.h>

using namespace core::types;

template<class __alloc_t> class Allocator {
public:
    __alloc_t *allocator(u32 size = 1) {
        __alloc_t *ptr = size == 1 || size <= 0 ? new __alloc_t() : new __alloc_t[size];

        if (ptr == nullptr)
            throw std::runtime_error("base_allocator: error allocate memory\n");

        return ptr;
    }

    __alloc_t *add_memory(__alloc_t *ptr, u32 size_ptr, u32 size) {
        __alloc_t *tmp_ptr = allocator(size);

        size_ptr = size_ptr > size ? size : size_ptr;

        for (u32 i = 0; i < size_ptr; i++)
            tmp_ptr[i] = ptr[i];

        delete[] ptr;

        return tmp_ptr;
    }
}; // base allocator

template<class __val_t, class alloc = Allocator<__val_t>> class array
        : public alloc {
protected:
    typedef __val_t *_Pt;
    typedef u32      _Sz;
    typedef bit      _Bt;

    _Pt ptr;
    _Sz ptr_sz;
    _Sz deleted;
    
    _Sz *ref_c;

    inline _Sz ptr_len(const _Pt pt) {
        _Pt s;

        for (s = pt; *s; s++);
        return (s - pt) - 1;
    }

public:
    typedef array<__val_t, alloc> arr;

    array(arr& cpy) : ptr(cpy.ptr), ptr_sz(cpy.ptr_sz), ref_c(cpy.ref_c) {++(*ref_c);}
    array(_Pt cpy)  : ptr(cpy), ptr_sz(ptr_len(cpy)), ref_c(new _Sz(1)) {}
    array(_Sz size) : ptr(this->allocator(size)), ptr_sz(size), ref_c(new _Sz(1)) {}
    array() : ptr(nullptr), ptr_sz(0), ref_c(new _Sz(0)) {}

    inline void update_size() {
        _Sz fact_size = ptr_len(ptr);

        if (fact_size == ptr_sz)
            return;

        ptr = this->add_memory(ptr, fact_size, ptr_sz);
    }

    inline _Sz size() const {return ptr_sz;}
    inline _Sz length() const {return ptr_sz <= 0 ? 0 : ptr_sz - 1;}
    inline _Pt data() {update_size(); return ptr;}
    inline _Bt isEmpty() const {return ptr_sz ? false : true;}

    inline __val_t& at(_Sz pos = 0) {
        if (pos >= ptr_sz)
            throw std::runtime_error("out of range\n");
        
        return *(ptr + pos);
    }

    inline void push_back(__val_t val) {
        if (isEmpty()) {
            ptr = this->allocator();
            ptr_sz = 1;

            ++(*ref_c);
        }

        else
            ptr = this->add_memory(ptr, ptr_sz, ++ptr_sz);
        
        *(ptr + length()) = val;
    }

    inline void pop_back() {
        if (isEmpty())
            return;

        --ptr_sz;
    }

    inline __val_t& operator[](_Sz pos) {return at(pos);}

    inline arr& operator=(arr& cpy) {
        if (this == &cpy)
            return *this;
        
        if (cpy.ref_c) {
            if (!isEmpty()) {
                if (ptr_sz == 1)
                    delete ptr;
                
                else
                    delete[] ptr;
            }
            
            ptr    = cpy.ptr;
            ptr_sz = cpy.ptr_sz;
            ref_c  = cpy.ref_c;

            ++(*ref_c);
        }

        return *this;
    }

    inline arr& operator=(_Pt cpy) {
        if (cpy == nullptr)
            return *this;
        
        if (!isEmpty()) {
            if (ptr_sz == 1)
                delete ptr;
            
            else
                delete[] ptr;
        }

        ptr    = cpy;
        ptr_sz = ptr_len(cpy);

        return *this;
    }

    inline arr& operator+=(arr& cpy) {
        if (cpy.isEmpty())
            return *this;
        
        if (isEmpty())
            return *this = cpy;

        _Sz new_size = ptr_sz + cpy.ptr_sz;
        
        ptr = this->add_memory(ptr, ptr_sz, new_size);

        for (_Sz i = 0; i < cpy.ptr_sz; i++)
            ptr[i + ptr_sz] = cpy.at(i);

        ptr_sz = new_size;
        
        return *this;
    }

    inline arr& operator+=(_Pt cpy) {
        if (cpy == nullptr)
            return *this;
        
        if (isEmpty())
            return *this = cpy;
        
        _Sz cpy_size = ptr_len(cpy);
        _Sz new_size = cpy_size + ptr_sz;

        ptr = this->add_memory(ptr, ptr_sz, new_size);

        for (_Sz i = 0; i < cpy_size; i++)
            ptr[i + ptr_sz] = cpy[i];
        
        ptr_sz = new_size;
        
        return *this;
    }

    inline arr& operator+(arr& cpy) {
        return *this += cpy;    
    }

    inline arr& operator+(_Pt cpy) {
        return *this += cpy;
    }

    ~array() {
        if (ref_c) {
            --(*ref_c);

            if (!(*ref_c)) {
                if (!ptr_sz)
                    delete[] ptr;

                delete ref_c;
            }
        }
    }
};

#endif // ARRAY_CORE
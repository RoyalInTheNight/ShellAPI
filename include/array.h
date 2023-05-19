#ifndef ARRAY_CORE
#define ARRAY_CORE

#include <iostream>
#include <exception>
#include <core.h>

using namespace core::types;

template<class __alloc_t> class Allocator {
public:
    __alloc_t *allocator(u32 size) {
        __alloc_t *ptr = new __alloc_t[size];

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

template<class __val_t, class allocator = Allocator<__val_t>> class array {
protected:
    __val_t     *arr_ptr;
    u32     size_arr_ptr;
    u32 *reference_count;

    allocator      alloc;

public:
    array(array<__val_t, allocator>& copy) : arr_ptr(std::move(copy.arr_ptr)), size_arr_ptr(copy.size_arr_ptr), reference_count(copy.arr_ptr ? new u32(1) : nullptr) {}
    array(u32 size) : arr_ptr(alloc.allocator(size)), size_arr_ptr(size), reference_count(new u32(0)) {}
    array() : size_arr_ptr(0), reference_count(new u32(0)) {}

    inline u32 size() const { return size_arr_ptr; }
    inline u32 length() const { if (size_arr_ptr > 0) return size_arr_ptr - 1; else return 0; }
    inline emt reference_increment() { this->reference_count++; }
    inline emt clear() { this->arr_ptr = alloc.allocator(this->size()); }

    inline __val_t& get(u32 pos = 0) {
        if (pos >= size_arr_ptr)
            throw std::runtime_error("array: out of range n >= n\n");

        return arr_ptr[pos];
    }

    emt push_back(__val_t value) {
        if (size_arr_ptr == 0) { 
            arr_ptr = alloc.allocator(size_arr_ptr);
            size_arr_ptr++;
        }

        else 
            arr_ptr = alloc.add_memory(arr_ptr, size_arr_ptr, size_arr_ptr++);

        arr_ptr[length()] = value;

        if (arr_ptr[length()] != value)
            throw std::runtime_error("array: error add element\n");
    }

    emt pop_back() {
        arr_ptr = alloc.add_memory(arr_ptr, size_arr_ptr, size_arr_ptr--);

        if (arr_ptr == nullptr)
            throw std::runtime_error("array: error delete element\n");
    }

    inline __val_t *data() const { return arr_ptr; }
    inline __val_t& operator[](u32 pos) { return get(pos); }

    array<__val_t, allocator>& operator=(array<__val_t, allocator>& copy) {
        if (&copy == this)
            return *this;

        if (copy.reference_count) {
            this->arr_ptr      = copy.arr_ptr;
            this->size_arr_ptr = copy.size_arr_ptr;

            ++(*copy.reference_count);

            this->reference_count = copy.reference_count;
        }

        return *this;
    }

    ~array() {
        if (this->reference_count) {
            --(*this->reference_count);

            if (!(*this->reference_count)) {
                delete[] this->arr_ptr;
                delete[] this->reference_count;
            }
        }
    }
};

#endif // ARRAY_CORE
#ifndef STRARRAY_CORE
#define STRARRAY_CORE

#include <array.h>
#include <core.h>

class base_string : public array<s8, Allocator<s8>> {
private:
    inline u32 strlen(s8 *str) {
        register const s8 *s;

        for (s = str; *s; ++s);
            return (s - str);
    }

public:
    base_string(smt string) {
        this->size_arr_ptr = strlen(string);
        this->arr_ptr      = alloc.allocator(this->size_arr_ptr);
        
        for (u32 i = 0; i < this->size_arr_ptr; i++)
            this->arr_ptr[i] = std::move(*string++);
    }

    base_string() {}

    inline smt c_str() const { return this->arr_ptr; }

    inline base_string& operator=(base_string& str) {
        if (&str == this)
            return *this;
        
        if (str.reference_count) {
            this->arr_ptr      = str.data();
            this->size_arr_ptr = str.size();

            ++(*str.reference_count);

            this->reference_count = str.reference_count;
        }

        return *this;
    }

    inline base_string& operator=(smt str) {
        this->size_arr_ptr = strlen(str);
        this->arr_ptr      = alloc.allocator(this->size_arr_ptr);

        for (u32 i = 0; i < this->size_arr_ptr; i++)
            this->arr_ptr[i] = std::move(*str++);
        
        return *this;
    }

    inline base_string& operator+=(base_string& str) {
        if (!this->size()) {
            this->size_arr_ptr += str.size();

            this->arr_ptr = alloc.allocator(this->size());

            for (u32 i = 0; i < str.size(); i++)
                this->arr_ptr[i] = str[i];
        }

        else {
            this->arr_ptr = alloc.add_memory(this->arr_ptr, this->size_arr_ptr, (this->size_arr_ptr + str.size()));
        
            for (u32 i = 0; i < str.size(); i++)
                this->arr_ptr[i + this->size_arr_ptr] = str[i];

            this->size_arr_ptr += str.size();
        }

        return *this;
    }

    inline base_string& operator+=(smt str) {
        u32 size_str = strlen(str);

        if (!this->size()) {
            this->arr_ptr = alloc.allocator(size_str);
            this->size_arr_ptr += size_str;

            for (u32 i = 0; i < this->size(); i++)
                this->arr_ptr[i] = str[i];
        }

        else {
            this->arr_ptr = alloc.add_memory(this->arr_ptr, this->size_arr_ptr, (this->size_arr_ptr + size_str));

            for (u32 i = 0; i < size_str; i++)
                this->arr_ptr[i + this->size_arr_ptr] = str[i];

            this->size_arr_ptr += size_str;
        }

        return *this;
    }

    inline base_string& operator+(base_string& str) {
        this->arr_ptr = alloc.add_memory(this->arr_ptr, this->size_arr_ptr, (this->size_arr_ptr + str.size()));

        for (u32 i = 0; i < str.size(); i++)
            this->arr_ptr[i + this->size_arr_ptr] = str[i];

        this->size_arr_ptr += str.size();

        return *this;
    }

    inline base_string& operator+(smt str) {
        u32 size_str = strlen(str);

        this->arr_ptr = alloc.add_memory(this->arr_ptr, this->size_arr_ptr, (this->size_arr_ptr + size_str));

        for (u32 i = 0; i < size_str; i++)
            this->arr_ptr[i + this->size_arr_ptr] = str[i];

        this->size_arr_ptr += size_str;
        
        return *this;
    }
};

#endif // STRARRAY_CORE

#include <string_array.h>
#include <iostream>

s32 main() {
    array<u32> tt(3);
    array<u32> ss;
    array<u32> st;


    tt[0] = 32;
    tt[1] = 33;
    tt[2] = 34;

    for (u32 i = 0; i < tt.size(); i++) 
    std::cout << tt[i] << std::endl;

    ss = tt;
    st = tt;
    tt = tt;

    std::cout << std::endl;

    base_string str = "Array ";
    base_string str2 = "2Array ";

    str += str2;
    str2 += str;
    str  = str2;

    std::cout << str.c_str() << std::endl << str2.c_str() << std::endl;
}

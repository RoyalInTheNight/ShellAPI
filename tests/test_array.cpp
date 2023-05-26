#include <array.h>

s32 main() {
    array<int> tt;
    int *ptr = new int[10];

    tt.pop_back();

    for (u32 i = 0; i < 10; i++) {
        tt.push_back(i + 23);
        ptr[i] = i + 25;
    }

    for (u32 i = 0; i < tt.size(); i++)
        std::cout << tt[i] << " ";

    tt.pop_back();

    std::cout << std::endl;

    for (u32 i = 0; i < tt.size(); i++)
        std::cout << tt[i] << " ";

    array<int> ta = tt;

    for (u32 i = 0; i < ta.size(); i++)
        std::cout << ta[i] << std::endl;


    std::cout << std::endl;

    ta = ptr;
    ta += tt;

    for (u32 i = 0; i < ta.size(); i++)
        std::cout << ta[i] << std::endl;
}

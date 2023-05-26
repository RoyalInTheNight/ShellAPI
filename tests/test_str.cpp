#include <string_array.h>
#include <core.h>

using namespace core::types;

s32 main() {
    char *str3 = "Hi\n";
    char *str4 = "Hello world!!\n";

    string str = str4;
    string str2 = str3;

    str2 += str;

    std::cout << str2.data() << std::endl;
}
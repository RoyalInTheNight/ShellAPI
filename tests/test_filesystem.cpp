#include <filesystem.h>

s32 main() {
    filesystem fsys;

    string str = fsys.file_read("Makefile");
    u32   file_size = (u32)fsys.file_size("Makefile");

    std::cout << str.data() << std::endl << file_size << std::endl << str.size() << std::endl;

    fsys.file_write("test_fs.txt", str);
    fsys.file_copy("test_fs.txt", "test_gs.txt");
    fsys.file_remove("test_fs.txt");

    std::cout << fsys.get_app_data() << std::endl;
    std::cout << fsys.get_tmp() << std::endl;

    std::cout << fsys.file_read("test_gs.txt").data() << std::endl;

    fsys.file_remove("test_gs.txt");
    fsys.file_create("fs_dir");
}
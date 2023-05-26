#include <filesystem.h>

std::streampos filesystem::file_size(const fs::path file_path) {
    std::ifstream file(file_path, std::ios_base::binary);

    if (file.fail())
        throw std::runtime_error("filesystem: file_open error\n");

    std::streampos

    file_size = file.tellg();
    file.seekg(0, std::ios::end);
    file_size = file.tellg() - file_size;

    file.close();

    return file_size;
}

string filesystem::file_read(const fs::path file_path) {
    std::streampos size_file = file_size(file_path);
    std::ifstream  file(file_path, std::ios_base::binary);

    if (file.fail())
        throw std::runtime_error("filesystem: file_open error\n");

    smt read_file_buffer = new s8[(u32)size_file];

    file.read(read_file_buffer, (u32)size_file);
    file.close();

    string str = read_file_buffer;

    return str;
}

emt filesystem::file_write(const fs::path file_path, string data) {
    std::ofstream file(file_path, std::ios_base::binary);

    if (file.is_open()) {
        file.write(data.data(), data.size());
        file.close();
    }

    else throw std::runtime_error("filesystem: file_open error\n");
}

fs::path filesystem::get_app_data() {
    #ifdef WIN64
        return getenv("APPDATA");
    #else
        return "/etc";
    #endif // WIN64
}

fs::path filesystem::get_tmp() {
    #ifdef WIN64
        return getenv("TEMP");
    #else
        return "/tmp";
    #endif // WIN64
}

emt filesystem::file_remove(const fs::path file_path) { fs::remove(file_path); }
emt filesystem::file_copy(const fs::path file_path_src, const fs::path file_path_dst) { fs::copy(file_path_src, file_path_dst); }
emt filesystem::file_move(const fs::path file_path_src, const fs::path file_path_dst) { fs::copy(file_path_src, file_path_dst); fs::remove(file_path_src); }
emt filesystem::file_create(const fs::path file_path) { fs::create_directory(file_path); }
#ifndef FS_CORE
#define FS_CORE

#include <string_array.h>
#include <filesystem>
#include <fstream>
#include <core.h>

namespace fs = std::filesystem;

using namespace core::types;
using namespace core::filesystem;

typedef base_string  string;

class filesystem {
public:
    static std::streampos file_size (const fs::path);
    static string file_read (const fs::path);
    static emt    file_write(const fs::path, const string);

    static fs::path get_app_data();
    static fs::path get_tmp();
    
    static emt file_remove(const fs::path);
    static emt file_copy(const fs::path, const fs::path);
    static emt file_move(const fs::path, const fs::path);
    static emt file_create(const fs::path);
};

#endif // FS_CORE
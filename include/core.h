#ifndef SHELL_CORE
#define SHELL_CORE

namespace core {
    namespace types {
        typedef char                s8;
        typedef unsigned char       u8;
        typedef short              s16;
        typedef unsigned short     u16;
        typedef int                s32;
        typedef unsigned int       u32;
        typedef long long          s64;
        typedef unsigned long long u64;
        typedef float              f32;
        typedef double             f64;
        typedef long double       f128;

        typedef void               emt;
        typedef void *             mmt;
        typedef char *             smt;
    }

    namespace socket {
        typedef core::types::s32 SOCKET;

        const static core::types::s32 backlog         = 512;
        const static core::types::s32 max_connections = 2048;
        const static core::types::s32 max_message_len = 4096;

        namespace errors {
            const static core::types::u32 invalid_socket = ~(0);
            const static core::types::s32 socket_error   = -(1);
            const static core::types::s32 connect_error  = -(2);
            const static core::types::s32 bind_error     = -(2);
            const static core::types::s32 listen_error   = -(3);
            const static core::types::s32 send_error     = -(4);
            const static core::types::s32 recv_error     = -(5);
            const static core::types::s32 ok             =  (0);
        }

        namespace liburing_errors {
            const static core::types::s32 io_queue_error = -(6);
        }
    }

    namespace filesystem {
        namespace errors {
            const static core::types::s32 read_file_error  = -(4);
            const static core::types::s32 write_file_error = -(5);
            const static core::types::s32 len_file_error   = -(6);
        }
    }
}

#endif // SHELL_CORE

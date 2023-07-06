#ifndef D8C1E08F_809D_473C_8B7F_77C96B1000B2
#define D8C1E08F_809D_473C_8B7F_77C96B1000B2

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
    #define OS_Linux
#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
    #define OS_Windows
    #define DIV 1048576
    #define WIDTH 7
#endif


#endif/* D8C1E08F_809D_473C_8B7F_77C96B1000B2 */

#ifndef C129A486_0FCC_42AC_9413_6ABF991DDB75
#define C129A486_0FCC_42AC_9413_6ABF991DDB75

#include "osdetect.hpp"
#include <functional>

#ifdef OS_Windows
#define NOMINMAX
#include <windows.h>
#else
#include <thread>
#include <mutex>
#endif

namespace z1dg::threading {
#ifdef OS_Windows
    typedef HANDLE mutex_type;
    typedef HANDLE thread_type;
    typedef DWORD thread_return_status;
#else
    typedef std::mutex mutex_type;
    typedef std::thread thread_type;
    typedef unsigned int thread_return_status;
#endif

    typedef thread_return_status (* threading_func_type)(void *);
    thread_type spawn_thread(threading_func_type f, void *arg=nullptr);
    void join_thread(thread_type &thread);
    void create_mutex(mutex_type *m);
    bool lock_mutex(mutex_type &mutex, threading_func_type f, void *arg=nullptr);
}


#endif/* C129A486_0FCC_42AC_9413_6ABF991DDB75 */

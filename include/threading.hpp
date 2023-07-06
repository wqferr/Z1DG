#ifndef C129A486_0FCC_42AC_9413_6ABF991DDB75
#define C129A486_0FCC_42AC_9413_6ABF991DDB75

#include "osdetect.hpp"
#include <functional>

#ifdef OS_Windows
#include <windows.h>
#else
#include <thread>
#include <mutex>
#endif

namespace z1dg {
#ifdef OS_Windows
    typedef HANDLE mutex_type;
    typedef HANDLE thread_type;
    typedef LPTHREAD_START_ROUTINE threading_func_type;
#else
    typedef std::mutex mutex_type;
    typedef std::thread thread_type;
    typedef std::function<int(void *)> threading_func_type;
#endif

    thread_type spawn_thread(z1dg::threading_func_type f, void *arg=nullptr);
    void join_thread(z1dg::thread_type &thread);
    void create_mutex(mutex_type &m);
    bool lock_mutex(z1dg::mutex_type &mutex, z1dg::threading_func_type f, void *arg=nullptr);
}


#endif/* C129A486_0FCC_42AC_9413_6ABF991DDB75 */

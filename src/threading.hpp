#ifndef C129A486_0FCC_42AC_9413_6ABF991DDB75
#define C129A486_0FCC_42AC_9413_6ABF991DDB75

#include "osdetect.hpp"
#include <functional>

namespace z1dg {

#ifdef OS_Windows
    #include <windows.h>
    typedef HANDLE mutex_type;
    typedef HANDLE thread_type;
    typedef LPTHREAD_START_ROUTINE threading_func_type;
#else
    #include <mutex>
    #include <thread>
    typedef std::mutex mutex_type;
    typedef std::thread thread_type;
    typedef std::function<int, void *> threading_func_type;
#endif
    thread_type spawn_thread(threading_func_type f, void *arg=nullptr);
    void join_thread(thread_type &thread);
    bool lock_mutex(mutex_type &mutex, threading_func_type f, void *arg=nullptr);
}


#endif/* C129A486_0FCC_42AC_9413_6ABF991DDB75 */

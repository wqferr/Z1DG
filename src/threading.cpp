#include "threading.hpp"

namespace z1dg {
    thread_type spawn_thread(threading_func_type f, void *arg) {
        #ifdef OS_Windows
            DWORD thread_id;
            return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)f, arg, 0, &thread_id);
        #else
            return std::thread(f, arg);
        #endif
    }

    void join_thread(thread_type &thread) {
        #ifdef OS_Windows
            WaitForSingleObject(thread, INFINITE);
        #else
            thread.join();
        #endif
    }

    void create_mutex(mutex_type *m) {
        #ifdef OS_Windows
            *m = CreateMutex(NULL, FALSE, NULL);
        #else
            // nop
        #endif
    }

    bool lock_mutex(mutex_type &mutex, threading_func_type f, void *arg) {
        #ifdef OS_Windows
            if (WaitForSingleObject(mutex, INFINITE) == WAIT_OBJECT_0) {
                __try {
                    f(arg);
                } __finally {
                    ReleaseMutex(mutex);
                    return TRUE;
                }
            }
            return FALSE;
        #else
            std::lock_guard<mutex_type> lock(mutex);
            f(arg);
            return true;
        #endif
    }
}
#if defined(_WIN64) || defined(_WIN32)
    #include <windows.h>

    __attribute__((constructor))
    static void shut_windows_yapping_up() {
        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    }
#endif

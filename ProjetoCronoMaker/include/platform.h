#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #include <io.h>
    #define SLEEP_MS(ms) Sleep(ms)
    #define DIR_SEPARATOR '\\'
    #define mkdir(dir) _mkdir(dir)
    #define access(path, mode) _access(path, mode)
    #define ACCESS_MODE 0
#else
    #include <unistd.h>
    #include <sys/select.h>
    #include <sys/stat.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
    #define DIR_SEPARATOR '/'
    #define ACCESS_MODE F_OK
#endif

#endif
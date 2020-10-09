#ifndef __CONSOLE_COLORS_H__
#define __CONSOLE_COLORS_H__

// the following snippet of code detects the current OS and
// defines the appropriate macro that is used to wrap some
// platform specific things
#if defined(_WIN32) || defined(_WIN64)
#   define __OS_WINDOWS__
#elif defined(__APPLE__)
#   define __OS_MACOS__
#elif defined(__unix__) || defined(__unix)
#   define __OS_LINUX__
#else
#   error unsupported platform
#endif


// This headers provides the `isatty()`/`fileno()` functions,
// which are used for testing whether a standart stream refers
// to the terminal. As for Windows, we also need WinApi funcs
// for changing colors attributes of the terminal.
#if defined(__OS_MACOS__) || defined(__OS_LINUX__)
#   include <unistd.h>
#elif defined(__OS_WINDOWS__)
#   include <io.h>
#   include <windows.h>
#endif

#include <stdio.h>

namespace console_colors {
    static const char* RESET       = "\033[0m";
    static const char* BLACK       = "\033[30m";        /* Black */
    static const char* RED         = "\033[31m";        /* Red */
    static const char* GREEN       = "\033[32m";        /* Green */
    static const char* YELLOW      = "\033[33m";        /* Yellow */
    static const char* BLUE        = "\033[34m";        /* Blue */
    static const char* MAGENTA     = "\033[35m";        /* Magenta */
    static const char* CYAN        = "\033[36m";        /* Cyan */
    static const char* WHITE       = "\033[37m";        /* White */
    static const char* BOLDBLACK   = "\033[1m\033[30m"; /* Bold Black */
    static const char* BOLDRED     = "\033[1m\033[31m"; /* Bold Red */
    static const char* BOLDGREEN   = "\033[1m\033[32m"; /* Bold Green */
    static const char* BOLDYELLOW  = "\033[1m\033[33m"; /* Bold Yellow */
    static const char* BOLDBLUE    = "\033[1m\033[34m"; /* Bold Blue */
    static const char* BOLDMAGENTA = "\033[1m\033[35m"; /* Bold Magenta */
    static const char* BOLDCYAN    = "\033[1m\033[36m"; /* Bold Cyan */
    static const char* BOLDWHITE   = "\033[1m\033[37m"; /* Bold White */
};


#undef __OS_WINDOWS__
#undef __OS_MACOS__
#undef __OS_LINUX__

#endif
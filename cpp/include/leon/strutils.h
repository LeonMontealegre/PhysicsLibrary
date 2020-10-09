#ifndef __STRUTILS_H__
#define __STRUTILS_H__

#include <string>
#include <string.h>
#include <stdio.h>

#include "utils.h"

template<typename... Args>
std::string format(const std::string& s, Args&&... args) {
    uint N = snprintf(NULL, 0, s.c_str(), args...);
    char* buf = new char[N+1];
    snprintf(buf, N+1, s.c_str(), args...);
    std::string result(buf);
    delete [] buf;
    return result;
}

#endif
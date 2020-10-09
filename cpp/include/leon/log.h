#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include "console_colors.h"

#define LOG_LEVEL 2

#if LOG_LEVEL >= 0
    #define log_e(s, ...) {fprintf(stderr, "%sERROR:%s ", console_colors::RED, console_colors::RESET); fprintf(stderr, s, ##__VA_ARGS__);}
#else
    #error LOG_LEVEL must be between [0, 2]!
#endif

#if LOG_LEVEL >= 1
    #define log_w(s, ...) {printf("%sWARN:%s ", console_colors::YELLOW, console_colors::RESET); printf(s, ##__VA_ARGS__);}
#else
    #define log_w(s, ...);
#endif

#if LOG_LEVEL >= 2
    #define log_i(s, ...)   printf(s, ##__VA_ARGS__)
#else
    #define log_i(s, ...);
#endif

#if LOG_LEVEL >= 3
    #error LOG_LEVEL must be between [0, 2]!
#endif


#endif
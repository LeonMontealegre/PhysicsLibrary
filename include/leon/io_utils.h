#ifndef __IO_UTILS_H__
#define __IO_UTILS_H__

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

std::string load_file_as_string(const char* file) {
    std::ifstream fs(file);
    if (fs.fail()) {
        fprintf(stderr, "Failed to open file: '%s'!\n", file);
        exit(EXIT_FAILURE);
    }
    std::stringstream buf;
    buf << fs.rdbuf();
    // std::string contents((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
    fs.close();
    return buf.str();
}

#endif
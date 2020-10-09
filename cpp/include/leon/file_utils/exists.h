#ifndef __LEON_FILE_UTILS_EXISTS_H__
#define __LEON_FILE_UTILS_EXISTS_H__

#include <sys/types.h>
#include <sys/stat.h>
#include "../types.h"
#include "../log.h"

namespace FileUtils {

    bool exists(c_str path) {
        struct stat info;
        if (stat(path, &info) != 0)
            return false;
        else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows
            return true;
        else
            return false;
    }

};

#endif
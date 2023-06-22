//
// Created by 艾乐乐 on 2023/6/20.
//

#include "file_util.h"

int util_file_exists(const char* file_path) {
    DWORD file_attributes = GetFileAttributes(file_path);
    if (file_attributes == INVALID_FILE_ATTRIBUTES) {
        return 0;
    }
    return !(file_attributes & FILE_ATTRIBUTE_DIRECTORY);
}
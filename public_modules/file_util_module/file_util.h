//
// Created by 艾乐乐 on 2023/6/20.
//

#ifndef AIRLINEBOOKINGSYSTEM_FILE_UTIL_H
#define AIRLINEBOOKINGSYSTEM_FILE_UTIL_H

#include <windows.h>

/**
 * 判断文件是否存在
 * @param file_path 文件路径 例如 "C:\\a.txt"
 * @return 存在返回 1，否则返回 0
 */
int util_file_exists(const char* file_path);

#endif //AIRLINEBOOKINGSYSTEM_FILE_UTIL_H

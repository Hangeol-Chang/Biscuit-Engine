#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <string>
#include <functional>
#include <iostream>

// 문자열을 해싱하는 함수
size_t hashStr(const std::string& str) {
    return std::hash<std::string>{}(str);
}

#endif  // STRING_HELPER_H
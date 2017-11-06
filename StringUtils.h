//
// Created by root on 11/6/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_STRINGUTILS_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_STRINGUTILS_H

#include <iostream>
#include <algorithm>

class StringUtils {
public:
// trim from start (in place)
    static void ltrim(std::string &s);

// trim from end (in place)
    static void rtrim(std::string &s);

// trim from both ends (in place)
    static void trim(std::string &s);

// trim from start (copying)
    static std::string ltrim_copy(std::string s);

// trim from end (copying)
    static std::string rtrim_copy(std::string s);

// trim from both ends (copying)
    static std::string trim_copy(std::string s);

    static std::string replace(std::string subject, const std::string& search, const std::string& replace);

    static std::string replaceFirst(std::string subject, const std::string& search, const std::string& replace);
};

#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_STRINGUTILS_H

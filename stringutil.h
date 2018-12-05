#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include "config.h"
#include <string>
namespace violet {
    class StringUtil {
        public:
            static void wstring_to_string(std::wstring& wstr,std::string& str);
            static void string_to_wstring(std::string& str,std::wstring& wstr);
    };

}

#endif

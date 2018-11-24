#include "stringutil.h"

namespace violet {

void StringUtil::wstring_to_string(std::wstring& wstr,std::string& str) {
    wchar_t* t = (wchar_t*)wstr.c_str();
    DWORD num = ::WideCharToMultiByte(CP_OEMCP,NULL,t,-1,NULL,0,NULL,FALSE);
    char* buf;
    buf = new char[num];
    ::WideCharToMultiByte(CP_ACP,NULL,t,-1,buf,num,NULL,FALSE);
    str = buf;
    delete buf;
}
void StringUtil::string_to_wstring(std::string& str,std::wstring& wstr){
    char* t = (char*)str.c_str();
    DWORD num = ::MultiByteToWideChar(CP_OEMCP, 0, (LPCSTR)t, str.size(), 0, 0);  
    wchar_t* wbuf;
    wbuf = new wchar_t[num+1];
    wbuf[num] = 0;
    ::MultiByteToWideChar(CP_ACP, 0,(LPCSTR)t, str.size(), wbuf, num);
    wstr = wbuf;
    delete wbuf;
}

}

#include <string>

#include <objbase.h>

// violet::UUIDGen

namespace violet {
    /*
    UUIDGen class is used to generate a identifier string.
    */
    class UUIDGen {
        public:
            std::string Gen() {
                GUID guid={0};
                char buf[64]={0};
                CoCreateGuid(&guid);
                _snprintf_s(buf, sizeof(buf),
                        "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                        guid.Data1, guid.Data2, guid.Data3,
                        guid.Data4[0], guid.Data4[1],
                        guid.Data4[2], guid.Data4[3],
                        guid.Data4[4], guid.Data4[5],
                        guid.Data4[6], guid.Data4[7]);
                return std::string(buf);
            }
    };
}
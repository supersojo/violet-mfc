#ifndef VFILE_H
#define VFILE_H
#include <string>
namespace violet {
    class VFile {
        public:
            virtual std::string GetFileName() = 0;
            virtual std::string GetDirectory() = 0;
    };
}

#endif

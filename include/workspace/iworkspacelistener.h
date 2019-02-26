#ifndef IWORKSPACELISTENER_H
#define IWORKSPACELISTENER_H

#include "file/vfile.h"

namespace violet {
    class IWorkspaceListener {
        public:
            virtual void MustOpenFile(VFile& file) = 0;
            virtual void GraphCouldBeSaved() = 0;
            virtual void TitleChanged(std::string& title) = 0;
    };
}

#endif

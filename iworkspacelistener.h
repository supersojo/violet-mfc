#ifndef IWORKSPACELISTENER_H
#define IWORKSPACELISTENER_H

namespace violet {
    class IWorkspaceListener {
        public:
            void MustOpenFile(VFile& file) = 0;
            void GraphCouldBeSaved() = 0;
            void TitleChanged(std::string& title) = 0;
    };
}

#endif

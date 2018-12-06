#ifndef IWORKSPACE_H
#define IWORKSPACE_H
#include <string>
#include "iworkspacelistener.h"
#include "workspacepanel.h"
namespace violet {
    class IWorkspace {
        public:
            IGraphFile& GetGraphFile() = 0;
            IEditorPart& GetEditorPart9) = 0;
            ISideBar& GetSideBar() = 0;
            std::string GetTitle() = 0;
            void SetTitle(std::string& title) = 0;
            std::string GetFilePath() = 0;
            void SetFilePath(std::string& path) = 0;
            void AddListener(IWorkspaceListener& listener) = 0;
            Id& GetId() = 0;
            WorkspacePanel& GetWorkspacePanel() = 0;
            void SetWorkspacePanel(WorkspacePanel& panel) = 0;        
    };
}

#endif

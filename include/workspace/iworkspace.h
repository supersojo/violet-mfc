#ifndef IWORKSPACE_H
#define IWORKSPACE_H
#include <string>
#include "iworkspacelistener.h"
#include "workspacepanel.h"
#include "file/igraphfile.h"
#include "abstract/id.h"
namespace violet {
    class IEditorPart;
    class ISideBar;
    class WorkspacePanel;
    class IWorkspace {
        public:
            virtual IGraphFile& GetGraphFile() = 0;
            virtual IEditorPart& GetEditorPart() = 0;
            virtual ISideBar& GetSideBar() = 0;
            virtual std::string GetTitle() = 0;
            virtual void SetTitle(std::string& title) = 0;
            virtual std::string GetFilePath() = 0;
            virtual void SetFilePath(std::string& path) = 0;
            virtual void AddListener(IWorkspaceListener& listener) = 0;
            virtual abstract::Id& GetId() = 0;
            virtual WorkspacePanel& GetWorkspacePanel() = 0;
            virtual void SetWorkspacePanel(WorkspacePanel& panel) = 0;        
    };
}

#endif

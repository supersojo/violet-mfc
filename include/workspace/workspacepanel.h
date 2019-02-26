#ifndef WORKSPACEPANEL_H
#define WORKSPACEPANEL_H

#include "ui/vcomponent.h"
#include "workspace.h"

namespace violet {
    /*
    architecture dependent
    - mfc
    - win32 sdk
    - gt
    - wxwidget
    - gtk
    - ...
    */
    class Workspace;
    class IWorkspace;
    
    class WorkspacePanel : public CFrameWnd {
        public:
            WorkspacePanel();
            WorkspacePanel(Workspace& workspace);
            void PrepareLayout();
            VComponent& GetEditorPart();
            VComponent& GetSiderBar();
        private:
            VComponent* m_editorPart;
            VComponent* m_sideBar;
            
            IWorkspace* m_workspace;
    };
}

#endif

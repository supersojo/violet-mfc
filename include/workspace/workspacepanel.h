#ifndef WORKSPACEPANEL_H
#define WORKSPACEPANEL_H

#include "ui/vcomponent.h"
#include "workspace.h"
#include "graph/vrect.h"

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
    
    class WorkspacePanel : public VComponent {
        public:
            WorkspacePanel();
            WorkspacePanel(Workspace& workspace,CWnd* parent);
            WorkspacePanel(Workspace& workspace,CWnd* parent,VRect& rect);
            void PrepareLayout();
            VComponent& GetEditorPart();
            VComponent& GetSiderBar();
            afx_msg void OnPaint();
        private:
            VComponent* m_editorPart;
            VComponent* m_sideBar;
            
            IWorkspace* m_workspace;
            
            
            DECLARE_MESSAGE_MAP()
    };
}

#endif

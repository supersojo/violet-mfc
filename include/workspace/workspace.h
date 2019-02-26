#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "iworkspace.h"
#include "abstract/id.h"
#include <vector>
namespace violet {
    class IWorkspace;
    class Workspace : public IWorkspace{
        public:
            Workspace();
            /* interface from IWorkspace */
            virtual IGraphFile& GetGraphFile();
            virtual IEditorPart& GetEditorPart();
            virtual ISideBar& GetSideBar();
            virtual std::string GetTitle();
            virtual void SetTitle(std::string& title);
            virtual std::string GetFilePath();
            virtual void SetFilePath(std::string& path);
            virtual void AddListener(IWorkspaceListener& listener);
            virtual abstract::Id& GetId();
            virtual WorkspacePanel& GetWorkspacePanel();
            virtual void SetWorkspacePanel(WorkspacePanel& panel); 
            
        private:
            WorkspacePanel* m_workspacePanel;
            IGraphFile* m_graphFile;
            IEditorPart* m_editorPart;
            ISideBar* m_sideBar;
            std::string m_title;
            std::string m_filePath;
            std::vector<IWorkspaceListener*> m_listeners;
            abstract::Id m_id;
    };
}

#endif

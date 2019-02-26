#include "workspace/workspace.h"
#include "workspace/sidebar.h"
namespace violet {
    
Workspace::Workspace() {
    m_workspacePanel = nullptr;
    m_graphFile = nullptr;
    m_editorPart = nullptr;
    m_sideBar = nullptr;
}

IGraphFile& Workspace::GetGraphFile() {
    return *m_graphFile;
}

IEditorPart& Workspace::GetEditorPart() {
    if (m_editorPart==nullptr) {
        //m_editorPart = new EditorPart();
    }
    return *m_editorPart;
}

ISideBar& Workspace::GetSideBar() {
    if (m_sideBar==nullptr) {
        m_sideBar = new SideBar();
    }
    return *m_sideBar;
}

std::string Workspace::GetTitle() {
    return m_title;
}

void Workspace::SetTitle(std::string& title) {
    m_title = title;
}

std::string Workspace::GetFilePath() {
    return m_filePath;
}

void Workspace::SetFilePath(std::string& path) {
    m_filePath = path;
}

void Workspace::AddListener(IWorkspaceListener& listener) {
    m_listeners.push_back(&listener);
}

abstract::Id& Workspace::GetId() {
    return m_id;
}

WorkspacePanel& Workspace::GetWorkspacePanel() {
    if (m_workspacePanel==nullptr)
        m_workspacePanel = new WorkspacePanel(*this);
    
    return *m_workspacePanel;
}

void Workspace::SetWorkspacePanel(WorkspacePanel& panel) {
    if (m_workspacePanel!=nullptr)
        ;// memory leak
    m_workspacePanel = &panel;
}

}

#include "workspace/workspacepanel.h"
#include "workspace/isidebar.h"

namespace violet {

WorkspacePanel::WorkspacePanel() {
    m_workspace = nullptr;
    m_editorPart = nullptr;
    m_sideBar = nullptr;
}

WorkspacePanel::WorkspacePanel(Workspace& workspace) {
    m_workspace = &workspace;
    m_editorPart = nullptr;
    m_sideBar = nullptr;
}

void WorkspacePanel::PrepareLayout() {
}

VComponent& WorkspacePanel::GetEditorPart() {
    if (m_editorPart==nullptr) {
        //IEditorPart* editorPart = m_workspace->GetEditorPart();
    }
    return *m_editorPart;
}

VComponent& WorkspacePanel::GetSiderBar() {
    if (m_sideBar==nullptr) {
        ISideBar* sideBar = &(m_workspace->GetSideBar());
    }
    return *m_sideBar;
}

}

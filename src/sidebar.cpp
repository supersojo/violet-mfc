#include "workspace/workspace.h"
#include "workspace/sidebar.h"
#include "workspace/sidebarpanel.h"

namespace violet {
    
SideBar::SideBar() {
    m_sidebarPanel = nullptr;
}

void SideBar::AddElement(ISideBarElement& element,std::string& title) {
}

SideBarPanel& SideBar::GetSideBarPanel() {
    if (m_sidebarPanel==nullptr)
        m_sidebarPanel = new SideBarPanel();
    
    return *m_sidebarPanel;
}

void SideBar::SetSideBarPanel(SideBarPanel& panel) {
    m_sidebarPanel = &panel;
}

}

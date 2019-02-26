#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "isidebar.h"


namespace violet {
    class SideBarPanel;
    class ISideBarElement;
    class SideBar :public ISideBar {
        public:
            SideBar();
            virtual void AddElement(ISideBarElement& element,std::string& title);
            virtual SideBarPanel& GetSideBarPanel();
            virtual void SetSideBarPanel(SideBarPanel& panel);
        private:
            SideBarPanel* m_sidebarPanel;
            
    };
}

#endif

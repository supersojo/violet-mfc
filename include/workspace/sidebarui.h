#ifndef SIDEBARUI_H
#define SIDEBARUI_H

namespace violet {
    /*
    used for layout the sidebar element in SideBar
    */
    class SideBarUI {
        public:
            SideBarUI(SideBar& sideBar) {
                m_sideBar = &sideBar;
            }
            void InstallUI() {
            }
        private:
            SideBar* m_sideBar;
    };
}

#endif

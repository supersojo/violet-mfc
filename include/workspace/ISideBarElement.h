#ifndef ISIDEBARELEMENT_H
#defien ISIDEBARELEMENT_H

namespace violet {
    class ISideBarElement {
        /*
        panel represents the visual sidebar element
        */
        public:
            void Install(IWorkspace& workspace) = 0;
            SideBarElementPanel& GetSideBarElementPanel() = 0;
            setSideBarElementPanel(SideBarElementPanel& panel) = 0;
    };
}

#endif

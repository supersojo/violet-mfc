#ifndef ISIDEBARELEMENT_H
#define ISIDEBARELEMENT_H

#include "iworkspace.h"
//#include "sidebarpanel.h"

namespace violet {
    class ISideBarElement {
        /*
        panel represents the visual sidebar element
        */
        public:
            void Install(IWorkspace& workspace);
            //SideBarElementPanel& GetSideBarElementPanel() = 0;
            //void SetSideBarElementPanel(SideBarElementPanel& panel) = 0;
    };
}

#endif

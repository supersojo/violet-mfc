#ifndef ISIDEBAR_H
#define ISIDEBAR_H

namespace violet {
    /*
    SideBarPanel represents the view of sidebar
    
    SideBar
    +----+
    |    | SideBarElement
    +----+
    |    | ..
    +----+
    
    */
    class ISideBar {
        public:
            virtual void AddElement(ISideBarElement& element,std::string& title) = 0;
            virtual IGraphToolsBar& GetGraphToolsBar() = 0;
            virtual IColorChoiceBar GetColorChoiceBar() = 0;
            virtual SideBarPanel& GetSideBarPanel() = 0;
            virtual void SetSideBarPanel(SideBarPanel& panel) = 0;
    };
}

#endif


#ifndef IGRAPHTOOLSBAR_H
#define IGRAPHTOOLSBAR_H

namespace violet {
    class IGraphToolsBar {
        /*
        */
        public:
            void AddTool(INode& node,std::string& title) = 0;
            void SelectNextTool() = 0;
            void SelectPreviousTool() = 0;
            void Reset() = 0;
            void AddListener(IGraphToolsBarListener& listener) = 0;
            void RemoveListener(IGraphToolsBarListener& listener) = 0;
            void AddMouseListener(MouseListener& listener) = 0;
            void RemoveMouseListener(MouseListener& listener) = 0;
    };
}


#endif

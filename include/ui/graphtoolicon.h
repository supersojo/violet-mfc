#ifndef GRAPHTOOLICON_H
#define GRAPHTOOLICON_H
#include "vicon.h"
#include "graphtool.h"

namespace violet {
    class GraphToolIcon : public VIcon {
        public:
            GraphToolIcon(GraphTool& graphTool) {
                m_graphTool = &graphTool;
            }
            virtual void DrawIcon(VContext& context,int x,int y){
                
            }
            virtual int GetIconWidth() {
                return GraphTool::ICON_SIZE;
            }
            virtual int GetIconHeight() {
                return GraphTool::ICON_SIZE;
            }
        private:
            GraphToolIcon(){}// disallow default construct
            GraphTool* m_graphTool;
    };
}

#endif

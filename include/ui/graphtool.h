#ifndef GRAPHTOOL_H
#define GRAPHTOOL_H
#include<string>
#include "iedge.h"
#include "inode.h"
#include "vicon.h"

namespace violet {
    class GraphTool {
        public:
            GraphTool() {
                m_edge == nullptr;
                m_node = nullptr;
                m_isNode = false;
                m_isEdge = false;
                m_icon = GraphToolIcon(*this);
            }
            GraphTool(IEdge& edge,std::string& label) {
                m_edge = &edge;
                m_node = nullptr;
                m_label = label;
                m_isNode = false;
                m_isEdge = true;
                m_icon = new GraphToolIcon(*this);
            }
            GraphTool(INode& node,std::string& label) {
                m_node = &node;
                m_edge = nullptr;
                m_label = label;
                m_isNode = true;
                m_isEdge = false;
                m_icon = new GraphToolIcon(*this);
            }
            ~GraphTool() {
                if (m_icon)
                    delete m_icon;
            }
            static const int ICON_SIZE = 20;
            static const int OFFSET = 4;
        private:
            VIcon* m_icon;
            IEdge* m_edge;
            INode* m_node;
            bool m_isNode;
            bool m_isEdge;
            std::string m_label;
    };
}
#endif

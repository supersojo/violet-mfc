#ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H
#include <vector>
#include "igraph.h"
#include "../graph/vrect.h"

/*
 * AbstractGrapg is the base graph class.
 */
namespace violet {
    class INode;
    class IEdge;
    class VRect;
    namespace abstract {
        class AbstractGraph : public IGraph {
            public:
                AbstractGraph();
                virtual ~AbstractGraph() {
                }
                /* IGraph interface */
                virtual std::vector<INode*>& GetNodePrototypes() = 0;
                virtual std::vector<IEdge*>& GetEdgePrototypes() = 0;
                virtual std::vector<INode*> GetAllNodes();
                virtual std::vector<IEdge*> GetAllEdges();
                
                virtual void RemoveEdge(IEdge &edge);
                virtual void RemoveNode(INode &node);
                
                virtual bool AddNode(INode& node,VPoint& point);
                
                virtual bool Connect(IEdge& edge,INode& start,VPoint& startLocation,
                                                 INode& end,VPoint& endLocation,
                                                 VPoint transitionPoints[]);
                
                virtual INode& FindNode(Id& id);
                virtual INode& FindNode(VPoint& point);
                
                virtual IEdge& FindEdge(Id& id);
                virtual IEdge& FindEdge(VPoint& point);
                
                virtual void Draw(VContext& context);
                
                virtual VRect GetClipBounds();
                virtual void SetBounds(VRect& rect);
                
                virtual IGridSticker& GetGridSticker();
                virtual void SetGridSticker(IGridSticker& gridSticker);
            private:
                void UpdateMinBounds(VRect& b);
                bool HasNode(INode& node);
                std::vector<INode*> m_nodes;
                std::vector<IEdge*> m_edges;
                VRect m_minBounds;
                IGridSticker* m_gridSticker;
        };
    }
}
#endif

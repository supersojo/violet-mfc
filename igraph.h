#ifndef IGRAPH_H
#define IGRAPH_H

#include <list>
#include <set>

// prototypes
namespace violet {
    class VPoint;
    class VRect;
    class VContext;
    namespace abstract {
        class Id;
        class INode;
        class IEdge;
        class IGridSticker;
    }
}

namespace violet {
    namespace abstract {
        class IGraph {
            public:
                virtual std::list<INode>& GetNodePrototypes() = 0;
                virtual std::list<IEdge>& GetEdgePrototypes() = 0;
                virtual std::set<INode>& GetAllNodes() = 0;
                virtual std::set<IEdge>& GetAllEdges() = 0;
                
                virtual void RemoveEdge(IEdge &edge) = 0;
                virtual void RemoveNode(INode &node) = 0;
                
                virtual bool AddNode(INode& node,VPoint& point) = 0;
                
                virtual bool Connect(IEdge& edge,INode& start,VPoint& startLocation,
                                                 INode& end,VPoint& endLocation,
                                                 VPoint transitionPoints[]) = 0;
                
                virtual INode& FindNode(Id& id) = 0;
                virtual INode& FindNode(VPoint& point) = 0;
                
                virtual IEdge& FindEdge(Id& id) = 0;
                virtual IEdge& FindEdge(VPoint& point) = 0;
                
                virtual void Draw(VContext& context) = 0;
                
                virtual VRect& GetClipBounds() = 0;
                virtual void SetBounds(VRect& rect) = 0;
                
                virtual IGridSticker& GetGridSticker() = 0;
                virtual void SetGridSticker(IGridSticker& gridSticker) = 0;
        };
    }
}
#endif

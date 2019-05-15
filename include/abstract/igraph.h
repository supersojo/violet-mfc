#ifndef IGRAPH_H
#define IGRAPH_H

#include <vector>

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
                /*
                 * GetNodePrototypes:
                 * Return all node types
                 */
                virtual std::vector<INode*>& GetNodePrototypes() = 0;
                /*
                 * GetEdgePrototypes:
                 * Return all edge types.
                 */
                virtual std::vector<IEdge*>& GetEdgePrototypes() = 0;
                /*
                 * GetAllNodes:
                 * Retuen all nodes in the graph
                 */
                virtual std::vector<INode*> GetAllNodes() = 0;
                /*
                 * GetAllEdges:
                 * Return all edges in the graph.
                 */
                virtual std::vector<IEdge*> GetAllEdges() = 0;
                
                /*
                 * RemoveNode RemoveEdge
                 * Remove node or edge from graph
                 */
                virtual void RemoveEdge(IEdge &edge) = 0;
                virtual void RemoveNode(INode &node) = 0;
                
                /*
                 * AddNode:
                 * Add node to graph, point is absolute location.
                 */
                virtual bool AddNode(INode& node,VPoint& point) = 0;
                
                /*
                 * Connect:
                 * Connect start and end node.
                 * startLocation and endLocation is relative location.
                 */
                virtual bool Connect(IEdge& edge,INode& start,VPoint& startLocation,
                                                 INode& end,VPoint& endLocation,
                                                 VPoint transitionPoints[]) = 0;
                /*
                 * FindNode:
                 * return node with id or location
                 */
                virtual INode& FindNode(Id& id) = 0;
                virtual INode& FindNode(VPoint& point) = 0;
                
                /*
                 * FindEdge:
                 * Return edge with id or location
                 */
                virtual IEdge& FindEdge(Id& id) = 0;
                virtual IEdge& FindEdge(VPoint& point) = 0;
                
                virtual void Draw(VContext& context) = 0;
                /*
                 * GetClipBounds:
                 * Return bounds of the graph
                 */
                virtual VRect GetClipBounds() = 0;
                virtual void SetBounds(VRect& rect) = 0;
                
                virtual IGridSticker& GetGridSticker() = 0;
                virtual void SetGridSticker(IGridSticker& gridSticker) = 0;
        };
    }
}
#endif

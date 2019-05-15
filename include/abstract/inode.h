#ifndef INODE_H
#define INODE_H

/*
 *
 * The INode interface for all nodes need to implement.
 */
#include <list>
#include "iidentifiable.h"

namespace violet {
    
    class VPoint;
    class VRect;
    class VContext;
    
    namespace abstract {
        class IEdge;
        class IGraph;
    }
}

namespace violet {
    namespace abstract {
        class INode : public IIdentifiable{
            public:
                virtual void Reconstruction() = 0;
                /*
                 * AddConnection:
                 * Each node can connect to many nodes, So it will add edge.
                 * Be sure the node is one if the nodes(start or end) of the edge.
                 */
                virtual bool AddConnection(IEdge& edge) = 0;
                /*
                 * RemoveConnection:
                 * the mililar logic as above.
                 */
                virtual void RemoveConnection(IEdge& edge) = 0;
                /*
                 * For complex graph, node may have child node.
                 * point is the relative location to the parent node.
                 */
                virtual bool AddChild(INode& node, VPoint& point) = 0;
                /*
                 * AddChild by some index and update relative localtion automatically
                 */
                virtual bool AddChild(INode& node, int index) = 0;
                /*
                 * Remove child node from the parent node.
                 * If node doesn't belong to child nodes, just do nothing.
                 */
                virtual void RemoveChild(INode& node) = 0;
                /*
                 * GetChildren:
                 * Return all child node in the parent node.
                 */
                virtual std::list<INode*>& GetChildren() = 0;
                /*
                 * GetParent:
                 * Return parent node if we have.
                 */
                virtual INode& GetParent() = 0;
                /*
                 * GetParents:
                 * Return the nodes from the node to top parent node.
                 */
                virtual std::list<INode*>& GetParents() = 0;
                /*
                 * SetParent:
                 */
                virtual void SetParent(INode& parent) = 0;
                /*
                 * SetGraph
                 */
                virtual void SetGraph(IGraph& g) = 0;
                virtual IGraph& GetGraph() = 0;
                
                virtual void Translate(double dx,double dy) = 0;
                
                virtual bool Contains(VPoint& point) = 0;
                /*
                 * GetConnectionPoint:
                 * the node should be start or end node of the edge.
                 * calculate localtion in the node.
                 */
                virtual VPoint GetConnectionPoint(IEdge&edge) = 0;
                /*
                 * SetLocation:
                 * Set location relative the parent node.
                 * So if no parent node, it is absolute location.
                 */
                virtual void SetLocation(VPoint& point) = 0;
                /*
                 * GetLocation:
                 * Return relative location.
                 * If no parent node then it is absolute localtion
                 */
                virtual VPoint& GetLocation() = 0;
                /*
                 * GetLocationOnGraph:
                 * If no parent the relative location is equal to the absolute localtion.
                 * else need calculate  from parent location.
                 */
                virtual VPoint GetLocationOnGraph() = 0;
                /*
                 * GetBounds:
                 * Return relative location and width height.
                 */
                virtual VRect GetBounds() = 0;
                
                virtual void Draw(VContext& context) = 0;
                /*
                 * When draw node may need deepth info.
                 */
                virtual int GetZ() = 0;
                virtual void SetZ(int z) = 0;
                /*
                 * GetToolTip:
                 * Return help info string.
                 */
                virtual std::string GetToolTip() = 0;
                /*
                 * Clone:
                 * Return a new node with same info.
                 */
                virtual INode& Clone() = 0;
        };
    }

}

#endif


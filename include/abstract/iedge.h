#ifndef IEDGE_H
#define IEDGE_H
#include <vector>
#include "iidentifiable.h"

/*
 * All proto classes used by the IEdge class
 */
namespace violet {
    class VPoint;
    class VLine;
    class VRect;
    class VContext;
}
namespace violet {
    namespace abstract {
        class INode;
        class Direction;
    }
}

// violet::abstract::IIdentifiable
namespace violet {
    namespace abstract {
        /*
        The interface is for class that can be identifiable.
        */
        class IEdge : public IIdentifiable {
            public:
                virtual void Reconstruction() = 0;
                /*
                 * SetStartNode:
                 * Each edge has a start node and end node. This function is used to set start node of the edge.
                 */
                virtual void SetStartNode(INode& startingNode) = 0;
                /*
                 * GetStartNode
                 * Return the start node of the edge.
                 */
                virtual INode& GetStartNode() = 0;
                /*
                 * See SetStartNode.
                 */
                virtual void SetEndNode(INode& endingNode) = 0;
                /*
                 * See GetStartNode.
                 */
                virtual INode& GetEndNode() = 0;
                /*
                 * SetStartLocation:
                 * Each edge has a start node.
                 * So this is relative location to the start node.
                 *(0,0) +------>
                 *      | (x,y)
                 *      V
                 */
                virtual void SetStartLocation(VPoint& startingLocaltion) = 0;
                /*
                 * See SetStartLocation.
                 */
                virtual VPoint& GetStartLocation() = 0;
                /*
                 * GetStartLocationOnGraph:
                 * Return the location on the graph.
                 * So it will know the start node location and relate location.
                 */
                virtual VPoint  GetStartLocationOnGraph() = 0;
                /*
                 * See SetStartLocation.
                 */
                virtual void SetEndLocation(VPoint& endingLocation) = 0;
                /* 
                 * See GetStartLocation.
                 */
                virtual VPoint& GetEndLocation() = 0;
                /*
                 * See GetStartLocationOnGraph.
                 */
                virtual VPoint  GetEndLocationOnGraph() = 0;
                /*
                 * SetTransitionPoints:
                 * From start node to end node make a path.
                 * Using SetTransitionPoints to set middle points in the path manually.
                 */
                virtual void SetTransitionPoints(VPoint transitionPoints[]) = 0;
                /*
                 * GetTransitionPoints:
                 * Return the points
                 */
                virtual std::vector<VPoint*>& GetTransitionPoints() = 0;
                /*
                 * Check if transition points are supported or not
                 */
                virtual bool IsTransitionPointsSupported() = 0;
                /*
                 * ClearTransitionPoints:
                 * clear the transition points
                 */
                virtual void ClearTransitionPoints() = 0;
                /*
                 * GetConnectionPoints:
                 * Return the points location on graph between start node and end node.
                 */
                virtual VLine GetConnectionPoints() = 0;
                /*
                 * Check point in the path of the edge
                 */
                virtual bool Contains(VPoint& point) = 0;
                /*
                 * GetBounds:
                 * Return location of start and width height information.
                 * +------->
                 * |    \ 
                 * V     \
                 */
                virtual VRect GetBounds() = 0;
                /*
                 * GetDirection:
                 * Return direction to start node or end node.
                 * node must be start node or end node.
                 */
                virtual Direction GetDirection(INode& node) = 0;
                /*
                 * Draw:
                 * draw the edge on graph
                 */
                virtual void Draw(VContext& context) = 0;
                /*
                 *
                 * GetToolTip
                 * Return help info.
                 */
                virtual std::string GetToolTip() = 0;
                /*
                 * Clone:
                 * Create a new edge with same info.
                 */
                virtual IEdge& clone() = 0;
                
        };
    }
}
#endif

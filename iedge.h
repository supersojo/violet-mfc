#ifndef IEDGE_H
#define IEDGE_H

#include "iidentifiable.h"


namespace violet {
    class VPoint;
    class VLine;
    class VRect;
    class VContext;
}
namespace violet {
    namespace abstract {
        class INode;
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
                virtual void SetStartNode(INode& startingNode) = 0;
                virtual INode& GetStartNode() = 0;
                virtual void SetEndNode(INode& endingNode) = 0;
                virtual INode& GetEndNode() = 0;
                virtual void SetStartLocation(VPoint& startingLocaltion) = 0;
                virtual VPoint& GetStartLocation() = 0;
                virtual VPoint& GetStartLocationOnGraph() = 0;
                virtual void SetEndLocation(VPoint& endingLocation) = 0;
                virtual VPoint& GetEndLocation() = 0;
                virtual VPoint& GetEndLocationOnGraph() = 0;
                virtual void SetTransitionPoints(VPoint transitionPoints[]) = 0;
                virtual VPoint* GetTransitionPoints() = 0;
                virtual bool IsTransitionPointsSupported() = 0;
                virtual void ClearTransitionPoints() = 0;
                virtual VLine& GetConnectionPoints() = 0;
                virtual bool Contains(VPoint& point) = 0;
                virtual VRect& GetBounds() = 0;
                //virtual Direction& GetDirection(INode& node) = 0;
                virtual void Draw(VContext& context) = 0;
                virtual std::string GetToolTip() = 0;
                virtual IEdge& clone() = 0;
                
        };
    }
}
#endif

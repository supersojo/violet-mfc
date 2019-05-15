#ifndef ABSTRACTEDGE_H
#define ABSTRACTEDGE_H
#include <vector>
#include "iedge.h"
#include "../graph/vpoint.h"
/*
 * All proto classes.
 */
namespace violet {
    class VPoint;
    namespace abstract {
        class INode;
        class IGraph;
        class Id;
    }
}
/*
 * AbstractEdge implement the base edge class
 *
 */
namespace violet{
    namespace abstract {
        
        class AbstractEdge : public IEdge {
            public:
                AbstractEdge();
                virtual ~AbstractEdge();
                /* IIdentifiable interface */
                virtual Id& GetId();
                virtual void SetId(Id& id);
                virtual int GetRevision();
                virtual void SetRevision(int rev);
                virtual void IncrementRevision();
                /* IEdge interface */
                virtual void Reconstruction();
                virtual void SetStartNode(INode& startingNode);
                virtual INode& GetStartNode();
                virtual void SetEndNode(INode& endingNode);
                virtual INode& GetEndNode();
                virtual void SetStartLocation(VPoint& startingLocation);
                virtual VPoint& GetStartLocation();
                virtual VPoint GetStartLocationOnGraph();
                virtual void SetEndLocation(VPoint& endingLocation);
                virtual VPoint& GetEndLocation();
                virtual VPoint  GetEndLocationOnGraph();
                virtual void SetTransitionPoints(VPoint transitionPoints[]);
                virtual std::vector<VPoint*>& GetTransitionPoints();
                virtual bool IsTransitionPointsSupported();
                virtual void ClearTransitionPoints();
                virtual VLine GetConnectionPoints();
                virtual bool Contains(VPoint& point);
                virtual VRect GetBounds();
                virtual Direction GetDirection(INode& node);
                virtual void Draw(VContext& context);
                virtual std::string GetToolTip();
                virtual IEdge& clone();
                /* others */
                virtual void BeforeReconstruction() {
                }
                virtual void AfterReconstruction() {
                    RefreshContactPoints();
                }
                virtual void CreateContentStructure();
                virtual void UpdateContactPoints();
            private:
                void RefreshContactPoints();
                Id m_id;
                int m_revision;
                INode* m_startNode;
                INode* m_endNode;
                VPoint m_startLocation;
                VPoint m_endLocation;
                std::vector<VPoint*> m_transitionPoints;
            protected:
                std::vector<VPoint*> m_contactPoints;
        };
    
    }


}

#endif

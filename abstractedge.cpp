#include "abstractedge.h"
#include "inode.h"
#include "vline.h"
#include "vpoint.h"
#include "vrect.h"
#include "direction.h"
namespace violet {
    namespace abstract {
        AbstractEdge::AbstractEdge() {
            m_revision = 0;
            m_startNode = nullptr;
            m_endNode = nullptr;
            m_startLocation.SetValid(false);
            m_endLocation.SetValid(false);
        }
        AbstractEdge::~AbstractEdge() {
        }
        /* IIdentifiable interface */
        Id& AbstractEdge::GetId() {
            return (m_id);
        }
        void AbstractEdge::SetId(Id& id) {
            m_id.SetValue(id.GetValue());
        }
        int AbstractEdge::GetRevision() {
            return m_revision;
        }
        void AbstractEdge::SetRevision(int rev) {
            m_revision = rev;
        }
        void AbstractEdge::IncrementRevision() {
            m_revision++;
        }
        /* IEdge interface */
        void AbstractEdge::Reconstruction() {
            BeforeReconstruction();
            CreateContentStructure();
            AfterReconstruction();
        }
        void AbstractEdge::SetStartNode(INode& startingNode) {
            m_startNode = &startingNode;
            RefreshContactPoints();
        }
        INode& AbstractEdge::GetStartNode() {
            return *m_startNode;
        }
        void AbstractEdge::SetEndNode(INode& endingNode) {
            m_endNode = &endingNode;
            RefreshContactPoints();
        }
        INode& AbstractEdge::GetEndNode() {
            return *m_endNode;
        }
        void AbstractEdge::SetStartLocation(VPoint& startingLocation) {
            m_startLocation = startingLocation;
            RefreshContactPoints();
        }
        VPoint& AbstractEdge::GetStartLocation() {
            return m_startLocation;
        }
        VPoint AbstractEdge::GetStartLocationOnGraph() {
            if (m_startNode==nullptr || m_startLocation.GetValid()==false)
                return VPoint(0,0,false);
            VPoint nodeLocationOnGraph = m_startNode->GetLocationOnGraph();
            return VPoint(nodeLocationOnGraph.GetX() + m_startLocation.GetX(),
                          nodeLocationOnGraph.GetY() + m_startLocation.GetY());
        }
        void AbstractEdge::SetEndLocation(VPoint& endingLocation) {
            m_endLocation = endingLocation;
            RefreshContactPoints();
        }
        VPoint& AbstractEdge::GetEndLocation() {
            return m_endLocation;
        }
        VPoint AbstractEdge::GetEndLocationOnGraph() {
            if (m_endNode==nullptr || m_endLocation.GetValid()==false)
                return VPoint(0,0,false);
            VPoint nodeLocationOnGraph = m_endNode->GetLocationOnGraph();
            return VPoint(nodeLocationOnGraph.GetX() + m_endLocation.GetX(),
                          nodeLocationOnGraph.GetY() + m_endLocation.GetY());
        }
        void AbstractEdge::SetTransitionPoints(VPoint transitionPoints[]) {
            if (transitionPoints==nullptr)
                return;
            int n = sizeof(transitionPoints)/sizeof(VPoint);
            // clear vpoints already in vector ????
            m_transitionPoints.clear();
            for (int i=0;i<n;i++)
                m_transitionPoints.push_back(&transitionPoints[i]);
            RefreshContactPoints();
        }
        std::vector<VPoint*>& AbstractEdge::GetTransitionPoints() {
            return m_transitionPoints;
        }
        bool AbstractEdge::IsTransitionPointsSupported() {
            return false;
        }
        void AbstractEdge::ClearTransitionPoints() {
            m_transitionPoints.clear();
        }
        VLine AbstractEdge::GetConnectionPoints() {
            /*
            +--------> x
            |(0,0)
            |
            V
            y
            */
            VPoint start = m_startNode->GetLocationOnGraph();
            VPoint end = m_endNode->GetLocationOnGraph();
            VPoint relativeStart = m_startNode->GetConnectionPoint(*this);
            VPoint relativeEnd = m_endNode->GetConnectionPoint(*this);
            VPoint p1 = start+relativeStart;
            VPoint p2 = end+relativeEnd;
            // align p1 p2 ??
            return VLine(p1,p2);
        }
        bool AbstractEdge::Contains(VPoint& point) {
            return false;
        }
        VRect AbstractEdge::GetBounds() {
            /*
               \(x,y))
                \
                 \(x,y)
            */
            VLine conn = GetConnectionPoints();
            return VRect(0,
                         0,
                         abs(conn.GetStart().GetX()-conn.GetEnd().GetX()),
                         abs(conn.GetStart().GetY()-conn.GetEnd().GetY())
                    );
        }
        Direction AbstractEdge::GetDirection(INode& node) {
            VPoint start = m_startNode->GetLocationOnGraph();
            VPoint end = m_endNode->GetLocationOnGraph();
            VPoint startCenter(start.GetX()+m_startNode->GetBounds().GetSize().GetX()/2,
                               start.GetY()+m_startNode->GetBounds().GetSize().GetY()/2);
            VPoint endCenter(end.GetX()+m_endNode->GetBounds().GetSize().GetX()/2,
                             end.GetY()+m_endNode->GetBounds().GetSize().GetY()/2);
            // size()==2
            if (m_contactPoints.size()>1) {
                if (m_startNode==&node) {
                    return Direction(startCenter,*(m_contactPoints[1]));
                } else if (m_endNode==&node) {
                    return Direction(startCenter,*(m_contactPoints[m_contactPoints.size()-2]));
                }
            }
            return Direction(0,0);
            
        }
        void AbstractEdge::Draw(VContext& context) {
        }
        std::string AbstractEdge::GetToolTip() {
            return std::string("");
        }
        IEdge& AbstractEdge::clone() {
            return *this;
        }
        /* others*/
        void AbstractEdge::CreateContentStructure() {
        }
        void AbstractEdge::RefreshContactPoints() {
            if ((m_startNode!=nullptr) &&
                (m_endNode!=nullptr) &&
                (m_startLocation.GetValid()) &&
                (m_endLocation.GetValid())) {
                    UpdateContactPoints();
                }
        }
        void AbstractEdge::UpdateContactPoints() {
            for(int i=0;i<m_contactPoints.size();i++)
            {
                delete m_contactPoints[i];
            }
            m_contactPoints.clear();
            VLine connectionPoints = GetConnectionPoints();
            m_contactPoints.push_back(new VPoint(connectionPoints.GetStart()));
            m_contactPoints.push_back(new VPoint(connectionPoints.GetEnd()));
            std::cout<<"abstract edge?"<<std::endl;
        }
    }
}
#include "lineedge.h"
#include "inode.h"
#include "vcontext.h"
#include "bentstyle.h"
#include "direction.h"
#include "vline.h"

namespace violet {

void LineEdge::RebuildShape() {
                VPath* path = new VPath;
                path->MoveTo(m_contactPoints[0]->GetX(), m_contactPoints[0]->GetY());

                for (int i = 1; i < m_contactPoints.size(); ++i)
                {
                    path->LineTo(m_contactPoints[i]->GetX(), m_contactPoints[i]->GetY());
                }
                m_shape = path;
}
BentStyle& LineEdge::GetBentStyle() {
    if (m_bentStyleChoiceList->GetSelectedValue().GetStyle().compare("FREE")!=0) {
        ClearTransitionPoints();
    }
    if (m_bentStyleChoiceList->GetSelectedValue().GetStyle().compare("AUTO")!=0) {
        return m_bentStyleChoiceList->GetSelectedValue();
    }
    // auto determine bent style

    Direction startDirection = GetDirection(GetStartNode()).GetNearestCardinalDirection();
    Direction endDirection = GetDirection(GetEndNode()).GetNearestCardinalDirection();
    /* 
       ^N
     W-+-->E
       |S
    */
    if ((startDirection.Equals(Direction::NORTH)||startDirection.Equals(Direction::SOUTH)) &&
        (endDirection.Equals(Direction::NORTH)||endDirection.Equals(Direction::SOUTH))) {
        return BentStyle::VHV;
    } else if ((startDirection.Equals(Direction::NORTH)||
                startDirection.Equals(Direction::SOUTH)) &&
               (endDirection.Equals(Direction::EAST)||
                endDirection.Equals(Direction::WEST))) {
        return BentStyle::VH;
    }else if ((startDirection.Equals(Direction::EAST)||
                startDirection.Equals(Direction::WEST)) &&
               (endDirection.Equals(Direction::NORTH)||
                endDirection.Equals(Direction::SOUTH))) {
        return BentStyle::HV;
    } else if ((startDirection.Equals(Direction::EAST)||
                startDirection.Equals(Direction::WEST)) &&
               (endDirection.Equals(Direction::EAST)||
                endDirection.Equals(Direction::WEST))) {
        return BentStyle::HVH;
    }
    /* default */
    return BentStyle::STRAIGHT;
}
void LineEdge::ReloadContactPoints(std::vector<VPoint>& points) {
    /* clear old m_contactPoints */        
    for(int i=0;i<m_contactPoints.size();i++)
        delete m_contactPoints[i];
    
    m_contactPoints.clear();
    
    //update new m_contactPoints
    VPoint** ps = new VPoint*[points.size()];
    for (int i=0;i<points.size();i++)
        ps[i] = new VPoint;

    for (int i=0;i<points.size();i++) {
        *(ps[i]) = points[i];
        m_contactPoints.push_back(ps[i]);
    }
    delete[] ps;
}
void LineEdge::UpdateContactPoints() {
    if (&GetStartNode()==&GetEndNode()) {// self loop
        /*
                +----+
                |    |
        +----------+ |
        |          | |
        |          |-+
        +----------+
        */
        std::vector<VPoint> points;

        VRect nodeBounds = GetStartNode().GetBounds();
        VPoint nodeLocation = GetStartNode().GetLocationOnGraph();
        
        VPoint ps_0(nodeLocation.GetX()+nodeBounds.GetSize().GetX(),
                       nodeLocation.GetY()+nodeBounds.GetSize().GetY()/2
                       );
        VPoint ps_1(ps_0.GetX()+SELF_LOOP_GAP_X,
                    ps_0.GetY());
        VPoint ps_2(ps_1.GetX(),
                    ps_1.GetY()-nodeBounds.GetSize().GetY()-SELF_LOOP_GAP_Y);
        VPoint ps_3(ps_0.GetX()-nodeBounds.GetSize().GetX()/2,
                    ps_2.GetY());
        VPoint ps_4(ps_3.GetX(),
                    ps_2.GetY()+nodeBounds.GetSize().GetY()/2+SELF_LOOP_GAP_Y);
        
        points.push_back(ps_0);
        points.push_back(ps_1);
        points.push_back(ps_2);
        points.push_back(ps_3);
        points.push_back(ps_4);
        
        ReloadContactPoints(points);
    } else {
        // node1 to node2
        VRect startBounds = GetStartNode().GetBounds();
		
        VRect endBounds = GetEndNode().GetBounds();
		
        VPoint startLocationOnGraph = GetStartNode().GetLocationOnGraph();
		
        VPoint endLocationOnGraph = GetEndNode().GetLocationOnGraph();
		
        VPoint startCenter = startLocationOnGraph + 
                             VPoint(startBounds.GetSize().GetX()/2,
                                    startBounds.GetSize().GetY()/2);
        VPoint endCenter = endLocationOnGraph + 
                             VPoint(endBounds.GetSize().GetX()/2,
                                    endBounds.GetSize().GetY()/2);	
        std::vector<VPoint> points;
        points.push_back(startCenter);
        // add transition points
        std::vector<VPoint*> &transitionPoints = GetTransitionPoints();
        for (int i=0;i<transitionPoints.size();i++) {
            points.push_back(*(transitionPoints[i]));
        }
        points.push_back(endCenter);
        // benstyle process GetBentStyle will use m_contactPoints
        //update m_contactPoints
        ReloadContactPoints(points);
        
        points = GetBentStyle().GetPath(points);

        ReloadContactPoints(points);
        
        VLine connectionPoints = GetConnectionPoints();
        VPoint start = connectionPoints.GetStart();
        VPoint end = connectionPoints.GetEnd();
        points.clear();
        points.push_back(start);
        for (int i=0;i<transitionPoints.size();i++) {
            points.push_back(*(transitionPoints[i]));
        }
        points.push_back(end);
        
        points = GetBentStyle().GetPath(points);
        //update m_contactPoints
        ReloadContactPoints(points);
        
    }
    // after update contact points
    // rebuild shape path
    if (m_shape!=nullptr) {
        delete m_shape;
    }
    RebuildShape();
}

void LineEdge::Draw(VContext& context) {
    UpdateContactPoints();
    
    // save 
    VColor color = context.GetColor();
    VStroke stroke = context.GetStroke();
    
    
    context.Draw(GetShape());
    
    // restore
    context.SetStroke(stroke);
    context.SetColor(color);
}


}
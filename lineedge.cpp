#include "lineedge.h"
#include "inode.h"
#include "vcontext.h"
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
        VPoint** ps = new VPoint*[5];
        for (int i=0;i<5;i++)
            ps[i] = new VPoint;
        std::cout<<"lineedge draw aa"<<std::endl;
        VRect nodeBounds = GetStartNode().GetBounds();
        VPoint nodeLocation = GetStartNode().GetLocationOnGraph();
        
        *ps[0] = VPoint(nodeLocation.GetX()+nodeBounds.GetSize().GetX(),
                       nodeLocation.GetY()+nodeBounds.GetSize().GetY()/2
                       );
        *ps[1] = VPoint((*ps[0]).GetX()+SELF_LOOP_GAP_X,
                        (*ps[0]).GetY());
        *ps[2] = VPoint((*ps[1]).GetX(),
                        (*ps[1]).GetY()-nodeBounds.GetSize().GetY()-SELF_LOOP_GAP_Y);
        *ps[3] = VPoint((*ps[0]).GetX()-nodeBounds.GetSize().GetX()/2,
                        (*ps[2]).GetY());
        *ps[4] = VPoint((*ps[3]).GetX(),
                        (*ps[2]).GetY()+nodeBounds.GetSize().GetY()/2+SELF_LOOP_GAP_Y);
        
        /* reload m_contactPoints */        
        for(int i=0;i<m_contactPoints.size();i++)
            delete m_contactPoints[i];
        
        m_contactPoints.clear();
        
        m_contactPoints.push_back(ps[0]);
        m_contactPoints.push_back(ps[1]);
        m_contactPoints.push_back(ps[2]);
        m_contactPoints.push_back(ps[3]);
        m_contactPoints.push_back(ps[4]);
        
        delete[] ps;
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
        // benstyle process
        
        //update m_contactPoints
    }
    // after update contact points
    // rebuild shape path
    if (m_shape!=nullptr) {
        delete m_shape;
    }
    RebuildShape();
}

void LineEdge::Draw(VContext& context) {
    std::cout<<"lineedge draw 11"<<std::endl;
    UpdateContactPoints();
    std::cout<<"lineedge draw 22"<<std::endl;
    
    // save 
    VColor color = context.GetColor();
    VStroke stroke = context.GetStroke();
    
    
    context.Draw(GetShape());
    
    // restore
    context.SetStroke(stroke);
    context.SetColor(color);
}


}
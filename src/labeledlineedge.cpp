#define _USE_MATH_DEFINES 
#include <math.h>
#include "edge/labeledlineedge.h"
#include "abstract/direction.h"
namespace violet {
    
    void LabeledLineEdge::Draw(VContext& context) {
        if (m_startLabelChanged) {
            m_startLabel->UpdateBounds(context);
            m_startLabel->GetContent().RefreshUp();
            m_startLabelChanged = false;
        }
        if (m_centerLabelChanged) {
            m_centerLabel->UpdateBounds(context);
            m_centerLabel->GetContent().RefreshUp();
            m_centerLabelChanged = false;
        }
        if (m_endLabelChanged) {
            m_endLabel->UpdateBounds(context);
            m_endLabel->GetContent().RefreshUp();
            m_endLabelChanged = false;
        }
        ArrowHeadEdge::Draw(context);
        DrawContent(context,*m_startTextContent, 
            *m_contactPoints[0],
            *m_contactPoints[1],
            false);
            
        DrawContent(context,*m_centerTextContent, 
            *m_contactPoints[m_contactPoints.size()/2 - 1],
            *m_contactPoints[m_contactPoints.size()/2],
            true);
            
        DrawContent(context,*m_endTextContent, 
            *m_contactPoints[m_contactPoints.size()-1],
            *m_contactPoints[m_contactPoints.size()-2],
            false);
    }
    void LabeledLineEdge::DrawContent(
            VContext& context, 
            VContentText& textContent,
            VPoint& start,VPoint& end, 
            bool center) {
                VRect textBounds = textContent.GetBounds();
                Direction direction(start,end);
                Direction nearestDirection = direction.GetNearestCardinalDirection();
                double x,y;
                if (center) {
                    x = (start.GetX() + end.GetX())/2;
                    y = (start.GetY() + end.GetY())/2;
                } else {
                    x = start.GetX();
                    y = end.GetY();
                }
                if ((GetBentStyle().GetStyle().compare("FREE")==0) ||
                    (GetBentStyle().GetStyle().compare("STRAIGHT")==0)) {
                    double tan = atan2(direction.GetY(),direction.GetX());
                    /*
                    +---->
                    |         
                    |     (x,y)   <---direction
                    V
                    */
                    if (direction.GetX()<0) {
                        tan += M_PI;
                    }
                    context.Rotate(VPoint(x,y),-tan*180/M_PI);//transform
                    if (center) {
                        textContent.Draw(context,
                            VPoint(textContent.GetWidth()/2,
                            textContent.GetHeight()));
                    } else {
                        if (direction.GetX()<0) {
                            textContent.Draw(context,
                            VPoint(-LABEL_GAP-textContent.GetWidth(),
                            -textContent.GetHeight()));
                        } else {
                            textContent.Draw(context,
                            VPoint(LABEL_GAP,
                            -textContent.GetHeight()));
                        }
                    }
                    context.Rotate(VPoint(x,y),tan*180/M_PI);//restore
                } else {// bent style HV VH HVH VHV
                    if (center) {
                        if (nearestDirection.Equals(Direction::NORTH) ||
                            nearestDirection.Equals(Direction::SOUTH)) {
                            y -= textBounds.GetHeight()/2;
                        } else {
                            x -= textBounds.GetWidth()/2;
                            y -= textBounds.GetHeight();
                        }
                    } else {// no center
                        if (nearestDirection.Equals(Direction::EAST)) {
                            x += LABEL_GAP;
                            y -= textBounds.GetHeight();
                        } else if (nearestDirection.Equals(Direction::WEST)) {
                            x -= textBounds.GetWidth()+LABEL_GAP;
                            y -= textBounds.GetHeight();
                        } else if (nearestDirection.Equals(Direction::SOUTH)) {
                            y += LABEL_GAP;
                        } else if (nearestDirection.Equals(Direction::NORTH)) {
                            y -= textBounds.GetHeight()+LABEL_GAP;
                        }
                    }
                    textContent.Draw(context,VPoint(x,y));
                }
    }

}
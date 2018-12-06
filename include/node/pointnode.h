#ifndef POINTNODE_H
#define POINTNODE_H
#include <cmath>
#include "../abstract/abstractnode.h"
#include "../content/vcontentinrectangle.h"
namespace violet {
    using namespace violet::abstract;
    
    class PointNode : public AbstractNode {
        public:
            virtual bool Contains(VPoint& point) {
                double threshold = 5;
                VPoint p = GetLocation();
                double dx = p.GetX()-point.GetX();
                double dy = p.GetY()-point.GetY();
                return sqrt(dx*dx+dy*dy) < threshold;
            }
            virtual VRect GetBounds() {
                return VRect(GetLocation(),VPoint(0,0));
            }
            virtual VPoint& GetLocation() {
                if (m_tempLocation.GetValid()) 
                    return m_tempLocation;
                else 
                    return AbstractNode::GetLocation();
            }
            void SetBounds(VRect& bounds) {
                if (m_tempLocation.GetValid()) {
                    m_tempLocation = VPoint(bounds.GetLocation().GetX(),
                        bounds.GetLocation().GetY());
                }
            }
            virtual void Translate(double dx,double dy) {
                AbstractNode::Translate(dx,dy);
                m_tempLocation.SetValid(false);
            }
            virtual void CreateContentStructure() {
                VContentInShape* contentInShape = new  VContentInRectangle(*new VContentEmpty);
                SetContent(*contentInShape);
            }
            virtual void Draw(VContext& context) {
            }
            virtual std::string GetToolTip() {
                return std::string("");
            }
        private:
            VPoint m_tempLocation;
    };
}

#endif

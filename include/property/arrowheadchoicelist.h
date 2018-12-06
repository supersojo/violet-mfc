#ifndef ARROWHEADCHOICELIST_H
#define ARROWHEADCHOICELIST_H
#include "iconchoicelist.h"
#include "../abstract/arrowhead.h"
#include "../abstract/varrowhead.h"
#include "../abstract/trianglearrowhead.h"
#include "../abstract/diamondarrowhead.h"
#include "../abstract/xarrowhead.h"
#include "../graph/vcolor.h"
#include "../graph/vpoint.h"
#include "../graph/vrect.h"
#include "../graph/vcontext.h"
namespace violet {
	namespace property {
        using namespace violet::abstract;
		class ArrowHeadChoiceList : public IconChoiceList<ArrowHead> {
			public:
				ArrowHeadChoiceList() : IconChoiceList<ArrowHead>(__GetKeys(),__GetValues()) {
				}
				~ArrowHeadChoiceList() {
                }
                
                static ArrowHead* NONE;
                static ArrowHead* V;
                static ArrowHead* TRIANGLE_WHITE;
                static ArrowHead* TRIANGLE_BLACK;
                static ArrowHead* DIAMOND_WHITE;
                static ArrowHead* DIAMOND_BLACK;
                static ArrowHead* X;
			private:
				class ArrowHeadIcon : public VIcon {
					public:
						ArrowHeadIcon(ArrowHead& arrowHead) {
							m_arrowHead = arrowHead.Clone();
						}
                        ArrowHeadIcon(const ArrowHeadIcon& arrowHeadIcon) {
                            m_arrowHead = arrowHeadIcon.m_arrowHead->Clone();// new one
                        }
                        ArrowHeadIcon& operator=(const ArrowHeadIcon&arrowHeadIcon) {// ?
                            m_arrowHead = arrowHeadIcon.m_arrowHead->Clone();
                            return *this;
                        }
                        ~ArrowHeadIcon() {
                            delete m_arrowHead;
                        }
						int GetIconWidth() {
							return WIDTH;
						}
						int GetIconHeight() {
							return HEIGHT;
						}
						void DrawIcon(VContext& context,int x,int y){
                            /*
                            XArrowHead need special handle
                            */
                            int offset = 0;
                            XArrowHead* xarrow = nullptr;
                            xarrow = dynamic_cast<XArrowHead*>(m_arrowHead);
                            VColor oldColor = context.GetColor();
                            VRect arrowHeadBounds = m_arrowHead->GetBounds();
                            
                            if (xarrow) {
                                arrowHeadBounds.GetLocation().SetX(0);
                                arrowHeadBounds.GetLocation().SetY(0);
                                offset = arrowHeadBounds.GetSize().GetX() / 2;
                            }
                                
                            VPoint start(5-arrowHeadBounds.GetLocation().GetX(),HEIGHT/2);
                            VPoint end(WIDTH-1-offset,HEIGHT/2);
                            

                            context.SetColor(VColor(0,0,0));//black
                            
                            VPoint oldLocation = context.GetLocation();
							context.Translate(x-oldLocation.GetX(),y-oldLocation.GetY());
                            context.DrawLine(start+VPoint(x,y),end+VPoint(x,y));
                            
                            m_arrowHead->Draw(context,start+VPoint(x,y),end+VPoint(x,y));
							
							context.Translate(oldLocation.GetX()-x,oldLocation.GetY()-y);
                            context.SetColor(oldColor);
                        }
					private:
						const static int WIDTH = 35;
						const static int HEIGHT = 20;
						ArrowHead* m_arrowHead;
				};
				std::vector<VIcon*> __GetKeys() {
					std::vector<VIcon*> keys;
					for (int i=0;i<7;i++) {
						keys.push_back(new ArrowHeadIcon(*ARROWHEAD_ICONS[i]));
                    }
					return keys;
				}
				std::vector<ArrowHead*> __GetValues() {
					std::vector<ArrowHead*> values;
					values.push_back(
                        new ArrowHead(*ARROWHEADS[0]));//NONE
                    values.push_back(
                        new VArrowHead(*dynamic_cast<VArrowHead*>(ARROWHEADS[1])));//V
                    values.push_back(
                        new TriangleArrowHead(*dynamic_cast<TriangleArrowHead*>(ARROWHEADS[2])));//
                    values.push_back(
                        new TriangleArrowHead(*dynamic_cast<TriangleArrowHead*>(ARROWHEADS[3])));
                    values.push_back(
                        new DiamondArrowHead(*dynamic_cast<DiamondArrowHead*>(ARROWHEADS[4])));
                    values.push_back(
                        new DiamondArrowHead(*dynamic_cast<DiamondArrowHead*>(ARROWHEADS[5])));
                    values.push_back(
                        new XArrowHead(*dynamic_cast<XArrowHead*>(ARROWHEADS[6])));
					return values;
				}
				static ArrowHead* ARROWHEADS[];
				static ArrowHeadIcon* ARROWHEAD_ICONS[];
		};
	}
}

#endif

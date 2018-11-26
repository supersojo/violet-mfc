#ifndef ARROWHEADCHOICELIST_H
#define ARROWHEADCHOICELIST_H

namespace violet {
	namespace property {
		class ArrowHeadChoiceList : public IconChoiceList<ArrowHead> {
			public:
				ArrowHeadChoiceList() : IconChoiceList<ArrowHead>(GetKeys(),GetValues()) {
				}
				~ArrowHeadChoiceList();
			private:
				class ArrowHeadIcon : public VIcon {
					public:
						ArrowHeadIcon(ArrowHead& arrowHead) {
							m_arrowHead = &arrowHead;
						}
						int GetIconWidth() {
							return WIDTH;
						}
						int GetIconHeight() {
							return HEIGHT;
						}
						void DrawIcon(VContext& context,int x,int y){
                            VColor oldColor = context.GetColor();
                            VRect arrowHeadBounds = m_arrowHead->GetBounds();
                            VPoint start(5-arrowHeadBounds.GetLocation().GetX(),HEIGHT/2);
                            VPoint end(WIDTH-1,HEIGHT/2);
                            

                            context.SetColor(VColor(0,0,0));//black
                            
                            VPoint oldLocation = context.GetLocation();
							context.Translate(x-oldLocation.GetX(),y-GetLocation().GetY());
                            context.DrawLine(start+VPoint(x,y),end+VPoint(x,y));
                            
                            m_arrowHead->Draw(context,start+VPoint(x,y),end+VPoint(x,y));
							
							context.Translate(oldLocation.GetX()-x,GetLocation().GetY()-y);
                            context.SetColor(oldColor);
                        }
					private:
						const static int WIDTH = 35;
						const static int HEIGHT = 20;
						ArrowHead* m_arrowHead;
				};
				std::vector<VIcon*> GetKeys() {
					std::vector<VIcon*> keys;
					for (int i=0;i<7;i++)
						keys.push_back(new ArrowHeadIcon(*ARROWHEADS[i]));
					return keys;
				}
				std::vector<ArrowHead*> GetValues() {
					std::vector<ArrowHead*> values;
					for (int i=0;i<7;i++)
						values.push_back(new ArrowHead(*ARROWHEADS[i]));
					return values;
				}
				static ArrowHead* ARROWHEADS[];
				static ArrowHeadIcon* ARROWHEAD_ICONS[];
		};
	}
}

#endif

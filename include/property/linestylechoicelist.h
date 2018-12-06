#ifndef LINESTYLECHOICELIST_H
#define LINESTYLECHOICELIST_H
#include "iconchoicelist.h"
#include "../graph/vcontext.h"
#include "../graph/vpoint.h"
#include "../graph/vcolor.h"
#include "../graph/vstroke.h"
#include "../graph/vicon.h"
#include "../edge/linestyle.h"
/*
it refers VStroke::SOLID VStroke::DOTTED
*/
namespace violet {
    namespace property {
        class LineStyleChoiceList : public IconChoiceList<VStroke> {
            public:
                LineStyleChoiceList();
                ~LineStyleChoiceList();
                static VStroke* SOLID;
                static VStroke* DOTTED;
            private:
                static std::vector<VIcon*> __GetKeys() {
                    std::vector<VIcon*> keys;
                    for (int i=0;i<2;i++)
                        keys.push_back(new LineStyleIcon(*LINE_STYLES_ICONS[i]));
                    return keys;
                }
                static std::vector<VStroke*> __GetValues() {
                    std::vector<VStroke*> values;
                    for (int i=0;i<2;i++)
                        values.push_back(new VStroke(*LINE_STYLES[i]));
                    return values;
                }
                class LineStyleIcon : public VIcon {
                    public:
                        LineStyleIcon(VStroke& lineStyle) {
                            m_lineStyle = &lineStyle;
                        }
						LineStyleIcon(const LineStyleIcon& lineStyleIcon) {
							m_lineStyle = lineStyleIcon.m_lineStyle;
						}
						LineStyleIcon& operator=(const LineStyleIcon& lineStyleIcon) {
							m_lineStyle = lineStyleIcon.m_lineStyle;
							return *this;
						}
                        int GetIconWidth() {
                            return WIDTH;
                        }
                        int GetIconHeight() {
                            return HEIGHT;
                        }
                        void DrawIcon(VContext& context,int x,int y){
                            VColor oldColor = context.GetColor();
                            VStroke oldStroke = context.GetStroke();
                            VPoint start(5,HEIGHT/2);
                            VPoint end(WIDTH-1,HEIGHT/2);
                            

                            context.SetColor(VColor(0,0,0));//black
                            context.SetStroke(*m_lineStyle);
                            
                            VPoint oldLocation = context.GetLocation();
                            context.DrawLine(start+oldLocation,end+oldLocation);
                            context.SetLocation(oldLocation);
                            
                            context.SetStroke(oldStroke);
                            context.SetColor(oldColor);
                        }
                    private:
                        VStroke* m_lineStyle;// all refer to LineStyle SOLID DOTTED, no need to free
                        const static int WIDTH = 35;
                        const static int HEIGHT = 20;
                };
                static VStroke* LINE_STYLES[];
                static LineStyleIcon* LINE_STYLES_ICONS[];
        };
    }
}

#endif

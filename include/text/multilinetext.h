#ifndef MULTILINETEXT_H
#define MULTILINETEXT_H
#include "vlinetext.h"

namespace violet {
    class MultiLineText : public VLineText {
        public:
            virtual void Draw(VContext& context) {
                std::vector<VLineText*>::iterator i;
                std::vector<bool>::iterator j;
                VPoint offset;
                VLineText* lineText;
                for (i=m_lines.begin(),j=m_lines_changed.begin();i!=m_lines.end();i++,j++) {
                    
                    lineText = (*i);
                    
                    if ((*j)==true) {
                        lineText->UpdateBounds(context);
                        *j = false;
                    }
                    // each linetext has 10 padding round
                    context.Translate(offset.GetX()+10,offset.GetY()+10);
                    lineText->Draw(context);
                    context.Translate(-offset.GetX()-10,-offset.GetY()-10);
                    offset = GetNextOffset(offset,*lineText);
                }
            }
            virtual void AppendLineText(std::string& text) {
                // append
                VLineText* newLine = new VLineText;
                newLine->SetText(text);
                
                m_lines.push_back(newLine);
                m_lines_changed.push_back(true);

            }
            virtual void SetLineText(int i,std::string& text) {
                if (i<0||i>=m_lines.size())
                    return;
                m_lines[i]->SetText(text);
                m_lines_changed[i] = true;
            }
            VPoint GetNextOffset(VPoint& beforeOffset,VLineText& lineText) {
                return VPoint(beforeOffset.GetX(),
                              beforeOffset.GetY()+lineText.GetBounds().GetHeight());
            }
            virtual VRect GetBounds() {
                double width=0,height=0;
                for (int i=0;i<m_lines.size();i++) {
                    if (m_lines[i]->GetBounds().GetWidth()>width)
                        width = m_lines[i]->GetBounds().GetWidth();
                    height += m_lines[i]->GetBounds().GetHeight();
                }
                return VRect(0,0,width,height);
            }
        private:
            std::vector<VLineText*> m_lines;
            std::vector<bool> m_lines_changed;
            // align type
    };
}

#endif

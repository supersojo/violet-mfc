#ifndef VCONTENTTEXT_H
#define VCONTENTTEXT_H
#include <iostream>
#include "vcontent.h"
#include "vlinetext.h"
namespace violet {
    class VContentText : public VContent {
        public:
            VContentText(VLineText& lineText) {
                m_lineText = &lineText;
                m_lineText->SetContent(*this);
                m_lineWidth = DEFAULT_LINE_WIDTH;
                // m_lineWidth <= content's width
            }
            virtual ~VContentText() {
                if (m_lineText!=nullptr)
                    delete m_lineText;
            }
            virtual void Draw(VContext& context) {
                /*
                 +---+
                 |   |
                 +---+
                 10 pixels around text
                */
                int lineWidth = context.GetLineWidth();
                
                context.SetLineWidth(m_lineWidth);
                context.Translate(10,10);
                
                m_lineText->Draw(context);
                
                context.Translate(-10,-10);
                context.SetLineWidth(lineWidth);
                

            }
            virtual void RefreshUp() {
                SetOptimalSize();
                VContent::RefreshUp();
            }
            virtual void RefreshDown() {
                SetOptimalSize();
                VContent::RefreshDown();
            }
            virtual VRect GetMinimalBounds() {
                VRect rect1 = m_lineText->GetBounds();
                VRect rect2 = VContent::GetBounds();
                std::cout<<"textrect:"<<rect1<<std::endl;
                std::cout<<"contrect:"<<rect2<<std::endl;
                return VRect(rect2.GetLocation().GetX(),
                             rect2.GetLocation().GetY(),
                             (rect1.GetSize().GetX()>rect2.GetSize().GetX()?rect1.GetSize().GetX():rect2.GetSize().GetX()),
                             (rect1.GetSize().GetY()>rect2.GetSize().GetY()?rect1.GetSize().GetY():rect2.GetSize().GetY())
                             );
            }
            static const int DEFAULT_LINE_WIDTH = 50;/* in pixel unit */
        private:
            void SetOptimalSize() {
                VRect rect = GetMinimalBounds();
                std::cout<<"newrect:"<<rect<<std::endl;
                SetWidth(rect.GetSize().GetX());
                SetHeight(rect.GetSize().GetY());
            }
            VLineText* m_lineText;
            int m_lineWidth;
    };
}


#endif

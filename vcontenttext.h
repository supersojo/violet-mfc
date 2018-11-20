#ifndef VCONTENTTEXT_H
#define VCONTENTTEXT_H
#include "vcontent.h"
#include "vlinetext.h"
namespace violet {
    class VContentText : public VContent {
        public:
            VContentText(VLineText& lineText) {
                m_lineText = &lineText;
            }
            virtual ~VContentText() {
            }
            virtual void Draw(VContext& context) {
                m_lineText->Draw(context);
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
                return VRect(rect2.GetLocation().GetX(),
                             rect2.GetLocation().GetY(),
                             (rect1.GetSize().GetX()>rect2.GetSize().GetX()?rect1.GetSize().GetX():rect2.GetSize().GetX()),
                             (rect1.GetSize().GetY()>rect2.GetSize().GetY()?rect1.GetSize().GetY():rect2.GetSize().GetY())
                             );
            }
        private:
            void SetOptimalSize() {}
            VLineText* m_lineText;
    };
}


#endif

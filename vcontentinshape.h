#ifndef VCONTENTINSHAPE_H
#define VCONTENTINSHAPE_H
#include "vrect.h"
#include "vpoint.h"
#include "vshape.h"
#include "vcontentempty.h"


namespace violet {
    class VContentInShape : public VContent {
        public:
            void Draw(VContext& context) {
                m_content->Draw(context,GetShapeOffset());
            }
            VPoint GetShapeOffset() {
                VRect& shapeBounds = GetShape().GetBounds();
                
                return VPoint(
                              (shapeBounds.GetSize().GetX()-m_content->GetWidth()),
                              (shapeBounds.GetSize().GetY()-m_content->GetHeight())
                              );
            }
            bool Contains(VPoint& point) {
                return GetShape().Contains(point);
            }
            VShape& GetShape() {
                return *m_shape;
            }
            void SetShape(VShape& shape) {
                m_shape = &shape;
            }
            virtual VContent& GetContent() {
                return *m_content;
            }
            virtual void SetContent(VContent& content) {
                if (m_content!=nullptr)
                    m_content->RemoveParent(*this);
                // delete m_content??
                if (&content==nullptr) {
                    VContent& c = *(new VContentEmpty);
                    c.AddParent(*this);
                    m_content = &c;
                } else {
                    content.AddParent(*this);
                    m_content = &content;
                }
                RefreshUp();
            }
            virtual void RefreshUp() {
                VRect rect = GetMinimalBounds();
                SetWidth(rect.GetSize().GetX());
                SetHeight(rect.GetSize().GetY());
                VContent::RefreshUp();
            }
            virtual void RefreshDown() {
                m_content->RefreshDown();
                VContent::RefreshDown();
            }
            virtual VRect GetMinimalBounds() {
                GetShape().GetBounds();
            }
        private:
            VContent* m_content;
            VShape*   m_shape;
    };
}

#endif

#ifndef LINEEDGE_H
#define LINEEDGE_H
#include "../config.h"
#include "shapeedge.h"
#include "../graph/vpath.h"
#include "bentStyle.h"
#include "../property/linestylechoicelist.h"
#include "../property/bentstylechoicelist.h"
namespace violet {
    using namespace abstract;
    using namespace property;
    class LineEdge : public ShapeEdge {
        public:
            LineEdge():ShapeEdge(){
                m_shape = nullptr;
                m_lineStyleChoiceList = new LineStyleChoiceList;
                m_bentStyleChoiceList = new BentStyleChoiceList;
                SetBentStyle(BentStyle::AUTO);
                SetLineStyle(*LineStyleChoiceList::SOLID);
            }
            virtual VShape& GetShape() {
                return *m_shape;
            }
            virtual void Draw(VContext& context);
            virtual void UpdateContactPoints();
            BentStyle& GetBentStyle();
            virtual void SetBentStyle(BentStyle & bentStyle){
                if (m_bentStyleChoiceList->SetSelectedValue(bentStyle)) {
                    m_selectedBentStyle = m_bentStyleChoiceList->GetSelectedPos();
                }
            }
            VStroke& GetLineStyle() {
                return m_lineStyleChoiceList->GetSelectedValue();
            }
            virtual void SetLineStyle(VStroke & stroke){
                if (m_lineStyleChoiceList->SetSelectedValue(stroke)) {
                    m_selectedLineStyle = m_lineStyleChoiceList->GetSelectedPos();
                }
            }
            void SetBentStyleChoiceList(BentStyleChoiceList* newChoiceList) {
                delete m_bentStyleChoiceList;
                m_bentStyleChoiceList = newChoiceList;
            }
            BentStyleChoiceList* GetBentStyleChoiceList() {
                return m_bentStyleChoiceList;
            }
            void SetLineStyleChoiceList(LineStyleChoiceList* newChoiceList) {
                delete m_lineStyleChoiceList;
                m_lineStyleChoiceList = newChoiceList;
            }
            virtual ~LineEdge(){
                if (m_shape)
                    delete m_shape;
                delete m_lineStyleChoiceList;
                delete m_bentStyleChoiceList;
            }
            static const int SELF_LOOP_GAP_X = 20;
            static const int SELF_LOOP_GAP_Y = 22;
        private:
            void ReloadContactPoints(std::vector<VPoint>& points);
            void RebuildShape();
            VShape* m_shape;
            LineStyleChoiceList* m_lineStyleChoiceList;
            BentStyleChoiceList* m_bentStyleChoiceList;
            int m_selectedLineStyle;
            int m_selectedBentStyle;
    };
}

#endif

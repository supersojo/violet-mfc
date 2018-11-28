#ifndef ARROWHEADEDGE_H
#define ARROWHEADEDGE_H
#include "lineedge.h"
#include "arrowhead.h"
#include "arrowheadchoicelist.h"
namespace violet {
    using namespace violet::abstract;
    class ArrowHeadEdge : public LineEdge {
        public:
            ArrowHeadEdge() : LineEdge() {
                m_startArrowHeadChoiceList = new ArrowHeadChoiceList;
                m_endArrowHeadChoiceList = new ArrowHeadChoiceList;

                SetStartArrowHead(*ArrowHeadChoiceList::NONE);
                SetEndArrowHead(*ArrowHeadChoiceList::NONE);
            }
            void SetStartArrowHead(ArrowHead& arrowHead) {
                if (m_startArrowHeadChoiceList->SetSelectedValue(arrowHead))
                    m_selectedStartArrowHead = m_startArrowHeadChoiceList->GetSelectedPos();
            }
            ArrowHeadChoiceList& GetStartArrowHeadChoiceList() {
                return *m_startArrowHeadChoiceList;
            }
            void SetStartArrowHeadChoiceList(ArrowHeadChoiceList& choiceList) {
                delete m_startArrowHeadChoiceList;
                m_startArrowHeadChoiceList = &choiceList;
                m_selectedStartArrowHead = m_startArrowHeadChoiceList->GetSelectedPos();
            }
            ArrowHeadChoiceList& GetEndArrowHeadChoiceList() {
                return *m_endArrowHeadChoiceList;
            }
            void SetEndArrowHeadChoiceList(ArrowHeadChoiceList& choiceList) {
                delete m_endArrowHeadChoiceList;
                m_endArrowHeadChoiceList = &choiceList;
                m_selectedEndArrowHead = m_endArrowHeadChoiceList->GetSelectedPos();
            }
            ArrowHead& GetStartArrowHead() {
                return m_startArrowHeadChoiceList->GetSelectedValue();
            }
            ArrowHead& GetEndArrowHead() {
                return m_endArrowHeadChoiceList->GetSelectedValue();
            }
            void SetEndArrowHead(ArrowHead& arrowHead) {
                if (m_endArrowHeadChoiceList->SetSelectedValue(arrowHead))
                    m_selectedEndArrowHead = m_endArrowHeadChoiceList->GetSelectedPos();
            }
            virtual void BeforeReconstruction() {
                LineEdge::BeforeReconstruction();
                // need renew choicelist???
            }
            virtual void SetBorderColor(VColor& color) {
                LineEdge::SetBorderColor(color);
                GetStartArrowHead().SetBorderColor(color);
                GetEndArrowHead().SetBorderColor(color);
            }
            virtual void SetBackgroundColor(VColor& bgColor) {
                LineEdge::SetBackgroundColor(bgColor);
                GetStartArrowHead().SetFilledColor(bgColor);
                GetEndArrowHead().SetFilledColor(bgColor);
            }
            virtual void Draw(VContext& context) {
                LineEdge::Draw(context);
                GetStartArrowHead().Draw(
                    context,
                    *m_contactPoints[1],
                    *m_contactPoints[0]);
                GetEndArrowHead().Draw(
                    context,
                    *m_contactPoints[m_contactPoints.size()-2],
                    *m_contactPoints[m_contactPoints.size()-1]);
            }
            ~ArrowHeadEdge() {
                delete m_startArrowHeadChoiceList;
                delete m_endArrowHeadChoiceList;
            }
        private:
            ArrowHeadChoiceList* m_startArrowHeadChoiceList;
            ArrowHeadChoiceList* m_endArrowHeadChoiceList;
            int m_selectedStartArrowHead;
            int m_selectedEndArrowHead;
    };
}

#endif

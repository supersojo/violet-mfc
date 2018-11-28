#ifndef LABELEDLINEEDGE_H
#define LABELEDLINEEDGE_H
#include "arrowheadedge.h"
#include "vlinetext.h"
#include "vcontenttext.h"
namespace violet {
    class LabeledLineEdge : public ArrowHeadEdge {
        public:
            LabeledLineEdge() {
                m_startLabel = new VLineText;
                m_centerLabel = new VLineText;
                m_endLabel = new VLineText;
                m_startTextContent = new VContentText(*m_startLabel);
                m_centerTextContent = new VContentText(*m_centerLabel);
                m_endTextContent = new VContentText(*m_endLabel);
                m_startLabelChanged = true;
                m_startLabelChanged = true;
                m_startLabelChanged = true;
            }
            
            virtual void BeforeReconstruction() {
                ArrowHeadEdge::BeforeReconstruction();
                // renew labels??
            }
            virtual void CreateContentStructure() {
                ArrowHeadEdge::CreateContentStructure();
                // renew contents?
                // reconstruct labels??
            }
            void SetStartLabel(std::string label) {
                m_startLabel->SetText(label);
                m_startLabelChanged = true;
            }
            void SetCenterLabel(std::string label) {
                m_centerLabel->SetText(label);
                m_centerLabelChanged = true;
            }
            void SetEndLabel(std::string label) {
                m_endLabel->SetText(label);
                m_endLabelChanged = true;
            }
            virtual void SetBorderColor(VColor& borderColor) {
                ArrowHeadEdge::SetBorderColor(borderColor);
                m_startLabel->SetTextColor(borderColor);
                m_centerLabel->SetTextColor(borderColor);
                m_endLabel->SetTextColor(borderColor);
            }
            virtual void Draw(VContext& context);
            virtual ~LabeledLineEdge() {
                /*
                freed by content
                delete m_startLabel;
                delete m_centerLabel;
                delete m_endLabel;
                */
                delete m_startTextContent;
                delete m_centerTextContent;
                delete m_endTextContent;
            }
            // no need the gap 
            // we already reserved the gpa space for text 10 pixels
            const static int LABEL_GAP = 0;//??
        private:
            void DrawContent(VContext& context, VContentText& textContent,VPoint& start,VPoint& end, bool center);
            VContentText* m_startTextContent;
            VContentText* m_centerTextContent;
            VContentText* m_endTextContent;
            VLineText* m_startLabel;
            VLineText* m_centerLabel;
            VLineText* m_endLabel;
            bool m_startLabelChanged;
            bool m_centerLabelChanged;
            bool m_endLabelChanged;
        protected:
            VContentText& GetStartTextContent() {
                return *m_startTextContent;
            }
            VContentText& GetCenterTextContent() {
                return *m_centerTextContent;
            }
            VContentText& GetEndTextContent() {
                return *m_endTextContent;
            }
            
    };
}

#endif

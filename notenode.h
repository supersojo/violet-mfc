#ifndef NOTENODE_H
#define NOTENODE_H
#include "abstractnode.h"
#include "vlinetext.h"
namespace violet {
    using abstract::AbstractNode;
    class NoteNode : public AbstractNode {
        public:
            NoteNode() {
                CreateContentStructure();
            }
            virtual void BeforeReconstruction() {
                AbstractNode::BeforeReconstruction();
                //m_lineText.Reconstruction();
            }
            virtual void CreateContentStructure();
            virtual void Draw(VContext& context);
            virtual void SetTextColor(VColor& color);
            void SetText(std::string& str);
            virtual ~NoteNode(){}
        private:
            VLineText* m_lineText;
            bool m_textChanged;
    };
}

#endif

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
            virtual ~NoteNode(){}
        private:
            VLineText* m_lineText;
    };
}

#endif

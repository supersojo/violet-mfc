#ifndef NOTEEDGE_H
#define NOTEEDGE_H
#include "lineedge.h"
namespace violet {
    class NoteEdge : public LineEdge {
        public:
            NoteEdge():LineEdge(){
                SetBentStyle(BentStyle::STRAIGHT);
                SetLineStyle(*LineStyleChoiceList::DOTTED);
            }
            void BeforeReconstruction() {
                LineEdge::BeforeReconstruction();
                SetBentStyle(BentStyle::STRAIGHT);
                SetLineStyle(*LineStyleChoiceList::DOTTED);
            }
            std::string GetToolTip() {
                return "";
            }
    };
}


#endif

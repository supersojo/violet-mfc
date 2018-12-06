#include "property/arrowheadchoicelist.h"
#include "abstract/arrowhead.h"

namespace violet {
	namespace property {
        ArrowHead* ArrowHeadChoiceList::NONE = new ArrowHead;
        ArrowHead* ArrowHeadChoiceList::V = new VArrowHead;
        ArrowHead* ArrowHeadChoiceList::TRIANGLE_WHITE = new TriangleArrowHead(VColor(255,255,255),"TRIANGLE_WHITE");
        ArrowHead* ArrowHeadChoiceList::TRIANGLE_BLACK = new TriangleArrowHead(VColor(0,0,0),"TRIANGLE_BLACK");
        ArrowHead* ArrowHeadChoiceList::DIAMOND_WHITE = new DiamondArrowHead(VColor(255,255,255),"DIAMOND_WHITE");
        ArrowHead* ArrowHeadChoiceList::DIAMOND_BLACK = new DiamondArrowHead(VColor(0,0,0),"DIAMOND_BLACK");
        ArrowHead* ArrowHeadChoiceList::X = new XArrowHead;
        
        ArrowHead* ArrowHeadChoiceList::ARROWHEADS[] = {
            ArrowHeadChoiceList::NONE,
            ArrowHeadChoiceList::V,
            ArrowHeadChoiceList::TRIANGLE_WHITE,
            ArrowHeadChoiceList::TRIANGLE_BLACK,
            ArrowHeadChoiceList::DIAMOND_WHITE,
            ArrowHeadChoiceList::DIAMOND_BLACK,
            ArrowHeadChoiceList::X
        };
        ArrowHeadChoiceList::ArrowHeadIcon* ArrowHeadChoiceList::ARROWHEAD_ICONS[] = {
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::NONE),
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::V),
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::TRIANGLE_WHITE),
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::TRIANGLE_BLACK),
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::DIAMOND_WHITE),
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::DIAMOND_BLACK),
            new ArrowHeadChoiceList::ArrowHeadIcon(*ArrowHeadChoiceList::X)
        };
    }
}
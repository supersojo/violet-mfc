#include "linestylechoicelist.h"

namespace violet {
    namespace property {
        VStroke* LineStyleChoiceList::SOLID = &LineStyle::SOLID;
        VStroke* LineStyleChoiceList::DOTTED = &LineStyle::DOTTED;
        /*
        two object need freed
        */
        VStroke* LineStyleChoiceList::LINE_STYLES[] = {
            new VStroke(*LineStyleChoiceList::SOLID),
            new VStroke(*LineStyleChoiceList::DOTTED)
        };
        /*
        two object need freed
        */
        LineStyleChoiceList::LineStyleIcon* LineStyleChoiceList::LINE_STYLES_ICONS[] = {
            new LineStyleChoiceList::LineStyleIcon(*LineStyleChoiceList::SOLID),
            new LineStyleChoiceList::LineStyleIcon(*LineStyleChoiceList::DOTTED)
        };
        LineStyleChoiceList::LineStyleChoiceList() : IconChoiceList<VStroke>(GetKeys(),GetValues()){
            
        }
        LineStyleChoiceList::~LineStyleChoiceList() {
            
        }
    }
}
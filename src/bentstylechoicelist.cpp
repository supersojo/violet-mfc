#include "property/bentstylechoicelist.h"

namespace violet {
    namespace property {
        BentStyle* BentStyleChoiceList::STRAIGHT = &BentStyle::STRAIGHT;
        BentStyle* BentStyleChoiceList::FREE = &BentStyle::FREE;
        BentStyle* BentStyleChoiceList::HV = &BentStyle::HV;
        BentStyle* BentStyleChoiceList::VH = &BentStyle::VH;
        BentStyle* BentStyleChoiceList::HVH = &BentStyle::HVH;
        BentStyle* BentStyleChoiceList::VHV = &BentStyle::VHV;
        BentStyle* BentStyleChoiceList::AUTO = &BentStyle::AUTO;
        BentStyle* BentStyleChoiceList::BENT_STYLE[] = {
            new BentStyle(*BentStyleChoiceList::AUTO),
            new BentStyle(*BentStyleChoiceList::STRAIGHT),
            new BentStyle(*BentStyleChoiceList::FREE),
            new BentStyle(*BentStyleChoiceList::HV),
            new BentStyle(*BentStyleChoiceList::VH),
            new BentStyle(*BentStyleChoiceList::HVH),
            new BentStyle(*BentStyleChoiceList::VHV)
        };
        std::string* BentStyleChoiceList::BEN_STYLE_KEYS[] = {
            new std::string("AUTO"),
            new std::string("STRAIGHT"),
            new std::string("FREE"),
            new std::string("HV"),
            new std::string("VH"),
            new std::string("HVH"),
            new std::string("VHV")
        };
        
        /* need free the news */
        
        BentStyleChoiceList::BentStyleChoiceList() : TextChoiceList<BentStyle>(__GetKeys(),__GetValues()){
        }
        BentStyleChoiceList::~BentStyleChoiceList() {
        }
        
    }
}

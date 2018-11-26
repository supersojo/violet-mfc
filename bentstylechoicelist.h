#ifndef BENTSTYLECHOICELIST_H
#define BENTSTYLECHOICELIST_H
#include "textchoicelist.h"
#include "bentstyle.h"
namespace violet {
    namespace property {
        class BentStyleChoiceList : public TextChoiceList<BentStyle> {
            public:
                BentStyleChoiceList();
                ~BentStyleChoiceList();
                static BentStyle* STRAIGHT;
                static BentStyle* FREE;
                static BentStyle* HV;
                static BentStyle* VH;
                static BentStyle* HVH;
                static BentStyle* VHV;
                static BentStyle* AUTO;
            private:
                std::vector<std::string*> GetKeys() {
                    std::vector<std::string*> keys;
                    for (int i=0;i<2;i++)
                        keys.push_back(new std::string(*BEN_STYLE_KEYS[i]));
                    return keys;
                }
                std::vector<BentStyle*> GetValues() {
                    std::vector<BentStyle*> values;
                    for (int i=0;i<2;i++)
                        values.push_back(new BentStyle(*BENT_STYLE[i]));
                    return values;
                }
                static BentStyle* BENT_STYLE[];
                static std::string* BEN_STYLE_KEYS[];
            
        };
    }
}

#endif

#ifndef ICONCHOICELIST_H
#define ICONCHOICELIST_H
#include "vicon.h"
#include "choicelist.h"
namespace violet {
    namespace property {
        template<class ValueType>
        class IconChoiceList : public ChoiceList<VIcon,ValueType> {
            public:
                IconChoiceList(std::vector<VIcon*>& keys,std::vector<ValueType*>& values) : ChoiceList<VIcon,ValueType>(keys,values){
                }
                virtual ~IconChoiceList(){}
            private:
                IconChoiceList(){}/* disallow default construct */
        };
    }
}
#endif
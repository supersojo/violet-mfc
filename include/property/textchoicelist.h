#ifndef TEXTCHOICELIST_H
#define TEXTCHOICELIST_H
#include <string>
#include "choicelist.h"
namespace violet {
    namespace property {
        template<class ValueType>
        class TextChoiceList : public ChoiceList<std::string,ValueType> {
            public:
                TextChoiceList(std::vector<std::string*>& keys,std::vector<ValueType*>& values) : ChoiceList<std::string,ValueType>(keys,values){
                }
                virtual ~TextChoiceList(){}
            private:
                TextChoiceList(){}/* disallow default construct */
        };
    }
}
#endif

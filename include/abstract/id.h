#ifndef ID_H
#define ID_H
/*
 * Id is used to identify a node or edge.
 */
#include <string>
#include "../util/uuidgen.h"
#include <iostream>

// violet::abstract::Id

namespace violet {
    namespace abstract {
        /*
        Id class is used to identify something.
        */
        class Id {
            public:
                Id() {
                    UUIDGen gen;
                    m_value = gen.Gen();
                }
                std::string GetValue() const{
                    return m_value;
                }
                void SetValue(std::string v) {
                    m_value = v;
                }
                /*
                 * Clone Return a new Id object with the same string value 
                 */
                Id& Clone() {
                    Id *tmp =new Id;
                    tmp->SetValue(GetValue());
                    return (*tmp);
                }
                /*
                 * Equal will check Id string value same or not.
                 */
                bool Equal(Id& obj) {
                    return (m_value.compare(obj.GetValue())) == 0;
                }
                /* 
                 * << will print the string value
                 */
                friend std::ostream& operator<<(std::ostream& out,const Id& id) {
                        out<<id.GetValue();
                        return out;
                }
            private:
                std::string  m_value;
        };
    }
}
#endif

#ifndef ID_H
#define ID_H

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
                Id& Clone() {
                    Id *tmp =new Id;
                    tmp->SetValue(GetValue());
                    return (*tmp);
                }
                bool Equal(Id& obj) {
                    return (m_value.compare(obj.GetValue())) == 0;
                }
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

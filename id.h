#ifndef ID_H
#define ID_H

#include <string>
#include "uuidgen.h"

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
                std::string GetValue() {
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
            private:
                std::string  m_value;
        };
    }
}
#endif

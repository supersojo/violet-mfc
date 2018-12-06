#ifndef IIDENTIFIABLE_H
#define IIDENTIFIABLE_H

#include "id.h"

// violet::abstract::IIdentifiable
namespace violet {
    namespace abstract {
        /*
        The interface is for class that can be identifiable.
        */
        class IIdentifiable {
            public:
                virtual Id& GetId() = 0;
                virtual void SetId(Id& id) = 0;
                virtual int GetRevision() = 0;
                virtual void SetRevision(int rev) = 0;
                virtual void IncrementRevision() = 0;
        };
    }
}
#endif

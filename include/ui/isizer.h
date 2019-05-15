#ifndef ISIZER_H
#define ISIZER_H

#include "graph/vrect.h"

namespace violet {
    class ISizer {
        public:
            virtual VRect GetBounds()= 0; 
    };
}

#endif

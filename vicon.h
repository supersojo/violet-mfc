#ifndef VICON_H
#define VICON_H
#include "vcontext.h"
namespace violet {
    class VIcon {
        public:
            // x y are absolute position on graph
            virtual void DrawIcon(VContext& context,int x,int y){
            }
            virtual ~VIcon(){}
    };
}

#endif

#ifndef VSTROKE_H
#define VSTROKE_H

namespace violet {

    class VStroke {
        public:
            VStroke(){}
            VStroke(const VStroke& stroke){
                
            }
            VStroke& operator=(const VStroke& stroke) {
                return *this;
            }
    };
}

#endif


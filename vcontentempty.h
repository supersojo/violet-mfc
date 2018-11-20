#ifndef VCONTENTEMPTY_H
#define VCONTENTEMPTY_H
#include "vcontent.h"
namespace violet {
    class VContentEmpty : public VContent{
        public:
            virtual ~VContentEmpty() {
            }
            virtual void Draw(VContext& context) {
            }
            void SetWidth(double w) {
            }
            void SetHeight(double h){
            }
            void SetMinWidth(double w) {
                VContent::SetMinWidth(w);
                VContent::SetWidth(w);
                RefreshUp();
            }
            void SetMinHeight(double h) {
                VContent::SetMinHeight(h);
                VContent::SetHeight(h);
                RefreshUp();
            }
    };
}

#endif

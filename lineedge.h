#ifndef LINEEDGE_H
#define LINEEDGE_H
#include "shapeedge.h"
#include "vpath.h"
namespace violet {
    class LineEdge : public ShapeEdge {
        public:
            LineEdge():ShapeEdge(){
                m_shape = nullptr;
            }
            virtual VShape& GetShape() {
                return *m_shape;
            }
            virtual void Draw(VContext& context);
            virtual void UpdateContactPoints();
            virtual ~LineEdge(){
            }
            static const int SELF_LOOP_GAP_X = 20;
            static const int SELF_LOOP_GAP_Y = 22;
        private:
            void RebuildShape();
            VShape* m_shape;
    };
}

#endif

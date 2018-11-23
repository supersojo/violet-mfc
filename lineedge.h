#ifndef LINEEDGE_H
#define LINEEDGE_H
#include "config.h"
#include "shapeedge.h"
#include "vpath.h"
#include "bentStyle.h"
namespace violet {
    using namespace abstract;
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
            BentStyle& GetBentStyle();
            virtual void SetBentStyle(BentStyle & bentStyle){
            }
            virtual ~LineEdge(){
            }
            static const int SELF_LOOP_GAP_X = 20;
            static const int SELF_LOOP_GAP_Y = 22;
        private:
            void ReloadContactPoints(std::vector<VPoint>& points);
            void RebuildShape();
            VShape* m_shape;
    };
}

#endif

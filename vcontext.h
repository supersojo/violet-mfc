#ifndef VCONTEXT_H
#define VCONTEXT_H
#include <gdiplus.h>
#include "vpoint.h"
namespace violet {
    class VShape;
    class VColor;
    class VPoint;
    /*
    context for draw something
    */
    class VContext {
        public:
            VContext();
            virtual void Draw(VShape& shape, VColor& color);
            virtual void Fill(VShape& shape, VColor& color);
            VPoint& GetLocation() {
                return m_location;
            }
            void SetLocation(VPoint& point) {
                m_location = point;
            }
            void Attach(Gdiplus::Graphics& graphics) {
                m_graphics = &graphics;
            }
            void DrawLine(VPoint& start,VPoint& end,VColor& color);
            void DrawString(std::string& str,VPoint& location, VColor&color);
            ~VContext();
        private:
            ULONG_PTR gdiplusToken;
            VPoint m_location;
            Gdiplus::Graphics* m_graphics;
    };

}

#endif



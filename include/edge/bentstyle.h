#ifndef BENTSTYLE_H
#define BENTSTYLE_H
#include <vector>
#include "../graph/vpoint.h"
namespace violet {
    class BentStyle {
        public:
            std::vector<VPoint> GetPath(std::vector<VPoint>& points);
            
            BentStyle() {
            }
            BentStyle(std::string style) : m_style(style){
            }
            BentStyle(const BentStyle& bentStyle) {
                m_style = bentStyle.m_style;
            }
            BentStyle& operator=(const BentStyle bentStyle) {
                m_style = bentStyle.m_style;
                return *this;
            }
            std::string GetStyle(){
                return m_style;
            }
            bool operator==(const BentStyle& style) {
                return GetStyle().compare(style.m_style)==0;
            }
            static BentStyle STRAIGHT;
            static BentStyle FREE;
            static BentStyle HV;
            static BentStyle VH;
            static BentStyle HVH;
            static BentStyle VHV;
            static BentStyle AUTO;
        private:
            std::string m_style;
            std::vector<VPoint> GetStraightPath(VPoint& start,VPoint& end);
            std::vector<VPoint> GetFreePath(std::vector<VPoint>& points);
            std::vector<VPoint> GetHVPath(VPoint& start,VPoint& end);
            std::vector<VPoint> GetVHPath(VPoint& start,VPoint& end);
            std::vector<VPoint> GetHVHPath(VPoint& start,VPoint& end);
            std::vector<VPoint> GetVHVPath(VPoint& start,VPoint& end);
            std::vector<VPoint> GetSelfPath(VPoint& point);
            static const int MIN_SEGMENT = 15;
            static const int SELF_WIDTH = 30;
            static const int SELF_HEIGHT = 25;
    };
}

#endif

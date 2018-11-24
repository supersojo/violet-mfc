#include <cmath>
#include <iostream>
#include "bentstyle.h"

namespace violet {

BentStyle BentStyle::STRAIGHT;
BentStyle BentStyle::FREE;
BentStyle BentStyle::HV;
BentStyle BentStyle::VH;
BentStyle BentStyle::HVH;
BentStyle BentStyle::VHV;
BentStyle BentStyle::AUTO;


std::vector<VPoint> BentStyle::GetPath(std::vector<VPoint>& points) {
    if (points.size() < 2)
        return std::vector<VPoint>();
    VPoint start = points[0];
    VPoint end = points[points.size()-1];
    
    std::vector<VPoint> r;
    
	std::cout<<"current path"<<std::endl;
    if (this == &STRAIGHT)
        r = GetStraightPath(start,end);
    else if (this == &FREE)
        r =  GetFreePath(points);
    else if (this == &HV)
        r =  GetHVPath(start,end);
    else if (this == &VH)
        r =  GetVHPath(start,end);
    else if (this == &HVH)
        r =  GetHVHPath(start,end);
    else if (this == &VHV)
        r =  GetVHVPath(start,end);
    if (!r.empty()) {
		std::vector<VPoint>::iterator i;
		for (i=r.begin();i!=r.end();i++) {
			std::cout<<(*i)<<"->";
		}
		std::cout<<std::endl;
        return r;
	}
    std::cout<<"revert path"<<std::endl;
    /* try reverse path*/
    if (start.GetX()==end.GetX() &&
        start.GetY()==end.GetY())
        r = GetSelfPath(start);
    else if (this == &HVH)
        r = GetVHVPath(start,end);
    else if (this == &VHV)
        r = GetHVHPath(start,end);
    else if (this == &HV)
        r = GetVHPath(start,end);
    else if (this == &VH)
        r = GetHVPath(start,end);
    else if (this == &FREE)
        r = GetFreePath(points);
    if (!r.empty())
        return r;
    //return default path
    return GetStraightPath(start,end);
}

std::vector<VPoint> BentStyle::GetStraightPath(VPoint& start,VPoint& end) {
    std::vector<VPoint> r;
    r.push_back(start);
    r.push_back(end);
    return r;
}

std::vector<VPoint> BentStyle::GetFreePath(std::vector<VPoint>& points) {
    std::vector<VPoint> r;
    for (int i=0;i<points.size();i++)
        r.push_back(points[i]);
    return r;
}

std::vector<VPoint> BentStyle::GetHVPath(VPoint& start,VPoint& end) {
    /*
    ---+
       |
    */
    std::vector<VPoint> r;
    double x1;
    double x2 = end.GetX();
    double y1 = start.GetY();
    double y2;
    // x direction
    if ((x2+MIN_SEGMENT) <= start.GetX())
        x1 = start.GetX();
    else if((x2-MIN_SEGMENT) >= start.GetX())
        x1 = start.GetX();
    else/* no enough space for H path */
        return r;
    // y direction
    if ((y1+MIN_SEGMENT) <= end.GetY())
        y2 = end.GetY();
    else if ((y1-MIN_SEGMENT) >= end.GetY())
        y2 = end.GetY();
    else/* no enough space for V path */
        return r;
    r.push_back(VPoint(x1,y1));
    r.push_back(VPoint(x2,y1));
    r.push_back(VPoint(x2,y2));
    return r;
}

std::vector<VPoint> BentStyle::GetVHPath(VPoint& start,VPoint& end) {
    /*
       |
       +---
    */
    std::vector<VPoint> r;
    double x1 = start.GetX();
    double x2;
    double y1;
    double y2 = end.GetY();
    // x direction
    if ((x1+MIN_SEGMENT) <= end.GetX())
        x2 = end.GetX();
    else if((x1-MIN_SEGMENT) >= end.GetX())
        x1 = end.GetX();
    else/* no enough space for H path */
        return r;
    // y direction
    if ((y2+MIN_SEGMENT) <= start.GetY())
        y1 = start.GetY();
    else if ((y2-MIN_SEGMENT) >= start.GetY())
        y1 = start.GetY();
    else/* no enough space for V path */
        return r;
    r.push_back(VPoint(x1,y1));
    r.push_back(VPoint(x1,y2));
    r.push_back(VPoint(x2,y2));
    return r;
}

std::vector<VPoint> BentStyle::GetHVHPath(VPoint& start,VPoint& end) {
    /*
    ---+
       |
       +----
    */
    std::vector<VPoint> r;
    double x1;
    double x2;
    double y1 = start.GetY();
    double y2 = end.GetY();
    if ((start.GetX()+2 * MIN_SEGMENT) <= end.GetX())
    {
        x1 = start.GetX();
        x2 = end.GetX();
    } else if ((end.GetX()+2 * MIN_SEGMENT) <= start.GetX()) {
        x1 = start.GetX();
        x2 = end.GetX();
    } else { /* no enough space for H path*/
        return r;
    }
    if (abs(y1 - y2) <= MIN_SEGMENT)
    {
        /*
         ---+
            |         =>  -------
            +----
        */
        r.push_back(VPoint(x1,y2));
        r.push_back(VPoint(x2,y2));
    } else {
        r.push_back(VPoint(x1,y1));
        r.push_back(VPoint((x1+x2)/2,y1));
        r.push_back(VPoint((x1+x2)/2,y2));
        r.push_back(VPoint(x2,y2));
    }
    return r;
}

std::vector<VPoint> BentStyle::GetVHVPath(VPoint& start,VPoint& end) {
    /*
      |
      +---+
          |
    */
    std::vector<VPoint> r;
    double x1 = start.GetX();
    double x2 = end.GetX();
    double y1;
    double y2;
    if ((start.GetY() + 2*MIN_SEGMENT)  <= end.GetY()) {
        y1 = start.GetY();
        y2 = end.GetY();
    } else if ((end.GetY() + 2*MIN_SEGMENT)  <= start.GetY()) {
        y1 = start.GetY();
        y2 = end.GetY();
    } else {/* no enough space for V path*/
        return r;
    }
    if (abs(x1 - x2) <= MIN_SEGMENT) {
        /*
        |         |
        +-+  =>   |
          |       |
        */
        r.push_back(VPoint(x2,y1));
        r.push_back(VPoint(x2,y2));
    } else {
        r.push_back(VPoint(x1,y1));
        r.push_back(VPoint(x1,(y1+y2)/2));
        r.push_back(VPoint(x2,(y1+y2)/2));
        r.push_back(VPoint(x2,y2));
    }
    return r;
}

std::vector<VPoint> BentStyle::GetSelfPath(VPoint& point) {
    double x1 = point.GetX() + SELF_WIDTH * 3 / 4;
    double y1 = point.GetY();
    double y2 = point.GetY() + SELF_HEIGHT;
    double x2 = point.GetX() + 2 * SELF_WIDTH;
    double y3 = point.GetY() - SELF_HEIGHT / 4;
    double x3 = point.GetX() + SELF_WIDTH;
    std::vector<VPoint> r;
    r.push_back(VPoint(x1,y1));
    r.push_back(VPoint(x1,y2));
    r.push_back(VPoint(x2,y2));
    r.push_back(VPoint(x2,y3));
    r.push_back(VPoint(x3,y3));
    return r;
}


}

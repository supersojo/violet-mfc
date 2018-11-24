#ifndef DIRECTION_H
#define DIRECTION_H
#include "config.h"
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "vpoint.h"
/*
 0
 +--------> x
 |
 |
 V y
*/

namespace violet {
    class VPoint;
    namespace abstract {
        class Direction {
            public:
                Direction() {
                    m_x = 0;
                    m_y = 0;
                }
                Direction(double dx,double dy) {
                    double length;
                    m_x = dx;
                    m_y = dy;
                    
                    if (abs(m_x)<0.000001)
                        m_x = 0;
                    if (abs(m_y)<0.000001)
                        m_y = 0;
                    
                    if ((m_x==0) && (m_y==0))
                        return;
                    
                    length = sqrt(m_x*m_x+m_y*m_y);
                    m_x = m_x/length;
                    m_y = m_y/length;
                    
                    if (abs(m_x)<0.000001)
                        m_x = 0;
                    if (abs(m_y)<0.000001)
                        m_y = 0;
                }
                Direction(VPoint& p,VPoint& q) : m_x(q.GetX()-p.GetX()),m_y(q.GetY()-p.GetY()){
                    double length;
                    
                    if (abs(m_x)<0.000001)
                        m_x = 0;
                    if (abs(m_y)<0.000001)
                        m_y = 0;
                    
                    if ((m_x==0) && (m_y==0))
                        return;
                    
                    length = sqrt(m_x*m_x+m_y*m_y);
                    m_x = m_x/length;
                    m_y = m_y/length;
                    
                    if (abs(m_x)<0.000001)
                        m_x = 0;
                    if (abs(m_y)<0.000001)
                        m_y = 0;
                }
                Direction(const Direction& direction) {
                    m_x = direction.m_x;
                    m_y = direction.m_y;
                }
                Direction Turn(double angle) {
                    double x,y;
                    double a = angle * (M_PI/180);
                    x = m_x*cos(a)-m_y*sin(a);
                    y = m_x*sin(a)+m_y*cos(a);
                    return Direction(x,y);
                }
                double GetX() {
                    return m_x;
                }
                double GetY() {
                    return m_y;
                }
                Direction GetNearestCardinalDirection() {
                    long x,y;
                    x = round(GetX());
                    y = round(GetY());
                    if ((abs(x)==1) && (abs(y)==1)) {
                        if (abs(GetX()) >= abs(GetY()))
                            y = 0;
                        if (abs(GetX()) < abs(GetY()))
                            x = 0;
                    }
                    if (x==0 && y==-1)
                        return Direction::NORTH;
                    if (x==0 && y==1)
                        return Direction::SOUTH;
                    if (x==1 && y==0)
                        return Direction::EAST;
                    if (x==-1 && y==0)
                        return Direction::WEST;
                    /* should never happen */
                    return *this;
                }
                Direction& operator=(const Direction& direction) {
                    m_x = direction.m_x;
                    m_y = direction.m_y;
                    return *this;
                }
                bool Equals(Direction& d) {
                    if ((m_x==d.GetX()) && (m_y==d.GetY()))
                        return true;
                    return false;
                }
                static  Direction NORTH;
                static  Direction SOUTH;
                static  Direction EAST;
                static  Direction WEST;
            private:
                double m_x;
                double m_y;
        };
    }
}
#endif

#ifndef _COORD_H_
#define _COORD_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926535898
#define DEGTORAD PI/180.0
#define RADTODEG 180.0/PI

struct coord
{
    double x_;
    double y_;
    double z_;
};

inline double polarProjectionX(double x, double dist, double angle)
{
    return x + dist * cos(angle * DEGTORAD);
}

inline double polarProjectionY(double y, double dist, double angle)
{
    return y + dist * sin(angle * DEGTORAD);
}

inline double angleBetweenPoints(double x1, double y1, double x2, double y2)
{
    return RADTODEG * atan2(y2 - y1, x2 - x1);
}

inline double DistanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
inline bool direct(int x1,int y1,int x2,int y2)
{
    int n=x1*y2-x2*y1;
    return n>=0;
}
inline double toAngle2(double fl)
{
	if(fl>=360)
		return fmod(fl,360);
	else if(fl<0)
		return fmod(fl,360) + 360;
    return fl;
}

inline int PinAB( double x0, double y0, double x1, double y1, double x2, double y2)
{
    double Kb, Kc;
    Kb = x0*y1 - x1*y0;
    Kc = x0*y2 - x2*y1;
    if(((0 > Kb) && (0 < Kc)) || ((0 < Kb) && (0 > Kc)))
        return 1;
    return 0;
}
 
inline int inTriangle( double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
    if ( PinAB ( x0 - x1, y0 -y1, x2 - x1, y2 - y1, x3 - x1, y3 - y1) &&
         PinAB ( x0 - x2, y0 -y2, x3 - x2, y3 - y2, x1 - x2, y1 - y2) &&
         PinAB ( x0 - x3, y0 -y3, x2 - x3, y2 - y3, x1 - x3, y1 - y3))
         return 1;
    return 0;
}
inline coord randInRect(double x0, double y0, double x1, double y1, double x2, double y2)
{
    double rX=rand()/(double)(RAND_MAX);
    double rY=rand()/(double)(RAND_MAX);
    coord rt={x0+(x1-x0)*rX+(x2-x0)*rY, y0+(y1-y0)*rX+(y2-y0)*rY,0};
    return rt;
}
inline int isInPolygon(int vertexNum, double *vertx, double *verty, float x0, float y0)
{
    int c = 0;
    for (int i = 0, j = vertexNum-1; i < vertexNum; j = i++)
    {
        if(((verty[i]>y0) != (verty[j]>y0))
            && (x0 < (vertx[j]-vertx[i]) * (y0-verty[i]) / (verty[j]-verty[i]) + vertx[i]))
            c = !c;
    }
    return c;
}

inline bool inAngle(double f1, double f2, double range)
{
    if(range >=180)
    {
        return true;
    }
    double begin1=f2-range;double end1;double begin2;double end2=f2+range;
    if(end2>=360)
    {
        begin1=f2-range;
        end1=360;
        begin2=0;
        end2=f2+range-360;
    }
    else if(begin1<0)
    {
        begin1=f2-range+360;
        end1=360;
        begin2=0;
        end2=f2+range;
    }
    else
    {
        end1=f2;
        begin2=f2;
    }
    if((f1 >= begin1 && f1 < end1) || (f1 >= begin2 && f1 <= end2))
    {
        return true;
    }
    return false;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// File:                    "math_func.cpp"
//
// Original Author:         Roby Atadero (RA)
//
// Creation Date:           Aug 15, 2007
//
// Last Edited:             Nov 16, 2007 - Added Min Function/Comments
//
// Purpose:                 Implementation of the generic math functions
//
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "mathfunctions.h"
#include "point.h"

using namespace std;

double distBetween(double x1, double y1, double x2, double y2)
{
	double dA = x1 - x2;
	double dB = y1 - y2;

	return sqrt(dA*dA + dB*dB);
}

double distBetween(Point p1, Point p2)
{
    double dA = p1.getX() - p2.getX();
	double dB = p1.getY() - p2.getY();

	return sqrt(dA*dA + dB*dB);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CalcAngle
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Takes two points and returns the angle the second point
//                      makes with the first in radians. Only a 2D function
//                      Ex. Point 1 = (0, 0)   Point 2 = (2, 2)
//
//
//                      |   o P2
//                      |  /
//                      | /
//                      |/ )  = 45 Degrees         Returns 45 degrees in radians
//                      o--------------            I.E.  45 deg = sqrt(2)/2
//                     P1
//
// Inputs:              double x1 - The x coordinate of the first point
//                      double y1 - The y coordinate of the first point
//                      double x2 - The x coordinate of the second point
//                      double y2 - The y coordinate of the second point
//
// Outputs:             None.
//
// Returns:             The radian angle the second point makes with the first.
////////////////////////////////////////////////////////////////////////////////
double calcAngle(double x1, double y1, double x2, double y2)
{
    double x = x2 - x1;
	double y = y2 - y1;

	return atan2(y, x);
}

double calcAngle(Point p1, Point p2)
{
    double x1 = p1.getX();
    double x2 = p2.getX();

    double y1 = p1.getY();
    double y2 = p2.getY();

	double x = x2 - x1;
	double y = y2 - y1;

	return atan2(y2 - y1, x2 - x1);
}

double min(double a, double b)
{
    if(a < b)
        return a;
    else
        return b;
}

double max(double a, double b)
{
    if(a > b)
        return a;
    return b;
}

///@file
///@brief File for the math functions.
///
/// This will make it easier to calculate certain things like distances and angles.
///
///Copyright 2008, Roby Atadero
///
///Please give credit if using this in your software.
///
///@author Roby Atadero
///@version 0.70
///@date 2008

///@addtogroup userclasses User Classes
///All classes that the programmer will directly use.
///@{

#ifndef _MATHFUNCTIONS_H_
#define _MATHFUNCTIONS_H_

#include "point.h"

using namespace std;

/// @brief Calculates the distance between the two points.
///
/// Returns the exact distance between the two points.
/// @param x1 The x location of point 1.
/// @param y1 The y location of point 1.
/// @param x2 The x location of point 2.
/// @param y2 The y location of point 2.
/// @return double The exact distance between the points.
double distBetween(double x1, double y1, double x2, double y2);

/// @brief Calculates the distance between the two points.
///
/// Returns the exact distance between the two points.
/// @param p1 The first Point.
/// @param p2 The second Point.
/// @return double The exact distance between the points.
double distBetween(Point p1, Point p2);


////////////////////////////////////////////////////////////////////////////////
// Function:            CalcAngle
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Takes two points and returns the angle the second point
//                      makes with the first in radians.
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
// Inputs:              double x - The x coordinate of the first point
//                      double y1 - The y coordinate of the first point
//                      double dX2_ - The x coordinate of the second point
//                      double dY2_ - The y coordinate of the second point
//
// Outputs:             None.
//
// Returns:             The radian angle the second point makes with the first.
////////////////////////////////////////////////////////////////////////////////

/// @brief Calculates the angle that is created from the two points.
///
/// Calculates the angle in radians that the second point makes with the first.
/// @param x1 The x location of point 1.
/// @param y1 The y location of point 1.
/// @param x2 The x location of point 2.
/// @param y2 The y location of point 2.
/// @return double The angle in radians that point 2 makes with point 1.
double calcAngle(double x1, double y1, double x2, double y2);

/// @brief Calculates the angle that is created from the two points.
///
/// Calculates the angle in radians that the second point makes with the first.
/// @param p1 The first Point.
/// @param p2 The second Point.
/// @return double The angle in radians that point 2 makes with point 1.
double calcAngle(Point p1, Point p2);

/// @brief Calculates the minimum between the two numbers.
///
/// @param a The first number.
/// @param b The second number.
/// @return double The minimum between the two.
double min(double a, double b);

/// @brief Calculates the maximum between the two numbers.
///
/// @param a The first number.
/// @param b The second number.
/// @return double The maximum between the two.
double max(double a, double b);

#endif
///@}

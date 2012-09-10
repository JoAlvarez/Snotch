///@file
///@brief File for the Point class.
///
/// This will allow the user to use cartesian Points.
///
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

#ifndef _POINT_H_
#define _POINT_H_

///@brief Class that creates Points.
///
/// This will allow the programmer to use cartesian Point objects.
class Point
{
    private:

        double                  x;
        double                  y;

    public:

        /// @brief Default Point constructor.
        ///
        /// Creates a point with default x and y values.
        Point();

        /// @brief Point contructor.
        ///
        /// Creates a point with the given values supplied.
        /// @param x The x location of the point.
        /// @param y The y location of the point.
        Point(double x, double y);

        /// @brief Moves the point by the given x and y amounts.
        /// @param x The amount to move the point in the x direction.
        /// @param y The amount to move the point in the y direction.
        void                    move(double x, double y);

        /// @brief Returns the x value of the point.
        /// @return double The x value of the point.
        double                  getX();

        /// @brief Returns the y value of the point.
        /// @return double The y value of the point.
        double                  getY();

        /// @brief Sets the x value of the point.
        /// @param x What the new x value of the point will be.
        void                    setX(double x);

        /// @brief Sets the y value of the point.
        /// @param y What the new y value of the point will be.
        void                    setY(double y);

        bool                    operator==(Point left);
        bool                    operator != ( Point );

};

#endif
///@}

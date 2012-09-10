///@file
///@brief File for the Timer class.
///
/// This will allow the programmer to use timers.
///
/// They will have a 1 milisecond resolution.
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

#ifndef __TIMER_H__
#define __TIMER_H__

///@brief Class that handles the timers.
///
/// Will allow the programmer to use high resolution timers.
class Timer
{
  private:
        unsigned int            startTime;
        unsigned int            stopTime;
        unsigned int            beforeTime;
        bool                    running;

  public:

        /// @brief Default constructor
        /// Creates a timer that is not started.
        Timer();

        /// @brief Starts a stopped timer.
        ///
        /// Starts a timer that is not currently running.
        /// Will cause no effect if called on an already running timer.
        void                    start();

        /// @brief Resets the timer back to zero seconds.
        ///
        /// Resets the timer back to zero seconds. This does not
        /// however stop the timer if it is running.
        void                    reset();

        /// @brief Stops the running timer.
        ///
        /// Stops the timer if it is running. Does not reset the
        /// time back to zero. Nothing will happen if you call this
        /// on an already stopped timer.
        void                    stop();

        /// @brief Returns the amount of miliseconds that have passed on the timer.
        /// @return unsigned int The number of miliseconds that have passed.
        unsigned int            getTimePassed();

        /// @brief Adds a certain amount of miliseconds onto the timer.
        /// @param miliSecs The number of miliseconds to add to the timer.
        /// A negative number can be passed in to take off time.
        void                    addTime(int iMilisecs_);

        /// @brief Checks whether or not the timer has passed a certain amount of miliseconds.
        /// @param miliSecs The number of miliseconds that is in question.
        /// @return bool Whether or not the timer passed that number of miliseconds.
        bool                    hasPassedTime(int iMilisecs_);

};
#endif
///@}

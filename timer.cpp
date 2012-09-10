#include "timer.h"
#include <cstdlib>
#include <SDL/SDL.h>

Timer::Timer()
{
    startTime = 0;
    stopTime = 0;
    beforeTime = 0;
    running = false;
}


void Timer::start()
{
    //Only start the timer if it wasn't running prior, otherwise do nothing
    if(!running)
    {
        //The new start time is now plus whatever the timer had on it previously
        startTime = SDL_GetTicks() - beforeTime;
        running = true;
    }
}

void Timer::reset()
{
    //Set all values to now meaning no time has passed
    startTime = SDL_GetTicks();
    stopTime = SDL_GetTicks();
    beforeTime = 0;
}

void Timer::stop()
{
    //Only stop the timer if it was running prior, otherwise do nothing
    if(running)
    {
        //Record the amount of time on the timer just in case we want to restart
        //the timer again. If we do then we want to remember how much time it
        //had on it so we can continue to add to it.
        beforeTime = SDL_GetTicks() - startTime;
        stopTime = SDL_GetTicks();
    }
    running = false;
}

unsigned int Timer::getTimePassed()
{
    if(running)
    {
        //If the timer is running, the time on it is now minus the start time.
        unsigned int nowTime = SDL_GetTicks();
        return nowTime - startTime;
    }
    else
    {
        //If the timer is stopped, the time on it is the time we stopped it
        //minus the time we started it.
        return stopTime - startTime;
    }
}

void Timer::addTime(int milisecs)
{
    //If the timer is running, then subtract the amount of given miliseconds
    //from the start time.
    if(running)
    {
        startTime -= milisecs;
    }
    //If the timer is stopped, then subtract the amount of given miliseconds
    //from the start time as well as add the amount of miliseconds to the
    //beforetime just in case we want to restart the timer again, we want to
    //have those seconds added on.
    else
    {
        startTime -= milisecs;
        beforeTime += milisecs;
    }
}

bool Timer::hasPassedTime(int milisecs)
{
    return milisecs <= getTimePassed();
}

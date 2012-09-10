#include "joystick.h"
#include <SDL/SDL.h>
#include <cstdlib>
#include <stdio.h>

Joystick::Joystick()
{
	m_iNum = 0;
	m_pJoystick = NULL;
	m_iAxes = 0;
	m_iButtons = 0;
	m_iHats = 0;
	m_iBalls = 0;
	m_sName = "";
}

Joystick::Joystick(int iNum_)
{
	m_iNum = iNum_;
	m_pJoystick = NULL;
	m_iAxes = 0;
	m_iButtons = 0;
	m_iHats = 0;
	m_iBalls = 0;
	m_sName = "";
}

Joystick::~Joystick()
{
	SDL_JoystickClose(m_pJoystick);
}

void Joystick::init()
{
    //Open the joystick and record all the data about the joystick.
	m_pJoystick = SDL_JoystickOpen(m_iNum);
	m_iAxes     = SDL_JoystickNumAxes(m_pJoystick);
	m_iButtons  = SDL_JoystickNumButtons(m_pJoystick);
	m_iHats     = SDL_JoystickNumHats(m_pJoystick);
	m_iBalls    = SDL_JoystickNumBalls(m_pJoystick);
	m_sName     = SDL_JoystickName(m_iNum);
}

bool Joystick::buttonPressed(int iButtonNum_)
{
	SDL_JoystickUpdate();

    //Returns true if the button is being pressed, else returns false.
	return SDL_JoystickGetButton(m_pJoystick, iButtonNum_);
}

double Joystick::getAxisLocation(int iAxis_)
{
	SDL_JoystickUpdate();

	//Returns the percentage the joystick is being pressed in that direction.
	return SDL_JoystickGetAxis(m_pJoystick, iAxis_) / (MAX_AXIS_MOVEMENT * 1.0);
}

Uint8 Joystick::getHatLocation(int iHat_)
{
	SDL_JoystickUpdate();
    return SDL_JoystickGetHat(m_pJoystick, iHat_);
}

bool Joystick::hatPressed(Uint8 iHatDir_)
{
    //If there are no hats detected, obviously no hat was pressed so return
    //false.
    if(m_iHats == 0)
        return false;

    SDL_JoystickUpdate();

    //Record the state of the joystick and bitwise AND it with the inputted
    //Hat direction.
    Uint8 iValue = SDL_JoystickGetHat(m_pJoystick, 0) & iHatDir_;

    //If the value of the variable after it was bitwise ANDed is zero, then that
    //direction was not pressed.
    if(iValue == 0)
        return false;
    else
        return true;
}

int Joystick::getNumButtons()
{
    return m_iButtons;
}

int Joystick::getNumHats()
{
    return m_iHats;
}

int Joystick::getNumAxes()
{
    return m_iAxes;
}

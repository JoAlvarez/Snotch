#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#include <string>
#include <SDL/SDL.h>

#define MAX_AXIS_MOVEMENT 32767.0

#define JOYSTICK_0 0
#define JOYSTICK_1 1
#define JOYSTICK_2 2
#define JOYSTICK_3 3
#define JOYSTICK_4 4
#define JOYSTICK_5 5
#define JOYSTICK_6 6
#define JOYSTICK_7 7

#define X_AXIS_LEFT 0
#define Y_AXIS_LEFT 1
#define X_AXIS_RIGHT 2
#define Y_AXIS_RIGHT 3


using namespace std;

class Joystick
{

	private:

		int					m_iNum;      //What number joystick it is.
		int					m_iAxes;     //Number of axes the joystick has.
		int					m_iButtons;  //Number of buttons on the joystick.
		int					m_iHats;     //Number of hats on the joystick.
		int					m_iBalls;    //Number of balls on the joystick.
		string				m_sName;     //The name of the joystick.
		SDL_Joystick*		m_pJoystick; //The SDL joystick pointer.

	public:

		Joystick();
		Joystick(int iNum_);
		~Joystick();

		void				init();

		bool				buttonPressed(int iNum_);
		bool                hatPressed(Uint8 iHatDir_);
		double				getAxisLocation(int iAxis_);
		Uint8				getHatLocation(int iHat_);
		int					getBallMotion(int iBall_);
		int                 getNumButtons();
		int                 getNumHats();
		int                 getNumAxes();


};

#endif


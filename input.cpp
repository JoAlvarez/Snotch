#include "input.h"
#include <sstream>

using namespace std;

//Give initial values to the static member variables.
Input* Input::instance = NULL;
int Input::referenceCount = 0;

//Default constructor for the input class.
Input::Input()
{
    mouseLeftDown       = false;
    mouseRightDown      = false;
    mouseMiddleDown     = false;
    mouseXMoveRelative  = 0;
    mouseYMoveRelative  = 0;
    mouseScrollRelative = 0;

    numJoysticks = 0;

    keyInput = "";
    joyInput = "";
    mouseInput = "";

    //Build the map that matches the keys on the keyboard to the SDL
    //representation of SDLKeys. This will be a fast approach when trying
    //to figure out what SDLKey matches a given string key. Searching for that
    //answer should be of only logarithmic time using this map rather than
    //linear which would be much slower.
    keyMap["a"] = SDLK_a;    keyMap["A"] = SDLK_a;
    keyMap["b"] = SDLK_b;    keyMap["B"] = SDLK_b;
    keyMap["c"] = SDLK_c;    keyMap["C"] = SDLK_c;
    keyMap["d"] = SDLK_d;    keyMap["D"] = SDLK_d;
    keyMap["e"] = SDLK_e;    keyMap["E"] = SDLK_e;
    keyMap["f"] = SDLK_f;    keyMap["F"] = SDLK_f;
    keyMap["g"] = SDLK_g;    keyMap["G"] = SDLK_g;
    keyMap["h"] = SDLK_h;    keyMap["H"] = SDLK_h;
    keyMap["i"] = SDLK_i;    keyMap["I"] = SDLK_i;
    keyMap["j"] = SDLK_j;    keyMap["J"] = SDLK_j;
    keyMap["k"] = SDLK_k;    keyMap["K"] = SDLK_k;
    keyMap["l"] = SDLK_l;    keyMap["L"] = SDLK_l;
    keyMap["m"] = SDLK_m;    keyMap["M"] = SDLK_m;
    keyMap["n"] = SDLK_n;    keyMap["N"] = SDLK_n;
    keyMap["o"] = SDLK_o;    keyMap["O"] = SDLK_o;
    keyMap["p"] = SDLK_p;    keyMap["P"] = SDLK_p;
    keyMap["q"] = SDLK_q;    keyMap["Q"] = SDLK_q;
    keyMap["r"] = SDLK_r;    keyMap["R"] = SDLK_r;
    keyMap["s"] = SDLK_s;    keyMap["S"] = SDLK_s;
    keyMap["t"] = SDLK_t;    keyMap["T"] = SDLK_t;
    keyMap["u"] = SDLK_u;    keyMap["U"] = SDLK_u;
    keyMap["v"] = SDLK_v;    keyMap["V"] = SDLK_v;
    keyMap["w"] = SDLK_w;    keyMap["W"] = SDLK_w;
    keyMap["x"] = SDLK_x;    keyMap["X"] = SDLK_x;
    keyMap["y"] = SDLK_y;    keyMap["Y"] = SDLK_y;
    keyMap["z"] = SDLK_z;    keyMap["Z"] = SDLK_z;

    keyMap["0"] = SDLK_0;    keyMap[")"] = SDLK_0;
    keyMap["1"] = SDLK_1;    keyMap["!"] = SDLK_1;
    keyMap["2"] = SDLK_2;    keyMap["@"] = SDLK_2;
    keyMap["3"] = SDLK_3;    keyMap["#"] = SDLK_3;
    keyMap["4"] = SDLK_4;    keyMap["$"] = SDLK_4;
    keyMap["5"] = SDLK_5;    keyMap["%"] = SDLK_5;
    keyMap["6"] = SDLK_6;    keyMap["^"] = SDLK_6;
    keyMap["7"] = SDLK_7;    keyMap["&"] = SDLK_7;
    keyMap["8"] = SDLK_8;    keyMap["*"] = SDLK_8;
    keyMap["9"] = SDLK_9;    keyMap["("] = SDLK_9;

    keyMap[","] = SDLK_COMMA;        keyMap["<"] = SDLK_COMMA;
    keyMap["."] = SDLK_PERIOD;       keyMap[">"] = SDLK_PERIOD;
    keyMap["/"] = SDLK_SLASH;        keyMap["?"] = SDLK_SLASH;
    keyMap[";"] = SDLK_SEMICOLON;    keyMap[":"] = SDLK_SEMICOLON;
    keyMap["'"] = SDLK_QUOTE;        keyMap["\""] = SDLK_QUOTE;
    keyMap["["] = SDLK_LEFTBRACKET;  keyMap["{"] = SDLK_LEFTBRACKET;
    keyMap["]"] = SDLK_RIGHTBRACKET; keyMap["}"] = SDLK_RIGHTBRACKET;
    keyMap["\\"] = SDLK_BACKSLASH;   keyMap["|"] = SDLK_BACKSLASH;
    keyMap["-"] = SDLK_MINUS;        keyMap["_"] = SDLK_MINUS;
    keyMap["="] = SDLK_EQUALS;       keyMap["+"] = SDLK_EQUALS;
    keyMap["`"] = SDLK_BACKQUOTE;    keyMap["~"] = SDLK_BACKQUOTE;

    keyMap["F1"] = SDLK_F1;      keyMap["F2"] = SDLK_F2;
    keyMap["F3"] = SDLK_F3;      keyMap["F4"] = SDLK_F4;
    keyMap["F5"] = SDLK_F5;      keyMap["F6"] = SDLK_F6;
    keyMap["F7"] = SDLK_F7;      keyMap["F8"] = SDLK_F8;
    keyMap["F9"] = SDLK_F9;      keyMap["F10"] = SDLK_F10;
    keyMap["F11"] = SDLK_F11;    keyMap["F12"] = SDLK_F12;

    keyMap["up"] = SDLK_UP;        keyMap["left"] = SDLK_LEFT;
    keyMap["down"] = SDLK_DOWN;    keyMap["right"] = SDLK_RIGHT;

    keyMap["backspace"] = SDLK_BACKSPACE;    keyMap["tab"] = SDLK_TAB;
    keyMap["enter"] = SDLK_RETURN;           keyMap["esc"] = SDLK_ESCAPE;
    keyMap["insert"] = SDLK_INSERT;          keyMap["home"] = SDLK_HOME;
    keyMap["end"] = SDLK_END;                keyMap["lalt"] = SDLK_LALT;
    keyMap["pageup"] = SDLK_PAGEUP;          keyMap["lctrl"] = SDLK_LCTRL;
    keyMap["pagedown"] = SDLK_PAGEDOWN;      keyMap["ralt"] = SDLK_RALT;
    keyMap["delete"] = SDLK_DELETE;          keyMap["rctrl"] = SDLK_RCTRL;
    keyMap["space"] = SDLK_SPACE;

}

//Initializes the Input class.
void Input::init()
{
    //Get the Window singleton pointer.
    window = Window::getInstance();

    //Figure out how many joysticks are detected.
    numJoysticks = SDL_NumJoysticks();

    //For every joystick detected, add it to the Joystick vector and initialize
    //it.
    for(int i = 0; i < numJoysticks; ++i)
	{
		joystick.push_back(i);
		joystick[i].init();
	}

    //Enable key repeating when a key is held down, similar to Windows event
    //system.
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

}

//Returns the input singleton pointer for others to use.
Input* Input::getInstance()
{
    //If nobody has this pointer, make it and initialize it.
    if(instance == NULL)
    {
        instance = new Input;
        instance->init();
    }
    //Increment the number of times this pointer has been given out
    //and return it.
    ++referenceCount;
    return instance;
}

//Free all dynamically allocated memory
void Input::destroy()
{
    window->release();
    if(instance)
    {
        delete instance;
        instance = NULL;
    }
}

//Allows something to get rid of the singleton pointer
//they have a hold of.
void Input::release()
{
    //Decrement the number of things that currently
    //have the singleton pointer. If there are no
    //more people with the pointer, then we should
    //destroy it to prevent memory leaks.
    if( --referenceCount < 1 )
    {
        destroy();
    }
    if(referenceCount < 0)
        referenceCount = 0;
}

bool Input::handleEvents()
{
    // Loop that processes events while there are some in the event queue.
    // Skips the entire loop if no events are in the queue.
        while (SDL_PollEvent(&event))
        {
            //First switch checks what kind of message the event is.
            //Ex. Mouse Event, Keyboard Event, etc.
            switch (event.type)
            {

                //If the X is clicked to quit the program, set the input
                //to say quit which should be noticed later in the program
                //and should quit then.
                case SDL_QUIT:
                    return false;
                break;

                //Event Caused By Mouse Movement
				case SDL_MOUSEMOTION:
				{
                    //Check what the relative movement of the mouse was and
                    //record that to the member variables.
					mouseXMoveRelative = event.motion.xrel;

					//Since SDLs window is backwards in the y direction, we
                    //negate the relative y movement to make it positive when
                    //the mouse was moved up and negative when moved down.
					mouseYMoveRelative = -event.motion.yrel;

                    //Take the window coordinates of the mouse and convert it to the
                    //game coordinates.
					mouseXlocation = event.motion.x *
                                    (window->rightCoord() - window->leftCoord()) /
                                     window->getWidth() + window->leftCoord();
					mouseYlocation = (window->topCoord() - window->bottomCoord()) - event.motion.y *
                                     (window->topCoord() - window->bottomCoord()) / window->getHeight() +
                                      window->bottomCoord();

				}
				break;

                //Event caused by mouse button pressed down.
				case SDL_MOUSEBUTTONDOWN:
				{
				    //Start switch that checks which button was pressed down.
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
							mouseLeftDown = true;
							mouseInput = "Left Down";
							break;
						case SDL_BUTTON_RIGHT:
							mouseRightDown = true;
							mouseInput = "Right Down";
							break;
                        case SDL_BUTTON_MIDDLE:
                            mouseMiddleDown = true;
                            mouseInput = "Middle Down";
                            break;
					}
				}
				break;

                //Event caused by mouse button being released up.
				case SDL_MOUSEBUTTONUP:
				{
				    //Start switch that checks which button was released up.
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
							mouseLeftDown = false;
							mouseInput = "Left Up";
							break;
						case SDL_BUTTON_RIGHT:
							mouseRightDown = false;
							mouseInput = "Right Up";
							break;
                        case SDL_BUTTON_MIDDLE:
                            mouseMiddleDown = true;
                            mouseInput = "Middle Up";
                            break;
					}
				}
				break;

                case SDL_JOYBUTTONDOWN:
                {
                    //We are going to put the Joystick input in the form
                    //                "Joy# But#"
                    //Where the first number if the number of the joystick
                    //and the second number if the number of the button pressed.


                    //So we start by putting "Joy" first.
                    joyInput = "Joy";

                    //Now to get the number of the joystick that had the button
                    //pressed and convert that number to string so we can add it
                    //to our JoyInput string.
                    stringstream stringStream;
                    int iJoystickNum = event.jbutton.which;
                    stringStream << iJoystickNum;
                    string sJoystickNum = "";
                    stringStream >> sJoystickNum;

                    //Add the # joystick to the string followed by " But".
                    sJoystickNum = sJoystickNum + " But";
                    joyInput = joyInput + sJoystickNum;

                    //Last we get the number of the button pressed and convert
                    //that number to string to add it onto the end of the
                    //JoyInput string.
                    stringstream stringStream2;
                    int iButtonNum = event.jbutton.button;
                    stringStream2 << iButtonNum;
                    string sButtonNum = "";
                    stringStream2 >> sButtonNum;
                    joyInput = joyInput + sButtonNum;
                }
                break;

                case SDL_JOYHATMOTION:
                {
                    //We are going to put the Joystick input in the form
                    //                "Joy# Hat#"
                    //Where the first number if the number of the joystick
                    //and the second number if the number of the button pressed.


                    //So we start by putting "Joy" first.
                    joyInput = "Joy";

                    //Now to get the number of the joystick that had the button
                    //pressed and convert that number to string so we can add it
                    //to our JoyInput string.
                    stringstream stringStream;
                    int iJoystickNum = event.jbutton.which;
                    stringStream << iJoystickNum;
                    string sJoystickNum = "";
                    stringStream >> sJoystickNum;

                    //Add the # joystick to the string followed by " But".
                    sJoystickNum = sJoystickNum + " Hat";
                    joyInput = joyInput + sJoystickNum;

                    //Last we get the number of the button pressed and convert
                    //that number to string to add it onto the end of the
                    //JoyInput string.
                    stringstream stringStream2;

                    Uint8 iHatDir = event.jhat.value;

                    if(iHatDir & SDL_HAT_UP)
                        joyInput = joyInput + "UP";
                    else if(iHatDir & SDL_HAT_DOWN)
                        joyInput = joyInput + "DOWN";
                    else if(iHatDir & SDL_HAT_LEFT)
                        joyInput = joyInput + "LEFT";
                    else if(iHatDir & SDL_HAT_RIGHT)
                        joyInput = joyInput + "RIGHT";
                    else
                        joyInput = joyInput + "CENTERED";
                }
                break;


                //Event caused by a key being pressed down.
                case SDL_KEYDOWN:
                {
                    //Pump events through and check whether or not the
                    //shift or capslock are being pressed.
                	SDLMod mod;
					SDL_PumpEvents();
					mod = SDL_GetModState();
					bool bShift = mod & KMOD_SHIFT;
					bool bCaps  = mod & KMOD_CAPS;

                    //In order to capitalize a letter, either the shift or
                    //capslock has to be down, but not both.
					bool bCapital = (bShift || bCaps) && !(bShift && bCaps);

                    //Start switch to check which key was pressed down.
                	switch(event.key.keysym.sym)
                	{
						case SDLK_a:
							if(bCapital)
								keyInput = "A";
							else
								keyInput = "a";
							break;

						case SDLK_b:
							if(bCapital)
								keyInput = "B";
							else
								keyInput = "b";
							break;

						case SDLK_c:
							if(bCapital)
								keyInput = "C";
							else
								keyInput = "c";
							break;

						case SDLK_d:
							if(bCapital)
								keyInput = "D";
							else
								keyInput = "d";
							break;

						case SDLK_e:
							if(bCapital)
								keyInput = "E";
							else
								keyInput = "e";
							break;

						case SDLK_f:
							if(bCapital)
								keyInput = "F";
							else
								keyInput = "f";
							break;

						case SDLK_g:
							if(bCapital)
								keyInput = "G";
							else
								keyInput = "g";
							break;

						case SDLK_h:
							if(bCapital)
								keyInput = "H";
							else
								keyInput = "h";
							break;

						case SDLK_i:
							if(bCapital)
								keyInput = "I";
							else
								keyInput = "i";
							break;

						case SDLK_j:
							if(bCapital)
								keyInput = "J";
							else
								keyInput = "j";
							break;

						case SDLK_k:
							if(bCapital)
								keyInput = "K";
							else
								keyInput = "k";
							break;

						case SDLK_l:
							if(bCapital)
								keyInput = "L";
							else
								keyInput = "l";
							break;

						case SDLK_m:
							if(bCapital)
								keyInput = "M";
							else
								keyInput = "m";
							break;

						case SDLK_n:
							if(bCapital)
								keyInput = "N";
							else
								keyInput = "n";
							break;

						case SDLK_o:
							if(bCapital)
								keyInput = "O";
							else
								keyInput = "o";
							break;

						case SDLK_p:
							if(bCapital)
								keyInput = "P";
							else
								keyInput = "p";
							break;

						case SDLK_q:
							if(bCapital)
								keyInput = "Q";
							else
								keyInput = "q";
							break;

						case SDLK_r:
							if(bCapital)
								keyInput = "R";
							else
								keyInput = "r";
							break;

						case SDLK_s:
							if(bCapital)
								keyInput = "S";
							else
								keyInput = "s";
							break;

						case SDLK_t:
							if(bCapital)
								keyInput = "T";
							else
								keyInput = "t";
							break;

						case SDLK_u:
							if(bCapital)
								keyInput = "U";
							else
								keyInput = "u";
							break;

						case SDLK_v:
							if(bCapital)
								keyInput = "V";
							else
								keyInput = "v";
							break;

						case SDLK_w:
							if(bCapital)
								keyInput = "W";
							else
								keyInput = "w";
							break;

						case SDLK_x:
							if(bCapital)
								keyInput = "X";
							else
								keyInput = "x";
							break;

						case SDLK_y:
							if(bCapital)
								keyInput = "Y";
							else
								keyInput = "y";
							break;

						case SDLK_z:
							if(bCapital)
								keyInput = "Z";
							else
								keyInput = "z";
							break;

						case SDLK_0:
							if(bShift)
								keyInput = ")";
							else
								keyInput = "0";
							break;

						case SDLK_9:
							if(bShift)
								keyInput = "(";
							else
								keyInput = "9";
							break;

						case SDLK_8:
							if(bShift)
								keyInput = "*";
							else
								keyInput = "8";
							break;

						case SDLK_7:
							if(bShift)
								keyInput = "&";
							else
								keyInput = "7";
							break;

						case SDLK_6:
							if(bShift)
								keyInput = "^";
							else
								keyInput = "6";
							break;

						case SDLK_5:
							if(bShift)
								keyInput = "%";
							else
								keyInput = "5";
							break;

						case SDLK_4:
							if(bShift)
								keyInput = "$";
							else
								keyInput = "4";
							break;

						case SDLK_3:
							if(bShift)
								keyInput = "#";
							else
								keyInput = "3";
							break;

						case SDLK_2:
							if(bShift)
								keyInput = "@";
							else
								keyInput = "2";
							break;

						case SDLK_1:
							if(bShift)
								keyInput = "!";
							else
								keyInput = "1";
							break;

						case SDLK_QUOTE:
							if(bShift)
								keyInput = "\"";
							else
								keyInput = "'";
							break;

						case SDLK_EQUALS:
							if(bShift)
								keyInput = "+";
							else
								keyInput = "=";
							break;

						case SDLK_COMMA:
							if(bShift)
								keyInput = "<";
							else
								keyInput = ",";
							break;

						case SDLK_SEMICOLON:
							if(bShift)
								keyInput = ":";
							else
								keyInput = ";";
							break;

						case SDLK_SLASH:
							if(bShift)
								keyInput = "?";
							else
								keyInput = "/";
							break;

						case SDLK_LEFTBRACKET:
							if(bShift)
								keyInput = "{";
							else
								keyInput = "[";
							break;

						case SDLK_BACKSLASH:
							if(bShift)
								keyInput = "|";
							else
								keyInput = "\\";
							break;

						case SDLK_RIGHTBRACKET:
							if(bShift)
								keyInput = "}";
							else
								keyInput = "]";
							break;

						case SDLK_MINUS:
							if(bShift)
								keyInput = "_";
							else
								keyInput = "-";
							break;

						case SDLK_PERIOD:
							if(bShift)
								keyInput = ">";
							else
								keyInput = ".";
							break;

						case SDLK_BACKQUOTE:
							if(bShift)
								keyInput = "~";
							else
								keyInput = "`";
							break;

						case SDLK_UP:
							keyInput = "up";
							break;

						case SDLK_DOWN:
							keyInput = "down";
							break;

						case SDLK_LEFT:
							keyInput = "left";
							break;

						case SDLK_RIGHT:
							keyInput = "right";
							break;

						case SDLK_BACKSPACE:
							keyInput = "backspace";
							break;

						case SDLK_TAB:
							keyInput = "tab";
							break;

						case SDLK_RETURN:
							keyInput = "enter";
							break;

						case SDLK_ESCAPE:
							keyInput = "esc";
							break;

						case SDLK_SPACE:
							keyInput = "space";
							break;

						case SDLK_DELETE:
							keyInput = "delete";
							break;

						case SDLK_INSERT:
							keyInput = "insert";
							break;

						case SDLK_HOME:
							keyInput = "home";
							break;

						case SDLK_END:
							keyInput = "end";
							break;

						case SDLK_PAGEUP:
							keyInput = "pageup";
							break;

						case SDLK_PAGEDOWN:
							keyInput = "pagedown";
							break;

						case SDLK_PAUSE:
							keyInput = "pause";
							break;

						case SDLK_F1:
							keyInput = "F1";
							break;

						case SDLK_F2:
							keyInput = "F2";
							break;

						case SDLK_F3:
							keyInput = "F3";
							break;

						case SDLK_F4:
							keyInput = "F4";
							break;

						case SDLK_F5:
							keyInput = "F5";
							break;

						case SDLK_F6:
							keyInput = "F6";
							break;

						case SDLK_F7:
							keyInput = "F7";
							break;

						case SDLK_F8:
							keyInput = "F8";
							break;

						case SDLK_F9:
							keyInput = "F9";
							break;

						case SDLK_F10:
							keyInput = "F10";
							break;

						case SDLK_F11:
							keyInput = "F11";
							break;

						case SDLK_F12:
							keyInput = "F12";
							break;

						case SDLK_RSHIFT:
                            keyInput = "rshift";
                            break;

						case SDLK_LSHIFT:
							keyInput = "lshift";
							break;

						case SDLK_RCTRL:
                            keyInput = "rctrl";
                            break;

						case SDLK_LCTRL:
							keyInput = "lctrl";
							break;

						case SDLK_RALT:
                            keyInput = "ralt";
                            break;

						case SDLK_LALT:
							keyInput = "lalt";
                            break;
                	}
                }
            }
        } // END MESSAGE PROCESSING
        return true;
}

//Resets the input back to nothing.
void Input::resetInput()
{
    keyInput = "";
    mouseInput = "";
    joyInput = "";
}

//Returns the mouse X location in the game.
double Input::getMouseXloc()
{
    return mouseXlocation;
}

//Returns the mouse Y location in the game.
double Input::getMouseYloc()
{
    return mouseYlocation;
}

//Returns the mouse location in the game.
Point Input::getMouseLoc()
{
    return Point(mouseXlocation, mouseYlocation);
}

//Returns the X percentage of the mouse location.
//0.0 = all the way left. 1.0 = all the way right.
double Input::getMouseXPercentage()
{
    return (mouseXlocation - window->leftCoord()) /
           (window->rightCoord() - window->leftCoord());
}

//Returns the Y percentage of the mouse location.
//0.0 = at the very bottom. 1.0 = at the very top.
double Input::getMouseYPercentage()
{
    return (mouseYlocation - window->bottomCoord()) /
           (window->topCoord() - window->bottomCoord());
}

//Returns if the specified key is down or not.
bool Input::isKeyDown(string key)
{
    //If the key code has nothing in it, obviously there's nothing to check.
    if(key == "")
        return false;

    //Get the state of the keyboard and all the keys.
    SDL_PumpEvents();
    Uint8* keyboard;
    keyboard = SDL_GetKeyState(NULL);

    //Put the string key in the keymap which will return what SDLKey
    //corresponds with the string key. With the SDLKey, now we check the
    //keyboard state to see if the key was pressed.
    return (keyboard[keyMap[key]]);
}

//Returns if the specified joystick button is down or not.
bool Input::isJoyButtonDown(string joyButton)
{
    //If the string has less than 9 characters (implying that something is
    //wrong with the input), or no joysticks are detected, just return false.
    if(numJoysticks == 0 || joyButton.size() < 9)
        return false;

    //The string passed in should be of the format
    //
    //   "Joy# But#"   Ex. "Joy2 But3" - Means Button 3 on Joystick 2
    //
    //Which should show what joystick number we are inquiring and what
    //button on that joystick are we asking about. So we must exact those two
    //numbers to make our check.

    //So to get that info out, we need to know where the space is at in between
    //Joy# and But#
    int indexAtSpace = 0;
    while(joyButton.substr(indexAtSpace, 1) != " " &&
          indexAtSpace < joyButton.size())
    {
        ++indexAtSpace;
        if(indexAtSpace >= joyButton.size())
            break;
    }

    //If the space is not in a possible space, something is wrong with the input
    //so just return false.
    if(indexAtSpace < 4 || indexAtSpace > joyButton.size())
        return false;

    //Extracting Joystick Number.

    //Take the first number out of the string behind "Joy" which tells us
    //what number joystick we are going to look at.
    string sJoyNumber;
    sJoyNumber = joyButton.substr(3, indexAtSpace - 3);

    //Convert the string number to an actual integer so we can use it.
    stringstream stringStream;
    stringStream << sJoyNumber;
    int iJoyNumber;
    stringStream >> iJoyNumber;

    //If the joystick number that was exatracted is bigger than the number of
    //joysticks detected, simply return false.
    if(iJoyNumber > numJoysticks - 1)
        return false;

    //Extracting Button Number

    //Get the second number out of the string behind "But" which tells us what
    //button we are going to check.
    string sButtonNumber;
    sButtonNumber = joyButton.substr(indexAtSpace + 4,
                    joyButton.size() - (indexAtSpace + 4));

    //Convert the string number to an integer so we can use it properly.
    stringstream stringStream4;
    stringStream4 << sButtonNumber;
    int iButtonNumber;
    stringStream4 >> iButtonNumber;

    //If the button passed in is bigger than the number of buttons, just
    //return false.
    if(iButtonNumber > joystick[iJoyNumber].getNumButtons() - 1)
        return false;

    //Return whether or not that button was pressed.
    return joystick[iJoyNumber].buttonPressed(iButtonNumber);
}

//Returns if the specified joystick hat is being pressed.
bool Input::isHatDirPressed(string joyHatDir)
{
    //If the string has less than 9 characters (implying that something is
    //wrong with the input), or no joysticks are detected, just return false.
    if(numJoysticks == 0 || joyHatDir.size() < 10)
        return false;

    //The string passed in should be of the format
    //
    //   "Joy# Hat'Dir'"     Ex. Joy1 HatDOWN
    //
    //Which should show what joystick number we are inquiring and what
    //button on that joystick are we asking about. So we must exact those two
    //numbers to make our check.

    //So to get that info out, we need to know where the space is at in between
    //Joy# and Hat'Dir'
    int indexAtSpace = 0;
    while(joyHatDir.substr(indexAtSpace, 1) != " " &&
          indexAtSpace < joyHatDir.size())
    {
        ++indexAtSpace;
        if(indexAtSpace >= joyHatDir.size())
            break;
    }

    //If the space is not in a possible place, something was wrong with the
    //input so return false.
    if(indexAtSpace < 4 || indexAtSpace > joyHatDir.size())
        return false;

    //Extracting Joystick Number.

    //Take the first number out of the string behind "Joy" which tells us
    //what number joystick we are going to look at.
    string sJoyNumber;
    sJoyNumber = joyHatDir.substr(3, indexAtSpace - 3);

    //Convert the string number to an actual integer so we can use it.
    stringstream sStringStream;
    sStringStream << sJoyNumber;
    int iJoyNumber;
    sStringStream >> iJoyNumber;

    //If the joystick number that was exatracted is bigger than the number of
    //joysticks detected, simply return false.
    if(iJoyNumber > numJoysticks - 1)
        return false;

    //Extracting Hat Direction

    //Take the 'Dir' part out of string so we can check if that direction was
    //pressed.
    string sHatDir;
    sHatDir = joyHatDir.substr(indexAtSpace + 4,
                               joyHatDir.size() - (indexAtSpace + 4));

    //Check the direction and return whether or not that direction was pressed.
    if(sHatDir == "UP")
    {
        return joystick[iJoyNumber].hatPressed(SDL_HAT_UP);
    }
    else if(sHatDir == "DOWN")
    {
        return joystick[iJoyNumber].hatPressed(SDL_HAT_DOWN);
    }
    else if(sHatDir == "LEFT")
    {
        return joystick[iJoyNumber].hatPressed(SDL_HAT_LEFT);
    }
    else if(sHatDir == "RIGHT")
    {
        return joystick[iJoyNumber].hatPressed(SDL_HAT_RIGHT);
    }

    //Direction did not equal UP DOWN LEFT or RIGHT so something is wrong with
    //the input so return false.
    return false;
}

//Return the percentage an axis on a joystick is being pressed.
double Input::getJoystickAxisPos(int joystickNum, int axisNum)
{
    //If there are no joysticks detected or the number passed in is higher than
    //the number of joysticks detected, obviously nothing was pressed then.
	if(numJoysticks == 0 || joystickNum > numJoysticks - 1)
		return 0;
    //If the axis number passed in is bigger than the number of axes on that
    //joystick, then obviously that axis was not pressed at all.
    if(axisNum > joystick[joystickNum].getNumAxes() - 1)
        return 0;

    //If the axis is a even number it deals with the X axis so treat it normal.
	if(axisNum % 2 == 0)
		return joystick[joystickNum].getAxisLocation(axisNum);
    //If the axis is a odd number it deals with the Y axis. Remember that SDL
    //windows have the positive Y in the opposite direction than what we see as
    //positive so just negate the value.
	else
		return joystick[joystickNum].getAxisLocation(axisNum) * -1;
}

//Return the buffered key input.
string Input::getKeyInput()
{
    return keyInput;
}

//Return the buffered joystick input.
string Input::getJoyInput()
{
    return joyInput;
}

//Return the buffered mouse input.
string Input::getMouseInput()
{
    return mouseInput;
}

//Return is the left mouse button is down.
bool Input::leftMouseDown()
{
    return mouseLeftDown;
}

//Return if the right mouse button is down.
bool Input::rightMouseDown()
{
    return mouseRightDown;
}

//Set the x location of the mouse.
void Input::setMouseX(double mouseX)
{
    this->mouseXlocation = mouseX;
}

//Set the Y location of the mouse.
void Input::setMouseY(double mouseY)
{
    this->mouseYlocation = mouseY;
}

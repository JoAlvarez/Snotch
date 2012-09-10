///@file
///@brief File for the Input class.
///
/// This will be able to handle all the forms of input:
///
/// Buffered and unbuffered Keyboard input, Mouse tracking,
/// and joystick inputs.
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

#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL/SDL.h>
#include <vector>
#include <string>
#include <map>
#include "window.h"
#include "joystick.h"
#include "point.h"


using namespace std;

///@brief Class that handles the input.
///
/// This will take care of all the input checking and handling.
class Input
{
  private:

        static Input*                 instance;            //Singleton pointer to the
                                                           //Input object.
        static int                    referenceCount;      //Number of things that currently
                                                           //have the singleton pointer available.

        SDL_Event                     event;               //Event variable that holds
                                                           //events to be processed.

        bool			              mouseLeftDown;       //Is left mouse down.
        bool			              mouseRightDown;      //Is right mouse down.
        bool                          mouseMiddleDown;     //Is middle mouse down.

        double                        mouseXlocation;
        double                        mouseYlocation;

        double                        mouseXMoveRelative;  //Tracks relative mouse x
                                                           //movement.
        double                        mouseYMoveRelative;  //Tracks relative mouse y
                                                           //movement.
        int                           mouseScrollRelative; //Tracks relative mouse
                                                           //scroll movement.

        std::string                   keyInput;            //Holds the keyboard input.
        std::string                   joyInput;            //Holds the joystick input.
        std::string                   mouseInput;          //Holds the mouse input.

        int				              numJoysticks;        //Holds the number of
                                                           //joysticks detected.
        std::vector<Joystick>         joystick;            //Vector that holds all the
                                                           //detected joysticks.

        std::map<std::string, SDLKey> keyMap;              //Map that corrolates key
                                                           //presses to SDLKeys.

        Window*                       window;              //Singleton pointer to the
                                                           //Window object.

        /// @brief Default constructor for the Input class.
        Input();

        /// @brief Initializes the Input object to be used.
        void init();

        /// @brief Destroys and frees all the memory from this class.
        void destroy();

  public:

        /// @brief Gets the instance of the Input object.
        ///
        /// Use this to obtain the instance of the input object for the window.
        /// @return Input* A pointer to the instance of the Input object.
        static Input*       getInstance();

        /// @brief Releases the instance of the Input object obtained.
        ///
        /// Release the instance of the Input obtained from getInstance().
        /// This must be called on the pointer obtained from getInstance() to
        /// ensure that no memory leaks occur and that the Input object is
        /// destroyed when nobody has an instance of the object.
        void                release();


        /// @brief Will handle all events that have occured
        ///
        /// Will handle all of the events that have occured since last calling
        /// this function.  This must be called to ensure that tracking of the
        /// mouse pointer is done as well as recieving all of the buffered keyboard
        /// input. If false has been returned, then the program has been asked to be quit.
        /// @return bool True means the program is doing fine and false means the program has been
        /// asked to be quit. If false was returned, the programmer must quit the program
        /// to ensure that the program quits when asked to.
        bool                handleEvents();

        /// @brief Clears all the values in the input variables.
        ///
        /// Will reset all of the calculated inputs in handleEvents back to
        /// cleared. This must be called at the end of the simulation loop to
        /// make sure that a certain input is not seen to have been pressed
        /// when actually it was pressed along time ago in the passed.
        void                resetInput();

        /// @brief Checks to see if a keyboard key is pressed.
        ///
        /// Will return whether or not a certain key is being pressed.
        /// @param key The string value of the key in question.
        /// Example: "a" => A key, "esc" => esc key, "space" => space key
        /// @return bool Whether or not the key in question is pressed.
        bool                isKeyDown(std::string key);

        /// @brief Checks to see if a certain joystick button is pressed.
        ///
        /// Returns whether or not a certain joystick button is down.
        /// @param joyButton The joystick button in question. Must be in the
        /// format "Joy# But#". So "Joy0 But5" is asking whether or not button
        /// 5 on joystick 0 is being pressed.
        /// @return bool Whether or not that button was down.
        bool                isJoyButtonDown(std::string joyButton);

        /// @brief Checks to see if a hat direction is being pressed.
        ///
        /// Returns whether or not a certain direction on the hat is down.
        /// @param joyHatDir The hat direction in question. Must be in the format
        /// "Joy# Hat'Dir'". So "Joy2 HatLEFT" is asking whether or not the left
        /// direction is being pressed on the hat of joystick 2.
        /// @return bool Whether or not that hat direction is being pressed.
        bool                isHatDirPressed(std::string joyHatDir);

        /// @brief Sees how far in either direction a certain axis on an analog stick is being pressed.
        ///
        /// Returns a percentage of how far a certain analog axis is being pressed. The returned value will
        /// be between 1.0 and -1.0.
        /// @param joystickNum Which joystick in question.
        /// @axisNum The analog axis in question. X_AXIS_LEFT means the X axis
        /// of the left analog stick. Y_AXIS_RIGHT means the Y axis of the
        /// right analog stick. Etc.
        /// @return double The percentage of how far that joystick is being
        /// pressed in the given axis. Ranges in between 1.0 and -1.0. 0.0
        /// means it is in the center.
        double              getJoystickAxisPos(int joystickNum, int axisNum);

        /// @brief Gets the value of the buffered keyboard input.
        ///
        /// Returns the string value of the key that was pressed in the
        /// buffered input. Use this function instead of isKeyDown for
        /// things where you just want to know if that key was pressed
        /// down at that instant. Such examples might be for typing input
        /// or moving through a menu in a game.
        /// @return string The key that was being pressed if any. Empty string returned if no key was pressed.
        std::string         getKeyInput();

        /// @brief Gets the value of the joystick input.
        ///
        /// Returns the string value of the joystick button or hat direction
        /// that was hit at that instant if any.
        /// @return string The string that represents what joystick input was
        /// recieved. Will be in the form "Joy# But#" or "Joy# Hat'Dir'".
        /// Examples: "Joy3 But1" or "Joy2 HatCENTERED" or "Joy4 HatDOWN".
        std::string         getJoyInput();

        /// @brief Gets the value of the mouse input.
        ///
        /// Returns the string value of what mouse buttons were hit or released
        /// at that instanct if any.
        /// @return string The string that represents what mouse button was hit
        /// or released. Example: "Left Down" means that left mouse click was
        /// pressed down. "Right Up" means the right mouse click was just released.
        std::string         getMouseInput();

        /// @brief Gets the value of how far the mouse moved in the X during the last frame.
        ///
        /// Returns how far the mouse moved in the X direction in the last frame.
        /// Will be relevant to the coordinate system that is being used at the time.
        /// @return double How far the mouse moved in the X direction during the last frame.
        double              getMouseXRel();

        /// @brief Gets the value of how far the mouse moved in the Y during the last frame.
        ///
        /// Returns how far the mouse moved in the Y direction in the last frame.
        /// Will be relevant to the coordinate system that is being used at the time.
        /// @return double How far the mouse moved in the Y direction during the last frame.
        double              getMouseYRel();

        /// @brief Whether or not the left mouse button is down.
        ///
        /// Will return whether or not the left mouse button is currently being pressed.
        /// @return bool Whether or not it is being pressed.
        bool                leftMouseDown();

        /// @brief Whether or not the right mose button is down.
        ///
        /// Will return whether or not the right mouse button is currently being pressed.
        /// @return bool Whether or not it is being pressed.
        bool                rightMouseDown();

        /// @brief Gets the current X location of the mouse in the coordinate system.
        ///
        /// Returns at what specific location the mouse is at in the current coordinate system.
        /// @return double The X value of the location of the mouse.
        double              getMouseXloc();

        /// @brief Gets the current Y location of the mouse in the coordinate system.
        ///
        /// Returns at what specific location the mouse is at in the current coordinate system.
        /// @return double The Y value of the location of the mouse.
        double              getMouseYloc();

        /// @brief Gets the current point location of the mouse in the coordinate system.
        ///
        /// Returns at what specific location the mouse is at in the current coordinate system.
        /// @return Point The Point value of the location of the mouse.
        Point               getMouseLoc();

        /// @brief Gets the percentage of how far the x of the mouse is on the screen.
        ///
        /// Returns the percentage of how far right the x of the mouse is on the screen.
        /// 0.0 means the mouse is on the far left of the screen. 1.0 means its on the far right.
        /// 0.5 means it is in the middle.
        /// @return double The percentage of how far the x of the mouse is on the screen. Ranges from 0.0 to 1.0.
        double              getMouseXPercentage();

        /// @brief Gets the percentage of how far the y of the mouse is on the screen.
        ///
        /// Returns the percentage of how far verticle the y of the mouse is on the screen.
        /// 0.0 means the mouse is on the bottom of the screen. 1.0 means its on the top.
        /// 0.5 means it is in the middle.
        /// @return double The percentage of how far the y of the mouse is on the screen. Ranges from 0.0 to 1.0.
        double              getMouseYPercentage();

        /// @brief Sets the x mouse coordinate to the given value.
        ///
        /// This should not be used by the programmer. This is specifically used
        /// by the input class and window class when changing coordinate systems.
        /// @param mouseX The new x mouse location.
        void                setMouseX(double mouseX);

        /// @brief Sets the y mouse coordinate to the given value.
        ///
        /// This should not be used by the programmer. This is specifically used
        /// by the input class and window class when changing coordinate systems.
        /// @param mouseY The new y mouse location.
        void                setMouseY(double mouseY);

};
#endif
///@}

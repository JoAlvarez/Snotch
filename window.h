///@file
///@brief File for the Window class.
///
/// Everything that takes care of opening a window
/// and seting the coordinate system. Also keeps
/// track of the framerate.
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

#ifndef __WINDOW_H__
#define __WINDOW_H__

#define SUCCESS 0
#define FAIL 1
#define DEFAULT_MAX_FRAMES_PER_SEC 120.0

#define DEFAULT_HEIGHT 600
#define DEFAULT_WIDTH 800

#define DEFAULT_LEFT_COORD_4_3 0
#define DEFAULT_RIGHT_COORD_4_3 1024
#define DEFAULT_TOP_COORD_4_3 768
#define DEFAULT_BOT_COORD_4_3 0

#define DEFAULT_LEFT_COORD_WIDE 0
#define DEFAULT_RIGHT_COORD_WIDE 1280
#define DEFAULT_TOP_COORD_WIDE 800
#define DEFAULT_BOT_COORD_WIDE 0

#define DEFAULT_BITS_PER_PIXEL 32
#define DEFAULT_FOV 45
#define DEFAULT_DRAW_DISTANCE 500

#include <string>
#include "timer.h"

class Input;

///@brief Class that handles the window.
///
/// Creates and allows manipulation to the window and coordinate system.
class Window
{
    private:

        static Window*  instance;           //The singleton pointer for this class.
        static int      referenceCount;     //The number of things that current have access
                                            //the singleton pointer.

        Input*          input;              //Pointer to the singleton input object.

        bool            fullScreen;         //Whether or not the game is fullscreen.

        int             drawDistance;       //Used only in 3D, shows how far we keep
                                            //drawing objects in our scene.

        unsigned int	frameStart;         //The starting time of the current frame.
        int             framesPerSecond;    //The current frames per second.
        double          lastFrameTime;      //The amount of time that went by last frame.

        bool			vSync;              //Whether or not the framerate can exceed
                                            //the screen's refresh rate. Having it on
                                            //generally prevents "tearing" of the graphics.

        bool            cursorIsShown;      //Whether or not the default cursor is shown.

        int             width;              //The width of the resolution of the window.
        int             height;             //The height of the resolution of the window.

        double          coordLeft;          //Left coordinate of the game window.
        double          coordRight;         //Right coordinate of the game window.
        double          coordTop;           //Top coordinate of the game window.
        double          coordBot;           //Bottom coordinate of the game window.

        Timer           theTimer;           //Timer used for calculating the time since last frame.

        /// @brief Default contructor for the Window class.
        Window();

        /// @brief Opens and initializes the window object.
        /// @return int Returns FAIL if window failed to open. SUCCESS if window opened fine.
        int init();

        /// @brief Destroys and frees all the memory from this class.
        void destroy();

        /// @brief Handles the initialization settings that are read in from file.
        ///
        /// @param setting The setting that is being set. Example: fullscreen, vsync, height, etc.
        /// @param value The value of that setting. Example: true, false, 600, etc
        void handleSettings(std::string setting, int value);

        /// @brief Saves to the initialization file the new requested width and height.
        /// @param width The new width that will be used when the program is restarted.
        /// @param height The new height that will be used when the program is restarted.
        void setResolution(int width, int height);

    public:

        /// @brief Gets the instance of the Window object.
        ///
        /// Use this to obtain the instance of the Window object.
        /// @return Window* A pointer to the instance of the Window object.
        static Window* getInstance();

        /// @brief Releases the instance of the Window object obtained.
        ///
        /// Release the instance of the Window obtained from getInstance().
        /// This must be called on the pointer obtained from getInstance() to
        /// ensure that no memory leaks occur and that the Window object is
        /// destroyed when nobody has an instance of the object.
        void release();

        /// @brief Sets the coordinate system to the given values.
        ///
        /// @param left The left x coordinate of the system.
        /// @param right The right x coordinate of the system.
        /// @param bot The bottom y coordinate of the system.
        /// @param top The top y coordinate of the system.
        void setCoord(double left, double right, double bot, double top);

        /// @brief Zooms in the coordinate system by the given percentages.
        ///
        /// @param xPercentage What percentage of the current x coordinate size desired.
        /// A value of 1.0 means 100% the size of the current x coordinate size which
        /// does nothing. 0.5 means half the size (zooming in) of the current x coordinate size.
        /// 2.0 means twice the size (zooming out) of the current x coordinate size.
        /// @param yPercentage What percentage of the current y coordinate size desired.
        /// A value of 1.0 means 100% the size of the current y coordinate size which
        /// does nothing. 0.5 means half the size (zooming in) of the current y coordinate size.
        /// 2.0 means twice the size (zooming out) of the current y coordinate size.
        void zoomCoord(double xPercentage, double yPercetange);

        /// @brief Gets the size of the width of the window.
        ///
        /// @return int The width of the window.
        int getWidth();

        /// @brief Gets the size of the height of the window.
        ///
        /// @return int The height of the window.
        int getHeight();

        /// @brief Get the left coordinate of the current coordinate system.
        /// @return double The left x value of the current cooridnate system.
        double leftCoord();

        /// @brief Get the right coordinate of the current coordinate system.
        /// @return double The right x value of the current cooridnate system.
        double rightCoord();

        /// @brief Get the top coordinate of the current coordinate system.
        /// @return double The top y value of the current cooridnate system.
        double topCoord();

        /// @brief Get the bottom coordinate of the current coordinate system.
        /// @return double The bottom y value of the current cooridnate system.
        double bottomCoord();

        /// @brief Gets the number of seconds that have passed during the last frame.
        /// @return double The number of seconds passed during the last frame.
        /// Will usually be below the value of 1.0.
        double timeSinceLastFrame();

        /// @brief Get the framerate of the program at that time.
        /// @return unsigned int The current framerate of the program.
        unsigned int getFrameRate();

        /// @brief Used to indicate the start of the frame.
        ///
        /// This is used to calculate the framerate. Do to this we must
        /// specify the start and end each frame. This will indicate the start.
        void startFrame();

        /// @brief Used to indicate the end of the frame.
        ///
        /// This is used to calculate the framerate. Do to this we must
        /// specify the start and end each frame. This will indicate the end.
        void endFrame();

        /// @brief Used to either show or hide the default mouse cursor
        ///
        /// @param show Whether or not to have the default mouse cursor shown or not.
        void showCursor(bool show);

        /// @brief Whether or not the default mouse cursor is shown or not.
        /// @return bool If the default mouse cursor is shown or not.
        bool isCursorShown();

};

#endif
///@}

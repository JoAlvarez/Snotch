#include "window.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <ctime>
#include <fstream>
#include "image.h"
#include "input.h"

using namespace std;

//Give initial values to the static member variables.
Window* Window::instance = NULL;
int Window::referenceCount = 0;

//Returns the singleton pointer for this class.
Window* Window::getInstance()
{
    //If nobody has this pointer, make it and initialize it.
    if(instance == NULL)
    {
        instance = new Window;
        int status = instance->init();
        if(status == FAIL)
        {
            delete instance;
            return NULL;
        }
    }
    //Increment the number of times this pointer has been given out
    //and return it.
    ++referenceCount;
    return instance;
}

//Default constructor for the window class.
Window::Window()
{
    //Set all the default values for the window prior to initializing it.
    width  = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    fullScreen = true;
    vSync = true;
    cursorIsShown = true;
    framesPerSecond = DEFAULT_MAX_FRAMES_PER_SEC;
    drawDistance = DEFAULT_DRAW_DISTANCE;

    coordLeft = DEFAULT_LEFT_COORD_4_3;
    coordRight = DEFAULT_RIGHT_COORD_4_3;
    coordTop = DEFAULT_TOP_COORD_4_3;
    coordBot = DEFAULT_BOT_COORD_4_3;

    lastFrameTime = 1;
}

//Initialize the window object
int Window::init()
{
    //Initialize all SDL components.
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO |
                   SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0 )
    {
        //If there was a problem initializing SDL, terminate program.
        return FAIL;
    }

    //Make sure SDL cleans up everything during the exit.
    atexit(SDL_Quit);

    //Read the game.ini file to get all the game settings.
    ifstream infile;
    infile.open("./data/game.ini");

    //Prepare variables to extract the settings information.
    string setting = "";
    int settingValue = 0;

    //While the game.ini file has settings data in it, continue extracting them
    //and handle the given settings.
    while(!infile.eof() && infile.is_open())
    {
        //Get the setting to set.
        infile >> setting;

        //If the file has no more information, quit getting settings
        if(infile.eof())
            break;

        //Now get the value of the setting to set.
        infile >> settingValue;

        //Handle the given setting that was extracted so the game will be
        //created properly.
        handleSettings(setting, settingValue);
    }

    //Close the settings file.
	infile.close();

    //If the vsync setting is on, turn on Verticle Syncing
	if(vSync)
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

    //Enable Double Buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Bitflags variable that will hold the state of our window
	int iBitFlags = 0;

    //If the fullscreen variable is true, set the bitflags with the fullscreen
    //settings.
	if(fullScreen)
	{
        iBitFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN |
                    SDL_OPENGL    | SDL_NOFRAME;
	}
	//Otherwise set the bitflags for windowed settings.
    else
        iBitFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL;


    //Check to see if the given video settings will work, if not, set them
    //to default values that will work and continue.
    if(!SDL_VideoModeOK(width, height, DEFAULT_BITS_PER_PIXEL, iBitFlags))
	{
		width = DEFAULT_WIDTH;
        height = DEFAULT_HEIGHT;
		setResolution(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	}

    //Set the window and taskbar caption for the game.
	SDL_WM_SetCaption("2D Game", "2D Game" );

    //Set the video mode with the given settings.
    SDL_SetVideoMode(width, height, DEFAULT_BITS_PER_PIXEL, iBitFlags);

    //Get the input object for the game.
    input = Input::getInstance();

    //Set the coordinate system to the variables set earlier.

    double ratio = (double)width / (double)height;

    if(ratio != 4.0 / 3.0)
    {
        coordLeft = DEFAULT_LEFT_COORD_WIDE;
        coordRight = DEFAULT_RIGHT_COORD_WIDE;
        coordBot = DEFAULT_BOT_COORD_WIDE;
        coordTop = DEFAULT_TOP_COORD_WIDE;
    }

    setCoord(coordLeft, coordRight, coordBot, coordTop);

    //Start the timer for recording the framerate.
    theTimer.start();

    return SUCCESS;

}

//Allows something to get rid of the singleton pointer
//they have a hold of.
void Window::release()
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

//Free all dynamically allocated memory
void Window::destroy()
{
    if(instance)
    {
        delete instance;
        instance = NULL;
    }
}

//Save the new width and height for this game to file.
void Window::setResolution(int newWidth, int newHeight)
{
    ofstream outfile;
    outfile.open("./data/game.ini");
    outfile << "width= " << newWidth << endl << "height= " << newHeight << endl
			<< "fullscreen= " << fullScreen << endl << "vsync= " << vSync;
	outfile.close();
}

//Return the resolution width of the window.
int Window::getWidth()
{
    return width;
}


//Return the resolution height of the window.
int Window::getHeight()
{
    return height;
}

//Return the left X coordinate of the window.
double Window::leftCoord()
{
    return coordLeft;
}

//Return the right X coordinate of the window.
double Window::rightCoord()
{
    return coordRight;
}

//Return the top Y coordinate of the window.
double Window::topCoord()
{
    return coordTop;
}

//Return the bottom Y coordinate of the window.
double Window::bottomCoord()
{
    return coordBot;
}

//Record the starting time of the current frame.
void Window::startFrame()
{
    frameStart = theTimer.getTimePassed();
}

//Record the ending time of the current frame and see how
//much time went by during that frame.
void Window::endFrame()
{
    unsigned int frameEnd = theTimer.getTimePassed();

    lastFrameTime = (frameEnd - frameStart) / 1000.0;
}

//Show or hide the default moues cursor depending on
//what variable was passed in.
void Window::showCursor(bool toggle)
{
    cursorIsShown = toggle;
    if(cursorIsShown)
    {
        SDL_ShowCursor(SDL_ENABLE);
    }
    else
    {
        SDL_ShowCursor(SDL_DISABLE);
    }
}

//Return whether or not the default mouse cursor is shown.
bool Window::isCursorShown()
{
    return cursorIsShown;
}

//Return the time since last frame.
double Window::timeSinceLastFrame()
{
    return lastFrameTime;
}

//Return the current framerate of the game.
unsigned int Window::getFrameRate()
{
    return (unsigned int)(1.0 / lastFrameTime);
}

//Set the window setting with the current value passed in.
void Window::handleSettings(string setting, int settingValue)
{
    if(setting == "width=")
    {
        width = settingValue;
    }
    else if(setting == "height=")
    {
        height = settingValue;
    }
    else if(setting == "fullscreen=")
    {
        fullScreen = settingValue;
    }
    else if(setting == "vsync=")
    {
        vSync = settingValue;
    }
    else if(setting == "drawdistance=")
    {
        drawDistance = settingValue;
    }
}

//Set the coordinate system shown on the window.
void Window::setCoord(double left, double right, double bottom, double top)
{
    //When moving the coordinate system, we must ensure that the mouse is in the right
    //location of the new coordinate system since the mouse just not set its location unless
    //the mouse is moved.

    //Record what percentage the mouse is on the X coordinate of the window.
    double mouseXpercentage = (coordRight - input->getMouseXloc()) / (coordRight - coordLeft);
    //Use that percentage to set the mouses new location.
    input->setMouseX(right - (right - left) * mouseXpercentage);

    //Record what percentage the mouse is on the Y coordinate of the window.
    double mouseYpercentage =  (coordTop - input->getMouseYloc()) / (coordTop - coordBot);
    //Use that percentage to set the mouses new location.
    input->setMouseY(top - (top - bottom) * mouseYpercentage);

    //Set the coordinate system variables.
    coordLeft = left;
    coordBot = bottom;
    coordRight = right;
    coordTop = top;

    //Actually set the new coordinate system in OpenGL.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

//Zoom the coorinate system in or out in each the x and or y direction.
void Window::zoomCoord(double xPercentage, double yPercentage)
{
    //Record the distance in the coordinate system in the X and Y direction.
    double xDistance = coordRight - coordLeft;
    double yDistance = coordTop - coordBot;

    //Record the middle X and Y of the current coorinate system.
    double xMiddle = coordLeft + xDistance / 2.0;
    double yMiddle = coordBot  + yDistance / 2.0;

    double left, right, bot, top;

    //Calculate the new values of the coordinate system.
    left = xMiddle - xDistance / 2.0 * (1 + xPercentage);
    right = xMiddle + xDistance / 2.0 * (1 + xPercentage);

    bot = yMiddle - yDistance / 2.0 * (1 + yPercentage);
    top = yMiddle + yDistance / 2.0 * (1 + yPercentage);

    //Set the coordinate system with the new values.
    setCoord(left, right, bot, top);
}


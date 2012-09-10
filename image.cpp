#include "image.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include "window.h"

using namespace std;



Image::Image()
{
    alias = "";
}

void Image::setAlias(string name)
{
    alias = name;
}

void Image::setTexture(GLuint image)
{
    glTexture = image;
}

string Image::getAlias()
{
    return alias;
}

GLuint* Image::getTexture()
{
    return &glTexture;
}

int power_of_two(int input)
{
    int value = 1;

    while ( value < input )
    {
        value <<= 1;
    }
    return value;
}


void SDL_GL_LoadTexture(SDL_Surface* surface, Image* texture)
{
    int w, h;
    SDL_Surface *image;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;

    w = power_of_two(surface->w);
    h = power_of_two(surface->h);

    image = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            w, h,
            32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN //OpenGL RGBA masks
            0x000000FF,
            0x0000FF00,
            0x00FF0000,
            0xFF000000
#else
            0xFF000000,
            0x00FF0000,
            0x0000FF00,
            0x000000FF
#endif
               );

    if ( image == NULL )
    {
        return;
    }

    //Save the alpha blending attributes that were on the SDL surface
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA )
    {
        SDL_SetAlpha(surface, 0, 0);
    }

    //Copy the surface data to be placed in the opengl texture
    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;
    SDL_BlitSurface(surface, &area, image, &area);

    //Restore the alpha blending attributes into the new opengl texture
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }

    //image = SDL_DisplayFormatAlpha(image);
    //Create an OpenGL texture to hold the image
    GLuint tempTexture;
    glGenTextures(1, (texture->getTexture()));
    glBindTexture(GL_TEXTURE_2D, *(texture->getTexture()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGBA,
             w, h,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             surface->pixels);
    SDL_FreeSurface(image); //Free the data on the SDL surface
   // texture->setTexture(tempTexture);

}

void LoadImage(Image* image, string filename)
{

    SDL_Surface* surface; //Create an SDL to load the image on for converting.

    surface = IMG_Load(filename.c_str()); //Load the image onto the surface.

    //SDL_LockSurface( surface );

    //Convert the SDL surface that has the image into an OpenGL texture.
    SDL_GL_LoadTexture(surface, image);
    //SDL_UnlockSurface( surface );
	SDL_FreeSurface( surface ); //Free the memory being used with the surface.

	// *NOTE* - SDL loads images upsidedown, remember to draw them correctly
	//          when you draw them or else they will come out upside down.

}

void RenderImage(Image image, double left_x, double right_x, double lower_y,
                 double upper_y)
{

    //Taking the note from the LoadImage function, we understand that SDL
    //surface load textures upside down. We need to adjust this by creating new
    //variables that reverse the y points so the image is drawn correctly.
    double dX1 = left_x;
    double dX2 = right_x;
    double dY1 = upper_y;
    double dY2 = lower_y;

	//Enable transparency and ready opengl for image rendering prior to actually
	//rendering.
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(image.getTexture()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    //Map the parts of the image to the given coordinates and render it.
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(dX1, dY1);	// Bottom left
        glTexCoord2f(1.0, 0.0); glVertex2f(dX2, dY1);	// Bottom right
        glTexCoord2f(1.0, 1.0); glVertex2f(dX2, dY2);	// Top right
        glTexCoord2f(0.0, 1.0); glVertex2f(dX1, dY2);	// Top left
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void RenderImage(Image image, double angle, double left_x, double right_x, double lower_y,
                 double upper_y)
{

    //Taking the note from the LoadImage function, we understand that SDL
    //surface load textures upside down. We need to adjust this by creating new
    //variables that reverse the y points so the image is drawn correctly.
    double dX1 = - (right_x - left_x) / 2.0;
    double dX2 = (right_x - left_x) / 2.0;
    double dY1 = (upper_y - lower_y) / 2.0;
    double dY2 = - (upper_y - lower_y) / 2.0;
	//Enable transparency and ready opengl for image rendering prior to actually
	//rendering.

	glLoadIdentity();
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glLoadIdentity();
    glTranslated((left_x + right_x) / 2.0, (upper_y + lower_y) / 2.0, 0);
    glRotated(angle, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, *(image.getTexture()));

    //Map the parts of the image to the given coordinates and render it.
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(dX1, dY1);	// Bottom left
        glTexCoord2f(1.0f, 0.0f); glVertex2f(dX2, dY1);	// Bottom right
        glTexCoord2f(1.0f, 1.0f); glVertex2f(dX2, dY2);	// Top right
        glTexCoord2f(0.0f, 1.0f); glVertex2f(dX1, dY2);	// Top left
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
}

////////////////////////////////////////////////////////////////////////////////
// Function:            RenderImage
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 13, 2007
//
// Function:            Takes a GLuint image mapping and opengl coordinates and
//                      image coordinates and maps the image coordinates part of
//                      the image and places it on the opengl coordinates part
//                      of the screen.
//
// Inputs:              GLuint& image    - The variable that will hold the
//                                             mapped out image data to be used
//                                             for output.
//                      double left_x          - The left x of the image to be
//                                             drawn in opengl.
//                      double right_x          - The right x of the image to be
//                                             drawn in opengl.
//                      double lower_y          - The lower y of the image to be
//                                             drawn in opengl.
//                      double upper_y          - The upper y of the image to be
//                                             drawn in opengl.
//                      double left_xTexCoord_ - The left x part of the image that
//                                             we start getting info from.
//                      double right_xTexCoord_ - The right x part of the image
//                                             that we stop getting info from.
//                      double lower_yTexCoord_ - The lower y part of the image
//                                             that we start getting info from.
//                      double upper_yTexCoord_ - The upper y part of the image
//                                             that we stop getting info from.
//
// Outputs:             Draws the desired part of the image to the screen that
//                      spans the given coordinates.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void RenderImage(Image image, double left_x, double right_x, double lower_y,
               double upper_y, double left_xTexCoord, double right_xTexCoord,
               double lower_yTexCoord, double upper_yTexCoord)
{
	//Taking the note from the LoadImage function, we understand that SDL
    //surface load textures upside down. We need to adjust this by creating new
    //variables that reverse the y points so the image is drawn correctly.
    double dX1 = left_x;
    double dX2 = right_x;
    double dY1 = upper_y;
    double dY2 = lower_y;




	//Enable transparency and ready opengl for image rendering prior to actually
	//rendering.
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *(image.getTexture()));

    if(left_xTexCoord < 0 || right_xTexCoord > 1 || upper_yTexCoord > 1 || lower_yTexCoord < 0)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    glBegin(GL_QUADS);
		//Bottom left
        glTexCoord2f(left_xTexCoord, lower_yTexCoord); glVertex2f(dX1, dY1);
        //Bottom right
        glTexCoord2f(right_xTexCoord, lower_yTexCoord); glVertex2f(dX2, dY1);
        //Top Right
        glTexCoord2f(right_xTexCoord, upper_yTexCoord); glVertex2f(dX2, dY2);
        //Top left
        glTexCoord2f(left_xTexCoord, upper_yTexCoord); glVertex2f(dX1, dY2);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            RenderImage
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 13, 2007
//
// Function:            Takes a GLuint image mapping and opengl coordinates and
//                      image coordinates and maps the image coordinates part of
//                      the image and places it on the opengl coordinates part
//                      of the screen rotated by angle degrees.
//
// Inputs:              GLuint& image    - The variable that will hold the
//                                             mapped out image data to be used
//                                             for output.
//                      double angle           - The angle to rotate the image in
//                                             degrees.
//                      double left_x          - The left x of the image to be
//                                             drawn in opengl.
//                      double right_x          - The right x of the image to be
//                                             drawn in opengl.
//                      double lower_y          - The lower y of the image to be
//                                             drawn in opengl.
//                      double upper_y          - The upper y of the image to be
//                                             drawn in opengl.
//                      double left_xTexCoord_ - The left x part of the image that
//                                             we start getting info from.
//                      double right_xTexCoord_ - The right x part of the image
//                                             that we stop getting info from.
//                      double lower_yTexCoord_ - The lower y part of the image
//                                             that we start getting info from.
//                      double upper_yTexCoord_ - The upper y part of the image
//                                             that we stop getting info from.
//
// Outputs:             Draws the desired part of the image to the screen that
//                      spans the given coordinates.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void RenderImage(Image image, double angle, double left_x, double right_x, double lower_y,
               double upper_y, double left_xTexCoord, double right_xTexCoord,
               double lower_yTexCoord, double upper_yTexCoord)
{
	//Taking the note from the LoadImage function, we understand that SDL
    //surface load textures upside down. We need to adjust this by creating new
    //variables that reverse the y points so the image is drawn correctly.
    double dX1 = - (right_x - left_x) / 2.0;
    double dX2 = (right_x - left_x) / 2.0;
    double dY1 = (upper_y - lower_y) / 2.0;
    double dY2 = - (upper_y - lower_y) / 2.0;



	//Enable transparency and ready opengl for image rendering prior to actually
	//rendering.
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, *(image.getTexture()));

    glLoadIdentity();
    glTranslated((left_x + right_x) / 2.0, (upper_y + lower_y) / 2.0, 0);
    glRotated(angle, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, *(image.getTexture()));

    if(left_xTexCoord < 0 || right_xTexCoord > 1 || upper_yTexCoord > 1 || lower_yTexCoord < 0)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    glBegin(GL_QUADS);
		//Bottom left
        glTexCoord2f(left_xTexCoord, lower_yTexCoord); glVertex2f(dX1, dY1);
        //Bottom right
        glTexCoord2f(right_xTexCoord, lower_yTexCoord); glVertex2f(dX2, dY1);
        //Top Right
        glTexCoord2f(right_xTexCoord, upper_yTexCoord); glVertex2f(dX2, dY2);
        //Top left
        glTexCoord2f(left_xTexCoord, upper_yTexCoord); glVertex2f(dX1, dY2);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();
}


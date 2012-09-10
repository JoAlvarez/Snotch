#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <string>

using namespace std;

class Image
{
    public:
        Image();
        void setAlias(string alias);
        void setTexture(GLuint texture);

        string getAlias();
        GLuint* getTexture();

    private:
        string alias;
        GLuint glTexture;
};

void LoadImage(Image* image, string filename);

void RenderImage(Image image, double lx, double rx, double ly, double uy);

void RenderImage(Image image, double angle, double lx, double rx, double ly, double uy);

void RenderImage(Image image, double lx, double rx, double ly, double uy,
			   double _dLX_TexCoord, double _dRX_TexCoord, double _dLY_TexCoord,
			   double _dUY_TexCoord);

void RenderImage(Image image, double angle, double lx, double rx, double ly, double uy,
			   double _dLX_TexCoord, double _dRX_TexCoord, double _dLY_TexCoord,
			   double _dUY_TexCoord);

#endif

#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "game.h"

using namespace std;

int main(int argc, char** argv)
{

    Game theGame;

    theGame.init();

    theGame.play();

  return 0;
}


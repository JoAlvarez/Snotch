#ifndef __THOUGHT_BUBBLE_H__
#define __THOUGHT_BUBBLE_H__

#include "point.h"
#include "resourcemgr.h"
#include "filenames.h"
#include <SDL/SDL_opengl.h>
#include <string>
#include <sstream>

class ThoughtBubble
{
    private:
        ResourceMgr*    resourceMgr;
        vector<string>  textRows;
        double          totalWidth;
        double          totalHeight;

        void drawBottomBorder( double leftX, double rightX, double topY , bool leftSide);
        void drawTopBorder( double leftX, double rightX, double bottomY );
        void drawLeftBorder( double rightX, double topY, double bottomY );
        void drawRightBorder( double leftX, double topY, double bottomY );
        void drawLrCorner( Point bottomRight );
        void drawText( Point ul );

    public:
        void init();
        void setText( string text );
        void draw( Point indicatorTip );
};

#endif

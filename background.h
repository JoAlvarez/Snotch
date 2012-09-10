#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "resourcemgr.h"
#include "window.h"
#include "point.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Background
{
    private:
        struct BgLayer
        {
            string          bgAlias;
            unsigned int    layer;
            double          xSpeed;
            double          ySpeed;
            double          width;
            double          height;
            double          xNatSpeed;
            double          yNatSpeed;
            double          leftX;
            double          upperY;
            bool            xRepeat;
            //None  Up UpDown
            string          yRepeat;
        };
        ResourceMgr* resourceMgr;
        Window* window;
        vector< BgLayer > bgLayers;
        void        drawLayer( unsigned int layer );
        void        drawBg( unsigned int index );
        void        skipLine( ifstream & input );
        void        handleInput( ifstream& inputFile );
        int         stringToInt( string toConvert );
        double      stringToDouble( string toConvert );
        bool        stringToBool( string toConvert );
        void        newLayer();
        void        addLayer( string bgAlias, double xSpeed, unsigned int layer, double width,
                              double height, double leftX, double upperY, bool xRepeat,
                              double xNatSpeed, double yNatSpeed, string yRepeat, double ySpeed );

    public:
        Background();
        void update();
        void clear();
        void draw();
        void load( string bgFile );

        ~Background();

};

#endif

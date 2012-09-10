#include "thoughtbubble.h"
#define TB_INDICATOR_TOTAL_WIDTH        64.0
#define TB_INDICATOR_TOTAL_HEIGHT       32.0
#define TB_INDICATOR_WIDTH              35.0
#define TB_INDICATOR_HEIGHT             22.0
#define TB_CORNER_WIDTH                 6.0
#define TB_CORNER_HEIGHT                6.0
#define TB_CORNER_TOTAL_WIDTH           8.0
#define TB_CORNER_TOTAL_HEIGHT          8.0

#define TB_FONT_HEIGHT                  12.0
#define TB_FONT_WIDTH                   11.0
#define TB_FONT_PADDING                 4.0

#define TB_WIDTH                        200.0
#define TB_ROW_WIDTH                    TB_WIDTH - ( TB_FONT_PADDING * 2.0 )


void ThoughtBubble::init()
{
    resourceMgr = ResourceMgr::getInstance();
    resourceMgr->loadImage( FILE_THOUGHT_BUBBLE_INDICATOR, "tbIndicator" );
    resourceMgr->loadImage( FILE_THOUGHT_BUBBLE_CORNER, "tbCorner" );
    resourceMgr->loadImage( FILE_THOUGHT_BUBBLE_BORDER, "tbBorder" );
    totalWidth   = TB_WIDTH;
    totalHeight  = TB_FONT_HEIGHT;
}

void ThoughtBubble::draw( Point indicatorTip )
{
    double indicatorUlX = indicatorTip.getX() - ( TB_INDICATOR_WIDTH / 2.0 );
    double indicatorUlY = indicatorTip.getY() + TB_INDICATOR_HEIGHT;

    double left     = indicatorUlX - ( ( totalWidth - TB_INDICATOR_WIDTH ) / 2.0 );
    double right    = indicatorUlX + TB_INDICATOR_WIDTH +
                      ( ( totalWidth - TB_INDICATOR_WIDTH ) / 2.0 );
    double top      = indicatorUlY + totalHeight;
    double bottom   = indicatorUlY;

    //Draw background
    glEnable ( GL_BLEND );
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f( 0.1529, 0.1529, 0.1529, 0.72 );
    glBegin( GL_QUADS );
        glVertex2f( left    , top );
        glVertex2f( right   , top  );
        glVertex2f( right   , bottom - 1  );
        glVertex2f( left    , bottom - 1  );
    glEnd();
    glColor4f( 1.0, 1.0, 1.0, 1.0 );

    glDisable( GL_BLEND );
    glEnd();
    //Draw indicator
    resourceMgr->drawImage( "tbIndicator",
                            indicatorUlX,
                            indicatorUlX + TB_INDICATOR_TOTAL_WIDTH,
                            indicatorUlY - TB_INDICATOR_TOTAL_HEIGHT,
                            indicatorUlY );

    //glColor3f(0,0,0);
    //Draw bottom left border
    drawBottomBorder( left, indicatorUlX, bottom , true);

    //Draw bottom right border
    drawBottomBorder( indicatorUlX + TB_INDICATOR_WIDTH, right, bottom , false);

    //Draw top border
    drawTopBorder( left, right, top );

    //Draw left border
    drawLeftBorder( left, top, bottom );

    //Draw right border
    drawRightBorder( right, top, bottom );

    glColor3f(1,1,1);

    drawText( Point( left, top ) );
}

void ThoughtBubble::drawBottomBorder( double leftX, double rightX, double bottomY , bool left )
{
    glBegin( GL_LINES );
        //Draw black lines
        glColor3f(0.0,0.0,0.0);

        glVertex2f( leftX  , bottomY + 2 );
        glVertex2f( rightX , bottomY + 2 );
        glVertex2f( leftX  , bottomY + 1 );
        glVertex2f( rightX , bottomY + 1 );


        //Draw white line
        glColor3f(1.0,1.0,1.0);
        glVertex2f( leftX  , bottomY );
        glVertex2f( rightX , bottomY );
    glEnd();

    /*
    if(left)
    {
        resourceMgr->drawImage("tbCorner", leftX + 32, leftX, bottomY, bottomY + 32);
        resourceMgr->drawImage("tbBorder", leftX + 31, rightX, bottomY, bottomY + 3);
    }
    else
    {
        resourceMgr->drawImage("tbCorner", rightX - 32, rightX, bottomY, bottomY + 32);
        resourceMgr->drawImage("tbBorder", leftX, rightX - 31, bottomY, bottomY + 3);
    }*/
}

void ThoughtBubble::drawTopBorder( double leftX, double rightX, double topY )
{
    glBegin( GL_LINES );
        //Draw black lines
        glColor3f(0.0,0.0,0.0);
        glVertex2f( leftX   , topY - 2 );
        glVertex2f( rightX  , topY - 2 );
        glVertex2f( leftX   , topY - 1 );
        glVertex2f( rightX  , topY - 1 );


        //Draw white line
        glColor3f(1.0,1.0,1.0);
        glVertex2f( leftX   , topY );
        glVertex2f( rightX  , topY );
    glEnd();

    //resourceMgr->drawImage("tbBorder", leftX + 31, rightX - 31, topY - 3, topY);
}

void ThoughtBubble::drawLeftBorder( double leftX, double topY, double bottomY )
{
    glBegin( GL_LINES );
        //Draw black lines
        glColor3f(0.0,0.0,0.0);
        glVertex2f( leftX + 2  , topY - 1 );
        glVertex2f( leftX + 2  , bottomY + 1 );
        glVertex2f( leftX + 1  , topY - 2 );
        glVertex2f( leftX + 1  , bottomY + 2 );


        //Draw white line
        glColor3f(1.0,1.0,1.0);
        glVertex2f( leftX, topY );
        glVertex2f( leftX, bottomY );
    glEnd();
    //resourceMgr->drawImage("tbCorner", leftX + 32, leftX, topY, topY - 32);
    //resourceMgr->drawImage("tbBorder", leftX, leftX + 3, bottomY + 31, topY - 31);


}

void ThoughtBubble::drawRightBorder( double rightX, double topY, double bottomY )
{
    glBegin( GL_LINES );
        //Draw black lines
        glColor3f(0.0,0.0,0.0);
        glVertex2f( rightX - 2  , topY - 2 );
        glVertex2f( rightX - 2  , bottomY + 2 );
        glVertex2f( rightX - 1  , topY - 1);
        glVertex2f( rightX - 1  , bottomY + 1 );


        //Draw white line
        glColor3f(1.0,1.0,1.0);
        glVertex2f( rightX, topY );
        glVertex2f( rightX, bottomY );
    glEnd();

    //resourceMgr->drawImage("tbCorner", rightX - 32, rightX, topY, topY - 32);
    //resourceMgr->drawImage("tbBorder", rightX - 3, rightX, bottomY + 31, topY - 31);

}

void ThoughtBubble::setText( string text )
{
    vector<string>  words;
    stringstream    textBlock;
    string          row;

    textBlock << text;

    textRows.clear();

    //Split the string into seperate words.
    while( !textBlock.eof() )
    {
        string tempString;
        textBlock >> tempString;

        tempString += " ";
        words.push_back( tempString );
    }

    ////Combine the words into rows
    for( unsigned int i = 0; i < words.size(); ++i )
    {
        double curRowWidth = ( row.size() + words[i].size() ) * TB_FONT_WIDTH;

        //If adding this word makes the row too long
        //skip adding the word to the row and add the
        //string to the rows vector.
        if( curRowWidth > TB_ROW_WIDTH )
        {
            textRows.push_back( row );
            row.clear();
        }
        row += words[i];
        //If we've gone though all the  words but haven't
        //exceeded a row width add the current row to the
        //rows vector.
        if( i == ( words.size() - 1 ) )
        {
            textRows.push_back( row );
        }
    }
    //Account for row height
    totalHeight = textRows.size() * TB_FONT_HEIGHT;
    totalHeight += ( textRows.size() + 1 ) * TB_FONT_PADDING;
}

void ThoughtBubble::drawText( Point ul )
{
    double curX = ul.getX() + TB_FONT_PADDING;
    double curY = ul.getY() - TB_FONT_HEIGHT - TB_FONT_PADDING;

    for( unsigned int i = 0; i < textRows.size(); ++i )
    {
        resourceMgr->drawText( "MONACO", textRows[i], curX, curY );
        curY -= TB_FONT_HEIGHT + TB_FONT_PADDING;
    }
}

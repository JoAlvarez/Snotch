#include "resourcemgr.h"

ResourceMgr* ResourceMgr::instance = NULL;
int ResourceMgr::referenceCount = 0;


ResourceMgr::ResourceMgr()
{

}

void ResourceMgr::init()
{
    audio.init();
    window = Window::getInstance();
}

ResourceMgr* ResourceMgr::getInstance()
{
    if(instance == NULL)
    {
        instance = new ResourceMgr;
        instance->init();
    }
    ++referenceCount;
    return instance;
}

void ResourceMgr::release()
{
    if( --referenceCount < 1 )
    {
        destroy();
    }
    if(referenceCount < 0)
        referenceCount = 0;
}

void ResourceMgr::destroy()
{
    if(instance)
    {
        deleteAllImages();
        deleteAllMusic();
        deleteAllSounds();
        audio.close();

        delete instance;
        instance = NULL;
    }
}

void ResourceMgr::loadImage(string filename, string alias)
{
    //Check to see if that alias has already been used.
    for(int i = 0; i < images.size(); ++i)
    {
        if(images[i]->getAlias() == alias)
            return;
    }

    //Add a new image to the vector.
    images.push_back(new Image);

    //Set the alias of the Image and load it.
    images[images.size() - 1]->setAlias(alias);
    LoadImage(images[images.size() - 1], filename);
}

void ResourceMgr::deleteImage(string alias)
{
    for(int i = 0; i < images.size(); ++i)
    {
        if(images[i]->getAlias() == alias)
        {
            glDeleteTextures(1, (images[i]->getTexture()) );
            delete images[i];
            images.erase(images.begin() + i);
            return;
        }
    }
}

void ResourceMgr::deleteFont(string alias)
{
    for(int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->clean();
            delete fonts[i];
            images.erase(images.begin() + i);
            return;
        }
    }
}

Image ResourceMgr::getImage(string alias)
{
    for(int i = 0; i < images.size(); ++i)
    {
        if(images[i]->getAlias() == alias)
        {
            return *images[i];
        }

    }
    Image temp;
    return temp;
}

void ResourceMgr::loadSound(string filename, string alias)
{
    audio.loadSound(filename, alias);
}

void ResourceMgr::loadMusic(string filename, string alias)
{
    audio.loadMusic(filename, alias);
}

void ResourceMgr::loadFont(string filename, string alias, int size)
{
    for(int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            return;
        }
    }
    fonts.push_back(new Font(alias));
    fonts[fonts.size() - 1]->init(filename, size);
}

void ResourceMgr::playSound(string alias)
{
    audio.playSound(alias);
}

void ResourceMgr::playSound3D(string alias, double xEar, double yEar, double xSrc, double ySrc)
{
    audio.playSound3D(alias, xEar, yEar, xSrc, ySrc);
}

void ResourceMgr::playMusic(string alias)
{
    audio.playMusic(alias);
}

void ResourceMgr::playMusicRepeat(string alias, int numLoops)
{
    audio.playMusicRepeat(alias, numLoops);
}

void ResourceMgr::playMusicFade(string alias, int numLoops, int miliSecs)
{
    audio.playMusicFade(alias, numLoops, miliSecs);
}

void ResourceMgr::playMusicFrom(string alias, int numLoops, double position)
{
    audio.playMusicFrom(alias, position, numLoops);
}

void ResourceMgr::playMusicFadeFrom(string alias, int numLoops, double position, int miliSecs)
{
    audio.playMusicFadeFrom(alias, position, numLoops, miliSecs);
}

void ResourceMgr::pauseMusic()
{
    audio.pauseMusic();
}

void ResourceMgr::resumeMusic()
{
    audio.resumeMusic();
}

void ResourceMgr::stopMusic()
{
    audio.stopMusic();
}

void ResourceMgr::fadeOutMusic(int miliSecs)
{
    audio.fadeOutMusic(miliSecs);
}

void ResourceMgr::setMaxSoundDistance(double distance)
{
    audio.setMaxSoundDistance(distance);
}

void ResourceMgr::setMaxFullHearDistance(double distance)
{
    audio.setMaxFullHearDistance(distance);
}

bool ResourceMgr::imageIsOffScreen(double leftX, double rightX, double lowerY,  double upperY)
{
    if(leftX < rightX)
    {
        if(leftX > window->rightCoord())
            return true;
        if(rightX < window->leftCoord())
            return true;
    }
    else
    {
        if(rightX > window->rightCoord())
            return true;
        if(leftX < window->leftCoord())
            return true;
    }

    if(lowerY < upperY)
    {
        if(lowerY > window->topCoord())
            return true;
        if(upperY < window->bottomCoord())
            return true;
    }
    else
    {
        if(upperY > window->topCoord())
            return true;
        if(lowerY < window->bottomCoord())
            return true;
    }
    return false;
}

void ResourceMgr::drawImage(string alias,  double leftX,
                            double rightX, double lowerY,
                            double upperY)
{
    if(imageIsOffScreen(leftX, rightX, lowerY, upperY))
        return;
    RenderImage(getImage(alias), leftX, rightX, lowerY, upperY);
}

void ResourceMgr::drawImage(string alias,  double angle,
                            double leftX,  double rightX,
                            double lowerY, double upperY)
{
    if(imageIsOffScreen(leftX, rightX, lowerY, upperY))
        return;
    RenderImage(getImage(alias), angle, leftX, rightX, lowerY, upperY);
}

void ResourceMgr::drawImage(string alias,  double leftX,
                            double rightX, double lowerY,
                            double upperY, double leftX_TexCoord,
                            double rightX_TexCoord, double lowerY_TexCoord,
                            double upperY_TexCoord)
{
    if(imageIsOffScreen(leftX, rightX, lowerY, upperY))
        return;
    RenderImage(getImage(alias), leftX, rightX, lowerY, upperY,
                leftX_TexCoord, rightX_TexCoord, lowerY_TexCoord,
                upperY_TexCoord);
}

void ResourceMgr::drawImage(string alias,  double angle,
                            double leftX,  double rightX,
                            double lowerY, double upperY,
                            double leftX_TexCoord,
                            double rightX_TexCoord,
                            double lowerY_TexCoord,
                            double upperY_TexCoord)
{
    if(imageIsOffScreen(leftX, rightX, lowerY, upperY))
        return;
    RenderImage(getImage(alias), angle, leftX, rightX, lowerY, upperY,
                leftX_TexCoord, rightX_TexCoord, lowerY_TexCoord,
                upperY_TexCoord);
}

void ResourceMgr::drawImageOverlay(string alias, double percentLeftX,
                                   double percentRightX, double percentLowerY,
                                   double percentUpperY)
{
    double leftX, rightX, lowerY, upperY;
    leftX = window->leftCoord();
    rightX = window->rightCoord();
    lowerY = window->bottomCoord();
    upperY = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    RenderImage(getImage(alias),
                window->getWidth()  * percentLeftX,
                window->getWidth()  * percentRightX,
                window->getHeight() * percentLowerY,
                window->getHeight() * percentUpperY);

    window->setCoord(leftX, rightX, lowerY, upperY);
}

void ResourceMgr::drawText(string alias, string text, double x, double y)
{
    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(text, x, y);
        }
    }
}

void ResourceMgr::drawText(string alias, int numText, double x, double y)
{
    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(numText, x, y);
        }
    }
}

void ResourceMgr::drawText(string alias, unsigned int numText, double x, double y)
{
    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(numText, x, y);
        }
    }
}

void ResourceMgr::drawText(string alias, double numText, double x, double y)
{
    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(numText, x, y);
        }
    }
}

void ResourceMgr::drawTextOverlay(string alias, string text, double percentX, double percentY)
{
    double leftX, rightX, lowerY, upperY;
    leftX = window->leftCoord();
    rightX = window->rightCoord();
    lowerY = window->bottomCoord();
    upperY = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(text, window->getWidth()  * percentX,
                                        window->getHeight() * percentY);
            break;
        }
    }

    window->setCoord(leftX, rightX, lowerY, upperY);
}

void ResourceMgr::drawTextOverlay(string alias, int numText, double percentX, double percentY)
{
    double leftX, rightX, lowerY, upperY;
    leftX = window->leftCoord();
    rightX = window->rightCoord();
    lowerY = window->bottomCoord();
    upperY = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(numText, window->getWidth()  * percentX,
                                        window->getHeight() * percentY);
            break;
        }
    }

    window->setCoord(leftX, rightX, lowerY, upperY);
}

void ResourceMgr::drawTextOverlay(string alias, unsigned int numText, double percentX, double percentY)
{
    double leftX, rightX, lowerY, upperY;
    leftX = window->leftCoord();
    rightX = window->rightCoord();
    lowerY = window->bottomCoord();
    upperY = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(numText, window->getWidth()  * percentX,
                                        window->getHeight() * percentY);
            break;
        }
    }

    window->setCoord(leftX, rightX, lowerY, upperY);
}

void ResourceMgr::drawTextOverlay(string alias, double numText, double percentX, double percentY)
{
    double leftX, rightX, lowerY, upperY;
    leftX = window->leftCoord();
    rightX = window->rightCoord();
    lowerY = window->bottomCoord();
    upperY = window->topCoord();

    window->setCoord(0, window->getWidth(), 0, window->getHeight());

    for(unsigned int i = 0; i < fonts.size(); ++i)
    {
        if(fonts[i]->getAlias() == alias)
        {
            fonts[i]->drawText(numText, window->getWidth()  * percentX,
                                        window->getHeight() * percentY);
            break;
        }
    }

    window->setCoord(leftX, rightX, lowerY, upperY);
}

void ResourceMgr::deleteAllImages()
{
    for(unsigned int i = 0; i < images.size(); i++)
    {
        delete images[i];
    }
    images.erase(images.begin(), images.end());
}

void ResourceMgr::deleteAllMusic()
{
    stopMusic();
    audio.deleteAllMusic();
}

void ResourceMgr::deleteAllSounds()
{
    audio.deleteAllSounds();
}

void ResourceMgr::deleteSound(string alias)
{
    audio.deleteSound(alias);
}

void ResourceMgr::deleteMusic(string alias)
{
    audio.deleteMusic(alias);
}

void ResourceMgr::deleteAllFonts()
{
    for(int i = 0; i < fonts.size(); ++i)
    {
        fonts[i]->clean();
        delete fonts[i];
    }

    fonts.erase(fonts.begin(), fonts.end());
}

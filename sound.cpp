#include "sound.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <string>


using namespace std;

Sound::Sound()
{
	m_pChunk = NULL;
	m_sName = "";
	m_iVolume = MAX_VOLUME;
}

Sound::Sound(string sFilename_, string sAlias_)
{
	m_iVolume = MAX_VOLUME;
	m_pChunk = Mix_LoadWAV(sFilename_.c_str());
	m_sName = sAlias_;
}

Sound::~Sound()
{
	Mix_FreeChunk(m_pChunk);
}

void Sound::loadSound(string sFilename_, string sAlias_)
{
	m_pChunk = Mix_LoadWAV(sFilename_.c_str());
	m_sName = sAlias_;
}

void Sound::playSound(int iChannel_)
{
	Mix_PlayChannel(iChannel_, m_pChunk, 0);
}

void Sound::playSoundRepeat(int iChannel_, int iNumLoops_)
{
	Mix_PlayChannel(iChannel_, m_pChunk, iNumLoops_);
}

void Sound::playSoundFade(int iChannel_, int iNumLoops_, int iMiliSecs_)
{
	Mix_FadeInChannel(iChannel_, m_pChunk, iNumLoops_, iMiliSecs_);
}

void Sound::playSoundTimed(int iChannel_, int iNumLoops_, int iTicks_)
{
	Mix_PlayChannelTimed(iChannel_, m_pChunk, iNumLoops_, iTicks_);
}

void Sound::playSoundFadeTimed(int iChannel_, int iNumLoops_, int iMiliSecs_,
							   int iTicks_)
{
	Mix_FadeInChannelTimed(iChannel_, m_pChunk, iNumLoops_, iMiliSecs_,
                           iTicks_);
}

void Sound::setVolume(int iVolume_)
{
	m_iVolume = iVolume_;
}

string Sound::getName()
{
	return m_sName;
}

int Sound::getVolume()
{
	return m_iVolume;
}

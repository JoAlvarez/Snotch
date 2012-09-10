#include "music.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <string>

using namespace std;

Music::Music()
{
	m_pMusic = NULL;
	m_sName = "";
}

Music::Music(string sFilename_, string sAlias_)
{
	m_pMusic = Mix_LoadMUS(sFilename_.c_str());
	m_sName = sAlias_;
}

Music::~Music()
{
	Mix_FreeMusic(m_pMusic);
}

void Music::loadMusic(string sFilename_, string sAlias_)
{
	m_pMusic = Mix_LoadMUS(sFilename_.c_str());
	m_sName = sAlias_;
}

void Music::playMusic()
{
	Mix_PlayMusic(m_pMusic, 1);
}

void Music::playMusicRepeat(int iNumLoops_)
{
	Mix_PlayMusic(m_pMusic, iNumLoops_);
}

void Music::playMusicFade(int iNumLoops_, int iMiliSecs_)
{
	Mix_FadeInMusic(m_pMusic, iNumLoops_, iMiliSecs_);
}

void Music::playMusicFrom(double dPosition_, int iNumLoops_)
{

    //Mix_RewindMusic();
    //Mix_SetMusicPosition(dPosition_);
    //playMusicRepeat(iNumLoops_);
    playMusicFadeFrom(dPosition_, iNumLoops_, 0);
	//Mix_FadeInMusicPos(m_pMusic, iNumLoops_, 0, dPosition_);
}

void Music::playMusicFadeFrom(double dPosition_, int iNumLoops_,
                               int iMiliSecs_)
{
	Mix_FadeInMusicPos(m_pMusic, iNumLoops_, iMiliSecs_, dPosition_);
}

string Music::getName()
{
	return m_sName;
}

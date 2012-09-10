#ifndef _MUSIC_H_
#define _MUSIC_H_
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <string>

using namespace std;

class Music
{
	private:

		Mix_Music*		m_pMusic;
		string			m_sName;

	public:

		Music();
		Music(string sFilename_, string sAlias_);
		~Music();

		void			loadMusic(string sFilename_, string sAlias_);
		string			getName();

		void			playMusic();
		void			playMusicRepeat(int iNumLoops_);
		void			playMusicFade(int iNumLoops_, int iMiliSecs_);
		void			playMusicFrom(double dPosition_, int iNumLoops_);
		void			playMusicFadeFrom(double dPosition_, int iNumLoops_,
										  int iMiliSecs_);

};

#endif


#ifndef _SOUND_H_
#define _SOUND_H_
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <string>

#define MAX_VOLUME 255
#define MIN_VOLUME 0

using namespace std;

class Sound
{
	private:

		Mix_Chunk*			m_pChunk;  // The SDL type that holds all the sound
                                       // data for the computer to use.
		string				m_sName;   // The alias used to reference the sound.
		int					m_iVolume; // The volume level of the sound.

	public:

		Sound();
		Sound(string sFilename_, string sAlias_);
		~Sound();

        ////////////////////////////////////////////////////////////////////////
        //   FUNCTIONS FOR LOADING AND RETRIEVING INFO ABOUT THE SOUND OBJECT
        ////////////////////////////////////////////////////////////////////////

		void				loadSound(string sFilename_, string sAlias_);
		void				setVolume(int iVolume_);
		string		        getName();
		int					getVolume();

		////////////////////////////////////////////////////////////////////////
        //                     FUNCTIONS FOR PLAYING SOUND
        ////////////////////////////////////////////////////////////////////////

		void				playSound(int iChannel_);
		void				playSoundRepeat(int iChannel_, int NumLoops_);
		void				playSoundTimed(int iChannel_, int iNumLoops_,
										   int iTicks_);
		void				playSoundFade(int iChannel_, int iNumLoops_,
										  int iMiliSecs_);
		void				playSoundFadeTimed(int iChannel_, int iNumLoops_,
											   int iMiliSecs_, int iTicks_);

};

#endif


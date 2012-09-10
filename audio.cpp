

#include "audio.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <vector>
#include <string>
#include "sound.h"
#include "music.h"
#include "mathfunctions.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::CAudio
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 29, 2007
//
// Function:            Initializes the audio class and specifies the number
//                      of sound channels there will be available to play
//                      sounds on at one time while the program is running.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
Audio::Audio()
{
    //The number of sound channels available for sound playing
	channels = 32;
	maxFullHearDistance = 500;
	maxSoundDistance = 1200;
	intervalPerVolumeDropoff = (maxSoundDistance - maxFullHearDistance) / MIN_VOLUME;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::~CAudio
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 29, 2007
//
// Function:            Destructor for the audio class. Does nothing.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
Audio::~Audio()
{

}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::Init
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 29, 2007
//
// Function:            Initializes the audio system to be able to begin
//                      using sound and music. Opens the audio subsystem
//                      and allocates the sound channels for playback. This
//                      function must be called before any sound or music
//                      playback can begin.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::init()
{
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
				  MIX_DEFAULT_CHANNELS, 4096);

	Mix_AllocateChannels(channels);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::Close
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 29, 2007
//
// Function:            Closes the audio subsystem and frees memory that was
//                      being used by the subsystem. Should be called prior
//                      the programing closing. No music or sound playback
//                      should be done after this function is called.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::close()
{
	Mix_CloseAudio();
	for(int i = 0; i < sounds.size(); ++i)
	{
        delete sounds[i];
	}

	for(int i = 0; i < music.size(); ++i)
	{
        delete music[i];
	}
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::DoesNameExist
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an alias name and returns whether or not
//                      a music or sound file was loaded using that name.
//                      Used for making sure two files do not get loaded
//                      with the same alias name.
//
// Inputs:              string sAlias_ - The alias name that will be checked
//                                       with all the sound and music files.
//
// Outputs:             None.
//
// Returns:             Bool - Whether or not the name exists in either the
//                             sound or music vectors.
////////////////////////////////////////////////////////////////////////////////
bool Audio::doesNameExist(string sAlias_)
{
    //Loop through all the sounds in the vector checking if any of the names
    //match the given alias. If so then that alias exists and true is returned.
	for(int i = 0; i < sounds.size(); ++i)
	{
		if(sounds[i]->getName() == sAlias_)
            return true;
	}
    //Loop through all the musics in the vector checking if any of the names
    //match the given alias. If so then that alias exists and true is returned.
	for(int i = 0; i < music.size(); ++i)
	{
		if(music[i]->getName() == sAlias_)
			return true;
	}
    //All aliases were checked an no match was found, therefore that alias does
    //not exist.
	return false;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::FindSound
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an alias name and if the alias name exists,
//                      it finds which index number it is in the sound
//                      vector and returns that number. Returns -1 if no
//                      sound was found with that alias.
//
// Inputs:              string sAlias_ - The alias name that will be checked
//                                       with all the sound files.
//
// Outputs:             None.
//
// Returns:             Int - The index number of the sound vector that
//                            corresponds to the alias name given. -1 if no
//                            sound matches that alias.
////////////////////////////////////////////////////////////////////////////////
int Audio::findSound(string sAlias_)
{
    //Loop through all the sounds in the sound vector checking if any of the
    //names match the given alias. If so then return the return the index to the
    //matching sound.
	for(int i = 0; i < sounds.size(); ++i)
	{
		if(sounds[i]->getName() == sAlias_)
			return i;
	}
    //No sound matched the given alias, return -1 to indicate so.
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::FindMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an alias name and if the alias name exists,
//                      it returns the Music pointer for that alias. Returns
//                      NULL if no Music was found for that alias.
//
// Inputs:              string sAlias_ - The alias name that will be checked
//                                       with all the sound and music files.
//
// Outputs:             None.
//
// Returns:             Music* - The music pointer that corresponds to the
//                               given alias. NULL is returns if no music
//                               corresponds to the given alias.
////////////////////////////////////////////////////////////////////////////////
Music* Audio::findMusic(string sAlias_)
{
    //Loop through all the musics in the music vector checking if any of the
    //names match the given alias. If so then return the return the address of
    //the matching music object.
	for(int i = 0; i < music.size(); ++i)
	{
		if(music[i]->getName() == sAlias_)
			return music[i];
	}
	//No music matched the given alias. Return NULL to indicate so.
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::FindFreeChannel
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Finds a free channel to play a sound on. Returns the
//                      number of the free channel. Returns -1 if no channel
//                      is free.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             Int - The number of the free channel. Return is -1
//                            if there is no free channel.
////////////////////////////////////////////////////////////////////////////////
int Audio::findFreeChannel()
{
    //Loop through all the channels and check to see if they are currently
    //playing a sound. If not then return the number of the channel that is free
	for(int i = 0; i < channels; ++i)
	{
	    //Check to see if the sound channel is free
		if(0 == Mix_Playing(i))
		{
			return i;
		}

	}
    //No sound channels were free. Return -1 to indicate so.
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::ConvertTo3DSoundAngle
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in a normal unit circle angle and converts it
//                      into a SDL sound angle for 3D audio.
//
//                      Normal angle =   90           SDL angle =   0
//                                       ---                       ---
//                                     /     \                   /     \
//                                 180 |     | 0             270 |     | 90
//                                     \     /                   \     /
//                                       ---                       ---
//                                       270                       180
//
// Inputs:              double dAngle_ - The normal unit circle angle to be
//                                       converted to an SDL 3D sound angle.
//
// Outputs:             None.
//
// Returns:             Double - The correct SDL 3D sound angle that was
//                               obtained by converting the input angle.
////////////////////////////////////////////////////////////////////////////////
double Audio::convertTo3DSoundAngle(double dAngle_)
{
	double dAngle = dAngle_;

	const int ZERO_DEGREES = 0;
	const int NINETY_DEGREES = 90;
    const int ONEEIGHTY_DEGREES = 180;
    const int TWOSEVENTY_DEGREES = 270;
    const int TWOTWENTYFIVE_DEGREES = 225;


    //Converts the normal angle to an SDL 3D sound angle
	if(ZERO_DEGREES <= dAngle && NINETY_DEGREES >= dAngle)
	{
		dAngle = NINETY_DEGREES - dAngle;
	}
	else if(TWOSEVENTY_DEGREES >= dAngle)
	{
		double dDifference = (dAngle - TWOSEVENTY_DEGREES) * 2;
		dAngle_ = dAngle - NINETY_DEGREES - dDifference;
	}
	else if(ONEEIGHTY_DEGREES <= dAngle && TWOSEVENTY_DEGREES > dAngle)
	{
		if(TWOTWENTYFIVE_DEGREES >= dAngle)
		{
			double dDifference = (TWOSEVENTY_DEGREES - dAngle);
			dDifference = NINETY_DEGREES - (dDifference);
			dDifference = NINETY_DEGREES - (dDifference * 2);
			dAngle += dDifference;
		}
		else
		{
			double dDifference = (TWOSEVENTY_DEGREES - dAngle);
			dDifference = NINETY_DEGREES - (dDifference * 2);
			dAngle -= dDifference;
		}

	}
	else
	{
		double dDifference = ONEEIGHTY_DEGREES - dAngle;
		dAngle_ = dAngle + NINETY_DEGREES + (dDifference * 2);
	}

    //After all changes have been made to the normal angle, return the SDL 3D
    //sound angle that corresponded to the inputed angle.
	return dAngle;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::Calc3DSoundVolume
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an X and Y for the listener and an X and Y
//                      for the sound source and calculates how loud the
//                      sound should come over through the speakers.
//
// Inputs:              double dXEar_ - The X location of the listener
//                      double dYEar_ - The Y location of the listener
//                      double dXSrc_ - The X location of the sound source
//                      double dYSrc_ - The Y location of the sound source
//
// Outputs:             None.
//
// Returns:             Int - The correct volume of how loud the sound
//                            should sound to the listener. 0 is the loudest
//                            255 if the quietest
////////////////////////////////////////////////////////////////////////////////
int Audio::calc3DSoundVolume(double dXEar_, double dYEar_,
                              double dXSrc_, double dYSrc_)
{
    //The volume for the sound
    int iVolume = 0;

    //Calculates distance from listener to sound source
	int iDistance = distBetween(dXEar_, dYEar_, dXSrc_, dYSrc_);

    //If the distance between the listener and the sound source is less than the
    //max volume distance. Set the volume to max (SDL volume of zero)
	if(iDistance < maxFullHearDistance)
		iVolume = MAX_VOLUME;
    //If sound distance is farther than the max distance for full volume,
    //decrease the volume one notch time for every iDistanceInterval_ the sound
    //is away.
	else
		iVolume = (iDistance - maxFullHearDistance) / intervalPerVolumeDropoff;

    //If the calculated volume is lower than the lowest volume level, set the
    //volume to the lowest volume level.
	if(MIN_VOLUME < iVolume)
		iVolume = MIN_VOLUME;

	return iVolume;
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::LoadSound
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in a filename and an alias that will be used
//                      to recognize that filename later in the future.
//                      Loads the sound to the sound vector if the given
//                      alias has not yet been used.
//
// Inputs:              string sFilename_ - The location of the sound file
//                                          in the folder.
//                      string sAlias_    - The name that will be used later
//                                          to reference the sound being loaded.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::loadSound(string sFilename_, string sAlias_)
{
    //Check to see if the alias does not exist before loading a sound with the
    //given alias
	if(doesNameExist(sAlias_))
		return;

    //Add the sound onto the sound vector with the given alias
	sounds.push_back(new Sound());
	sounds[sounds.size() - 1]->loadSound(sFilename_, sAlias_);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::LoadMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in a filename and an alias that will be used
//                      to recognize that filename later in the future.
//                      Loads the music to the music vector if the given
//                      alias has not yet been used.
//
// Inputs:              string sFilename_ - The location of the music file
//                                          in the folder.
//                      string sAlias_    - The name that will be used later
//                                          to reference the music being
//                                          loaded.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::loadMusic(string sFilename_, string sAlias_)
{
    //Check to see if the alias does not exist before loading the music with the
    //given alias
	if(doesNameExist(sAlias_))
		return;

    //Add the music to the music vector with the given alias
	music.push_back(new Music());
	music[music.size() - 1]->loadMusic(sFilename_, sAlias_);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlaySound
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an alias and plays the sound that
//                      corresponds to the alias on a free open sound
//                      channel. Does nothing if no sound corresponds to the
//                      given alias or there is no free sound channel.
//
// Inputs:              string sAlias_ - The name used to reference the
//                                       desired sound to be played.
//
// Outputs:             The desired sound at full volume.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playSound(string sAlias_)
{
    //Find the sound index the corresponds to the given alias
    int iSound = findSound(sAlias_);

    //If no sould corresponded to the alias, end the function and play nothing
	if(-1 == iSound)
		return;

    //Find a free sound channel
	int iFreeChannel = findFreeChannel();

    //If no sound channel was free, end the function and play nothing
	if(-1 == iFreeChannel)
		return;

    //Set the sound to full volume and to be played on both speakers and play
    //the sound
	Mix_SetPosition(iFreeChannel, 0, 0);
	sounds[iSound]->playSound(iFreeChannel);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlaySound3D
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an alias and plays the sound that
//                      corresponds to the alias on a free open sound
//                      channel. The sound should be played coming from the
//                      correct direction and volume determined on the where
//                      listener and the sound are at. Nothing is played if
//                      no sound corresponds to the given alias or all
//                      sound channels are taken.
//                      Example - If someone shoots a gun far off in the
//                                distance in the left direction, the sound
//                                should sound faint coming out of the left
//                                speaker.
//
// Inputs:              string sAlias_ - The name used to reference the
//                                       desired sound to be played.
//
// Outputs:             The desired sound at the correct volume and
//                      direction
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playSound3D(string sAlias_, double dXEar_, double dYEar_,
						double dXSrc_, double dYSrc_)
{
    const double RADIANS_TO_DEGREES = 180 / 3.14;

    //Find a free sound channel
	int iFreeChannel = findFreeChannel();

    //If no sound channel was free, end the function and play nothing
	if(-1 == iFreeChannel)
		return;

    //Find the sound index the corresponds to the given alias
    int iSound = findSound(sAlias_);

    //If no sould corresponded to the alias, end the function and play nothing
    if(-1 == iSound)
		return;

    //Find what angle the sound makes with the listener and convert to degrees
	double dAngle = calcAngle(dXEar_, dYEar_, dXSrc_, dYSrc_) *
							 RADIANS_TO_DEGREES;

    //Convert the angle to an SDL sound angle for playback
	dAngle = convertTo3DSoundAngle(dAngle);
    //Calculate what volume the sound volume should be by using the function
	int iDistance = calc3DSoundVolume(dXEar_, dYEar_, dXSrc_, dYSrc_);

    //Set the sounds position and volume so if plays out of the speakers
    //correctly
	Mix_SetPosition(iFreeChannel, dAngle, iDistance);

    //Play the sound
	sounds[iSound]->playSound(iFreeChannel);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlayMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Sept 30, 2007
//
// Function:            Takes in an alias and plays the song that
//                      corresponds with the alias only once.
//
// Inputs:              string sAlias_ - The name used to reference the
//                                       desired music to be played.
//
// Outputs:             The desired music only once.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playMusic(string sAlias_)
{
    //Find the music that corresponds to the given alias
	Music* TempMusic_ = findMusic(sAlias_);

    //If there was a music file that corresponded to the alias, play it.
    //Otherwise do nothing.
    if(NULL != TempMusic_)
        TempMusic_->playMusic();
}


////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlayMusicRepeat
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Takes in an alias and a number of times to repeat.
//                      Play that song that corresponds with the alias the
//                      repeat number of times. A repeat number of -1 will
//                      play forever or until the StopMusic function is
//                      called.
//
// Inputs:              string sAlias_ - The name used to reference the
//                                       desired music to be played.
//                      int iNumLoops_ - The number of times to play
//                                       the song. -1 plays forever.
//
// Outputs:             The desired music the repeat number of times.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playMusicRepeat(string sAlias_, int iNumLoops_)
{
    //Grab the music that corresponds to the alias and play it with repeating.
	Music* TempMusic = findMusic(sAlias_);
	TempMusic->playMusicRepeat(iNumLoops_);
}


////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlayMusicFade
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Takes in an alias and a number of times to repeat
//                      and the number of miliseconds to fade into the song.
//                      Play that song that corresponds with the alias the
//                      repeat number of times. A repeat number of -1 will
//                      play forever or until the StopMusic function is
//                      called.
//
// Inputs:              string sAlias_ - The name used to reference the
//                                       desired music to be played.
//                      int iNumLoops_ - The number of times to play
//                                       the song. -1 plays forever.
//                      int iMiliSecs_ - The number of miliseconds it
//                                       takes to fully fade into the
//                                       song.
//
// Outputs:             The desired music the repeat number of times while
//                      fading into the music.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playMusicFade(string sAlias_, int iNumLoops_, int iMiliSecs_)
{
	Music* TempMusic = findMusic(sAlias_);
	TempMusic->playMusicFade(iNumLoops_, iMiliSecs_);
}


////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlayMusicFrom
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Takes in an alias and a number of times to repeat
//                      and the number of miliseconds into the song to start.
//                      Play that song that corresponds with the alias the
//                      repeat number of times starting at the indicated number
//                      of milliseconds from the start. A repeat number of -1
//                      will play forever or until the StopMusic function is
//                      called.
//
// Inputs:              string sAlias_    - The name used to reference the
//                                          desired music to be played.
//                      double dPosition_ - The number of seconds from the
//                                          beginning to start playing the song.
//                      int iNumLoops_    - The number of times to play
//                                          the song. -1 plays forever.
//
//
// Outputs:             The desired music the repeat number of times starting
//                      from a given location.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playMusicFrom(string sAlias_, double dPosition_, int iNumLoops_)
{
	Music* TempMusic = findMusic(sAlias_);

	TempMusic->playMusicFrom(dPosition_, iNumLoops_);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PlayMusicFadeFrom
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Takes in an alias and a number of times to repeat
//                      and the number of miliseconds into the song to start
//                      while fading in over a time of given milliseconds.
//                      Play that song that corresponds with the alias the
//                      repeat number of times starting at the indicated number
//                      of milliseconds from the start. A repeat number of -1
//                      will play forever or until the StopMusic function is
//                      called.
//
// Inputs:              string sAlias_    - The name used to reference the
//                                          desired music to be played.
//                      double dPosition_ - The number of seconds from the
//                                          beginning to start playing the song.
//                      int iNumLoops_    - The number of times to play
//                                          the song. -1 plays forever.
//                      int iMiliSecs_    - The number of miliseconds it
//                                          takes to fully fade into the
//                                          song.
//
//
// Outputs:             The desired music the repeat number of times while
//                      fading into the music and starting from a given
//                      location.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::playMusicFadeFrom(string sAlias_, double dPosition_, int iNumLoops_,
							  int iMiliSecs_)
{
	Music* TempMusic = findMusic(sAlias_);

	TempMusic->playMusicFadeFrom(dPosition_, iNumLoops_, iMiliSecs_);
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::PauseMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Pauses any music that is playing.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::pauseMusic()
{
	Mix_PauseMusic();
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::ResumeMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Resumes any music that is paused.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::resumeMusic()
{
	Mix_ResumeMusic();
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::StopMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Stops any music that is playing.
//
// Inputs:              None.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::stopMusic()
{
    Mix_HaltMusic();
}

////////////////////////////////////////////////////////////////////////////////
// Function:            CAudio::FadeOutMusic
//
// Last Modified by:    Roby Atadero
//
// Last Modified:       Oct 12, 2007
//
// Function:            Stops the music by fading it out over a given time.
//
// Inputs:              int iMiliSecs_ - The number of miliseconds to fade the
//                                       song out over.
//
// Outputs:             None.
//
// Returns:             None.
////////////////////////////////////////////////////////////////////////////////
void Audio::fadeOutMusic(int iMiliSecs_)
{
	Mix_FadeOutMusic(iMiliSecs_);
}

void Audio::setMaxSoundDistance(double distance)
{
    maxSoundDistance = distance;
    intervalPerVolumeDropoff = (maxSoundDistance - maxFullHearDistance) / 255.0;
}

void Audio::setMaxFullHearDistance(double distance)
{
    maxFullHearDistance = distance;
    intervalPerVolumeDropoff = (maxSoundDistance - maxFullHearDistance) / 255.0;
}

void Audio::deleteAllMusic()
{
    for(int i = 0; i < music.size(); ++i)
    {
        delete music[i];
    }
    music.erase(music.begin(), music.end());
}

void Audio::deleteAllSounds()
{
    for(int i = 0; i < sounds.size(); ++i)
    {
        delete sounds[i];
    }
    sounds.erase(sounds.begin(), sounds.end());
}

void Audio::deleteMusic(string alias)
{
    for(int i = 0; i < music.size(); ++i)
    {
        if(music[i]->getName() == alias)
        {
            delete music[i];
            music.erase(music.begin() + i);
            return;
        }
    }
}

void Audio::deleteSound(string alias)
{
    for(int i = 0; i < sounds.size(); ++i)
    {
        if(sounds[i]->getName() == alias)
        {
            delete sounds[i];
            sounds.erase(sounds.begin() + i);
            return;
        }
    }
}


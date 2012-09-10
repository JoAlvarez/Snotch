///@file
///@brief File for the audio class.
///
/// This will take care of all the loading and playing of sound
/// and music files that are used for the program. These functions
/// should not be explicitly called by the user. The ResourceMgr
/// will be calling all of these functions.
///
///Copyright 2008, Roby Atadero
///
///Please give credit if using this in your software.
///
///@author Roby Atadero
///@version 0.70
///@date 2008

///@addtogroup audioclasses Audio Classes
///All classes that related to using audio
///@{

#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <vector>
#include "sound.h"
#include "music.h"
#include <string>

#define INFINATE_REPEAT -1

using namespace std;

///@brief File for the audio class.
///
/// This will take care of all the loading and playing of sound
/// and music files that are used for the program.
class Audio
{
	private:

		vector<Sound*> sounds;
		vector<Music*> music;
		int	channels;


		int    findSound(string alias);
		Music* findMusic(string alias);
		bool   doesNameExist(string alias);
		int    findFreeChannel();
		double convertTo3DSoundAngle(double angle);
		int    calc3DSoundVolume(double xEar, double yEar, double xSrc, double ySrc);

        double maxSoundDistance;
        double maxFullHearDistance;
        double intervalPerVolumeDropoff;

	public:

        /// @brief Default Constructor for the Audio class.
		Audio();
		~Audio();

        /// @brief Initializes the audio components.
        ///
        /// This must be called prior to loading or playing any
        /// sound or music files. Nothing will play if this function
        /// is not called.
		void init();

        /// @brief Shuts down the audio components.
        ///
        /// This should be called prior to the program ending
        /// to ensure that all the audio resources are freed
        /// from the computer.
		void close();

		/// @brief Loads a sound file.
		///
		/// Loads a sound file into memory so that it can be played later.
		/// This should only be a WAV file.
        /// @param filename The exact location of the WAV file. Can use a
        /// reference or a direct location as a location for the file.
        /// Example: "./sounds/boom.wav" Means the file will be found in the
        /// running directory under the folder "sounds".
        /// @param alias The name that will be used to reference the sound
        /// later when wanting to play it back.
		void loadSound(string filename, string alias);

        /// @brief Loads a music file.
		///
		/// Loads a music file into memory so that it can be played later.
		/// This can be a WAV, MP3, OGG, MIDI, and MOD files. Suggested not
		/// to use MP3's since there can be some problems with these files
		/// during playback.
        /// @param filename The exact location of the music file. Can use a
        /// reference or a direct location as a location for the file.
        /// Example: "./music/backgroundmusic.ogg" Means the file will be
        /// found in the running directory under the folder "music".
        /// @param alias The name that will be used to reference the music
        /// later when wanting to play it back.
		void loadMusic(string filename, string alias);

        /// @brief Plays a sound at full volume through all speakers.
        ///
        /// Plays the sound that identifies with the alias given through
        /// all the speakers at full volume.
        /// @param alias The name that references the sounds file. Should
        /// match the alias that was passed in during loadSound for that sound.
		void playSound  (string alias);

		/// @brief Plays a sound through the speakers at a given location.
		///
		/// Plays a sound through the speakers with the correct volume and
		/// location that matches the ear and location of the sound. Sounds
		/// that come from the left side of the ear will come through mostly
		/// the left speaker. The farther away a sound is from the ear, the
		/// fainter the sound will be.
		/// @param alias The name that references the sound file. Should
		/// match the alias that was passed in during loadSound for that sound.
		/// @param xEar The x location of the listening ear.
		/// @param yEar The y location of the listening ear.
		/// @param xSrc The x location of where the sound is originating from.
		/// @param ySrc The y location of where the sound is originating from.
		void playSound3D(string alias, double xEar, double yEar, double xSrc, double ySrc);

        /// @brief Plays a music file.
        ///
        /// Plays a music file that is referenced with the given alias. Will
        /// play this music file one play through and stop.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		void playMusic(string alias);

		/// @brief Plays a music file multiple times
        ///
        /// Plays a music file that is referenced with the given alias. Will
        /// play this music file as many of times as the number given into the
        /// function.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		/// @param numLoops The number of times to play the song. 0 does not
		/// play it, 2 plays it 2 times, -1 plays it forever until the song is
		/// stopped or paused.
		void playMusicRepeat(string alias, int numLoops);

		/// @brief Fades in a music file that plays multiple times.
        ///
        /// Fades in a music file that is referenced with the given alias. Will
        /// play this music file as many of times as the number given into the
        /// function.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		/// @param numLoops The number of times to play the song. 0 does not
		/// play it, 2 plays it 2 times, -1 plays it forever until the song is
		/// stopped or paused.
		/// @param miliSecs How many miliseconds it takes to fade into the song.
		/// At the end of that time, the music should be at full volume.
		void playMusicFade(string alias, int numLoops, int miliSecs);

        /// @brief Plays a music file multiple times while starting from a given position.
        ///
        /// Plays a music file that is referenced with the given alias. The song
        /// will start at a given amount of seconds into the song. Will
        /// play this music file as many of times as the number given into the
        /// function.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		/// @param position The number of seconds into the song to start playing
		/// from.
		/// @param numLoops The number of times to play the song. 0 does not
		/// play it, 2 plays it 2 times, -1 plays it forever until the song is
		/// stopped or paused.
		void playMusicFrom(string alias, double position, int numLoops);

        /// @brief Plays a music file multiple times while starting from a
        /// given position and fading in.
        ///
        /// Plays a music file that is referenced with the given alias. The song
        /// will start at a given amount of seconds into the song while fading in
        /// for a given amount of miliseconds. Will play this music file as many of
        /// times as the number given into the function.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		/// @param position The number of seconds into the song to start playing
		/// from.
		/// @param numLoops The number of times to play the song. 0 does not
		/// play it, 2 plays it 2 times, -1 plays it forever until the song is
		/// stopped or paused.
		/// @param miliSecs How many miliseconds it takes to fade into the song.
		/// At the end of that time, the music should be at full volume.
		void playMusicFadeFrom(string alias, double position, int numLoops, int miliSecs);

        /// @brief Pauses any music playing.
        ///
        /// Will pause any music currently playing.
        /// A subsequent call resumeMusic will replay the song where you paused it.
		void pauseMusic();

		/// @brief Resumes any paused music.
        ///
        /// Will resume any music that was paused.
        /// Calling this on non-paused music does nothing.
		void resumeMusic();

		///@brief Stops any playing music.
        ///
        /// Will stop any music currently playing. Once stopped the song
        /// cannot be started again unless using playMusic or any of its
        /// counterparts that do fading and looping.
		void stopMusic();

		///@brief Fades out music over a given time.
        ///
        /// Will fade out any music playing over the time of the given
        /// amount of miliseconds.
        /// @param miliSecs The number of miliseconds it takes to fully
        /// fade out the music playing.
		void fadeOutMusic(int miliSecs);

        ///@brief Sets the maximum distance to where 3D sound is heard.
        ///
        /// Sets the maximum distance a sound can be playing while still being heard.
        /// The closer a sound is to the given distance, the fainter it sounds. If the
        /// sound is at or farther than the distance given, that sound will not be heard.
        ///
        /// This only effects when you use playSound3D
        /// @param distance The maximum amount of distance that 3D sounds can be heard.
		void setMaxSoundDistance(double distance);

		///@brief Sets the maximum distance that a sound is still heard at full volume.
        ///
        /// Sets the maximum distance that a sound can be while still being able to hear
        /// it at full volume.  Anything closer than that distance is still heard at full
        /// volume. Everything futher than this distance will sound fainter the farther it
        /// is away.
        void setMaxFullHearDistance(double distance);

        ///@brief Frees all loaded music from memory.
        ///
        /// This will unload all the loaded music from memory. Any want to play music after this
        /// requires reloading music using the loadMusic function.
        void deleteAllMusic();

        ///@brief Frees all loaded sounds from memory.
        ///
        /// This will unload all the loaded sounds from memory. Any want to play sounds after this
        /// requires reloading the sounds using the loadSound function.
        void deleteAllSounds();

        ///@brief Frees a specific music from memory.
        ///
        /// This will unload the music that matches the given alias from memory. Any want to play
        /// this music afterward requires reloading it using loadMusic.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
        void deleteMusic(string alias);

        ///@brief Frees a specific sound from memory.
        ///
        ///This will unload the sound that matches the given alias from memory.
        /// Any want to play this sound afterward requires reloading it using
        /// loadSound.
        /// @param alias The name that references the sound file. Should
		/// match the alias that was passed in during loadSound for that sound.
        void deleteSound(string alias);

};

#endif
///@}

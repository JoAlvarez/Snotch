///@file
///@brief File for the audio class.
///
/// This will take care of all the loading and playing of sound
/// and music files that are used for the program. These functions
/// should not be explicitly called by the user. The ResourceMgr
/// will be calling all of these functions. Essentially, it will
/// manage all of the resources of the project.
///
///Copyright 2008, Roby Atadero
///
///Please give credit if using this in your software.
///
///@author Roby Atadero
///@version 0.70
///@date 2008

///@addtogroup userclasses User Classes
///All classes that the programmer will directly use.
///@{

#ifndef __RESOURCEMGR_H__
#define __RESOURCEMGR_H__

#include <vector>
#include <string>
#include "image.h"
#include "audio.h"
#include "font.h"
#include "window.h"

using namespace std;

///@brief File for the resourceMgr.
///
/// This will take care of all the loading and playing/drawing of sound,
/// music, image, and font files that are used for the program.
class ResourceMgr
{
    private:
        Audio               audio;
        vector<Image*>      images;
        vector<Font*>       fonts;

        Window*             window;

        static              ResourceMgr* instance;
        static              int referenceCount;

        ResourceMgr();

        void                init();
        void                destroy();

        bool                imageIsOffScreen(double leftX, double rightX, double lowerY, double upperY);
        Image               getImage(string alias);

    public:

        /// @brief Gets the instance of the ResourceMgr object.
        ///
        /// Use this to obtain the instance of the ResourceMgr object.
        /// @return ResourceMgr* A pointer to the instance of the ResourceMgr object.
        static ResourceMgr* getInstance();

        /// @brief Releases the instance of the ResourceMgr object obtained.
        ///
        /// Release the instance of the ResourceMgr obtained from getInstance().
        /// This must be called on the pointer obtained from getInstance() to
        /// ensure that no memory leaks occur and that the ResourceMgr object is
        /// destroyed when nobody has an instance of the object.
        void                release();

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
        void                loadSound(string filename, string alias);

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
        void                loadMusic(string filename, string alias);

        /// @brief Loads an image file.
		///
		/// Loads an image file into memory so that it can be drawn later.
		/// This can be a BMP, JPEG, GIF, PNG, TIFF, TGA filetype.
        /// @param filename The exact location of the image file. Can use a
        /// reference or a direct location as a location for the file.
        /// Example: "./images/background.png" Means the file will be
        /// found in the running directory under the folder "images".
        /// @param alias The name that will be used to reference the image
        /// later when wanting to draw it.
        void                loadImage(string filename, string alias);

        /// @brief Loads an font file.
		///
		/// Loads an font file into memory so that it can be drawn later.
		/// This can be a TTF or RTF file.
        /// @param filename The exact location of the font file. Can use a
        /// reference or a direct location as a location for the file.
        /// Example: "./fonts/arial.ttf" Means the file will be
        /// found in the running directory under the folder "fonts".
        /// @param alias The name that will be used to reference the font
        /// later when wanting to draw text with it.
        void                loadFont (string filename, string alias, int size);


        /// @brief Plays a sound at full volume through all speakers.
        ///
        /// Plays the sound that identifies with the alias given through
        /// all the speakers at full volume.
        /// @param alias The name that references the sounds file. Should
        /// match the alias that was passed in during loadSound for that sound.
		void				playSound  (string alias);

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
		void				playSound3D(string alias,
                                        double xEar,
										double yEar,
										double xSrc,
										double ySrc);


        /// @brief Plays a music file.
        ///
        /// Plays a music file that is referenced with the given alias. Will
        /// play this music file one play through and stop.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		void				playMusic        (string alias);

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
		void				playMusicRepeat  (string alias, int numLoops);

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
		void				playMusicFade    (string alias, int numLoops,
										      int miliSecs);

        /// @brief Plays a music file multiple times while starting from a given position.
        ///
        /// Plays a music file that is referenced with the given alias. The song
        /// will start at a given amount of seconds into the song. Will
        /// play this music file as many of times as the number given into the
        /// function.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		/// @param numLoops The number of times to play the song. 0 does not
		/// play it, 2 plays it 2 times, -1 plays it forever until the song is
		/// stopped or paused.
		/// @param position The number of seconds into the song to start playing
		/// from.
		void				playMusicFrom    (string alias,int numLoops, double position);

		/// @brief Plays a music file multiple times while starting from a
        /// given position and fading in.
        ///
        /// Plays a music file that is referenced with the given alias. The song
        /// will start at a given amount of seconds into the song while fading in
        /// for a given amount of miliseconds. Will play this music file as many of
        /// times as the number given into the function.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		/// @param numLoops The number of times to play the song. 0 does not
		/// play it, 2 plays it 2 times, -1 plays it forever until the song is
		/// stopped or paused.
        /// @param position The number of seconds into the song to start playing
		/// from.
		/// @param miliSecs How many miliseconds it takes to fade into the song.
		/// At the end of that time, the music should be at full volume.
		void				playMusicFadeFrom(string alias, int numLoops,double position,
                                              int miliSecs);

        /// @brief Pauses any music playing.
        ///
        /// Will pause any music currently playing.
        /// A subsequent call resumeMusic will replay the song where you paused it.
		void				pauseMusic();

		/// @brief Resumes any paused music.
        ///
        /// Will resume any music that was paused.
        /// Calling this on non-paused music does nothing.
		void				resumeMusic();

		///@brief Stops any playing music.
        ///
        /// Will stop any music currently playing. Once stopped the song
        /// cannot be started again unless using playMusic or any of its
        /// counterparts that do fading and looping.
		void				stopMusic();

		///@brief Fades out music over a given time.
        ///
        /// Will fade out any music playing over the time of the given
        /// amount of miliseconds.
        /// @param miliSecs The number of miliseconds it takes to fully
        /// fade out the music playing.
		void				fadeOutMusic(int miliSecs);

        ///@brief Sets the maximum distance to where 3D sound is heard.
        ///
        /// Sets the maximum distance a sound can be playing while still being heard.
        /// The closer a sound is to the given distance, the fainter it sounds. If the
        /// sound is at or farther than the distance given, that sound will not be heard.
        ///
        /// This only effects when you use playSound3D
        /// @param distance The maximum amount of distance that 3D sounds can be heard.
		void                setMaxSoundDistance   (double distance);

		///@brief Sets the maximum distance that a sound is still heard at full volume.
        ///
        /// Sets the maximum distance that a sound can be while still being able to hear
        /// it at full volume.  Anything closer than that distance is still heard at full
        /// volume. Everything futher than this distance will sound fainter the farther it
        /// is away.
		void                setMaxFullHearDistance(double distance);

        /// @brief Draws an image on the screen to the given coordinates.
        ///
        /// Draws an image that cooresponds to the given alias in the rectangle specified
        /// by the given coordinates. The image will stretch to fit the rectangle.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param leftX The left x coordinate of the rectangle the image will be drawn in.
        /// @param rightX The right x coordinate of the rectangle the image will be drawn in.
        /// @param lowerY The lower y coordinate of the rectangle the image will be drawn in.
        /// @param upperY The upper y coordinate of the rectangle the image will be drawn in.
        void                drawImage(string alias, double leftX,  double rightX,
                                                    double lowerY, double upperY);

        /// @brief Draws an image on the screen to the given coordinates and rotated by a given angle.
        ///
        /// Draws an image that cooresponds to the given alias in the rectangle specified
        /// by the given coordinates and rotated by the given angle amount. The image will stretch to
        /// fit the rectangle.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param angle The angle amount the image will be rotated. Expressed in degrees.
        /// @param leftX The left x coordinate of the rectangle the image will be drawn in.
        /// @param rightX The right x coordinate of the rectangle the image will be drawn in.
        /// @param lowerY The lower y coordinate of the rectangle the image will be drawn in.
        /// @param upperY The upper y coordinate of the rectangle the image will be drawn in.
        void                drawImage(string alias,  double angle,
                                      double leftX,  double rightX,
                                      double lowerY, double upperY);

        /// @brief Draws a section of an image on the screen to the given coordinates.
        ///
        /// Draws a section of a image that cooresponds to the given alias in the rectangle specified
        /// by the given coordinates. The way the section of image is
        /// secified is through percentages along the x and y coordinates of the image.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param leftX The left x coordinate of the rectangle the image will be drawn in.
        /// @param rightX The right x coordinate of the rectangle the image will be drawn in.
        /// @param lowerY The lower y coordinate of the rectangle the image will be drawn in.
        /// @param upperY The upper y coordinate of the rectangle the image will be drawn in.
        /// @param leftX_TexCoord The left x percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param rightX_TexCoord The right x percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param lowerY_TexCoord The lower y percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param upperY_TexCoord The upper y percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        void                drawImage(string alias, double leftX, double rightX,
                                      double leftY, double upperY,
                                      double leftX_TexCoord,  double rightX_TexCoord,
                                      double lowerY_TexCoord, double upperY_TexCoord);

        /// @brief Draws a section of an image on the screen to the given coordinates and rotated by a given angle.
        ///
        /// Draws a section of a image that cooresponds to the given alias in the rectangle specified
        /// by the given coordinates and rotated by the given angle amount. The way the section of image is
        /// secified is through percentages along the x and y coordinates of the image.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param angle The angle amount the image will be rotated. Expressed in degrees.
        /// @param leftX The left x coordinate of the rectangle the image will be drawn in.
        /// @param rightX The right x coordinate of the rectangle the image will be drawn in.
        /// @param lowerY The lower y coordinate of the rectangle the image will be drawn in.
        /// @param upperY The upper y coordinate of the rectangle the image will be drawn in.
        /// @param leftX_TexCoord The left x percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param rightX_TexCoord The right x percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param lowerY_TexCoord The lower y percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param upperY_TexCoord The upper y percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        void                drawImage(string alias,  double angle,
                                      double leftX,  double rightX,
                                      double lowerY, double upperY,
                                      double leftX_TexCoord,  double rightX_TexCoord,
                                      double lowerY_TexCoord, double upperY_TexCoord);

        /// @brief Draws an image on the screen to secific screen values.
        ///
        /// Draws an image that cooresponds to the given alias in the rectangle specified
        /// by the given window percentage coordinates. The image will stretch to fit the rectangle.
        /// The image will be in the same spot regardless the coordinate system that is being used.
        /// Suggested use for this would thinks like user interfaces and stats.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param percentageLeftX The left x percentage of the screen the image will be drawn in.
        /// @param percentageRightX The right x percentage of the screen the image will be drawn in.
        /// @param percentageLowerY The lower y percentage of the screen the image will be drawn in.
        /// @param percentageUpperY The upper y percentage of the screen the image will be drawn in.
        void                drawImageOverlay(string alias,
                                             double percentLeftX,  double percentRightX,
                                             double percentLowerY, double percentUpperY);

        /// @brief Draws an image on the screen to secific screen values and rotated by a given amount.
        ///
        /// Draws an image that cooresponds to the given alias in the rectangle specified
        /// by the given window percentage coordinates and rotated by a given angle amount.
        /// The image will stretch to fit the rectangle.
        /// The image will be in the same spot regardless the coordinate system that is being used.
        /// Suggested use for this would thinks like user interfaces and stats.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param angle The angle amount to rotate the image expressed in degrees.
        /// @param percentageLeftX The left x percentage of the screen the image will be drawn in.
        /// @param percentageRightX The right x percentage of the screen the image will be drawn in.
        /// @param percentageLowerY The lower y percentage of the screen the image will be drawn in.
        /// @param percentageUpperY The upper y percentage of the screen the image will be drawn in.
        void                drawImageOverlay(string alias,  double angle,
                                             double leftX,  double rightX,
                                             double lowerY, double upperY);

        /// @brief Draws a section of an image on the screen to secific screen values.
        ///
        /// Draws a section of an image that cooresponds to the given alias in the rectangle specified
        /// by the given window percentage coordinates.
        /// The image will stretch to fit the rectangle. The way the section of image is
        /// secified is through percentages along the x and y coordinates of the image.
        /// The image will be in the same spot regardless the coordinate system that is being used.
        /// Suggested use for this would thinks like user interfaces and stats.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param percentageLeftX The left x percentage of the screen the image will be drawn in.
        /// @param percentageRightX The right x percentage of the screen the image will be drawn in.
        /// @param percentageLowerY The lower y percentage of the screen the image will be drawn in.
        /// @param percentageUpperY The upper y percentage of the screen the image will be drawn in.
        /// @param leftX_TexCoord The left x percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param rightX_TexCoord The right x percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param lowerY_TexCoord The lower y percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param upperY_TexCoord The upper y percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        void                drawImageOverlay(string alias, double leftX, double rightX,
                                             double leftY, double upperY,
                                             double leftX_TexCoord,  double rightX_TexCoord,
                                             double lowerY_TexCoord, double upperY_TexCoord);

        /// @brief Draws a section of an image on the screen to secific screen values and being rotated.
        ///
        /// Draws a section of an image that cooresponds to the given alias in the rectangle specified
        /// by the given window percentage coordinates and rotated by a given angle amount.
        /// The image will stretch to fit the rectangle. The way the section of image is
        /// secified is through percentages along the x and y coordinates of the image.
        /// The image will be in the same spot regardless the coordinate system that is being used.
        /// Suggested use for this would thinks like user interfaces and stats.
        /// @param alias The alias that cooresponds the desired image to draw.
        /// @param angle The angle amount to rotate the image expressed in degrees.
        /// @param percentageLeftX The left x percentage of the screen the image will be drawn in.
        /// @param percentageRightX The right x percentage of the screen the image will be drawn in.
        /// @param percentageLowerY The lower y percentage of the screen the image will be drawn in.
        /// @param percentageUpperY The upper y percentage of the screen the image will be drawn in.
        /// @param leftX_TexCoord The left x percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param rightX_TexCoord The right x percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the far left of the texture, 1.0 means the far right, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param lowerY_TexCoord The lower y percentage starting point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        /// @param upperY_TexCoord The upper y percentage ending point of the section of image that is
        /// desired to be drawn. 0.0 means the bottom of the texture, 1.0 means the top, 0.5 means
        /// the middle. Texture wrapping is allowed so values like 1.5 and -0.25 are applicable.
        void                drawImageOverlay(string alias,  double angle,
                                             double leftX,  double rightX,
                                             double lowerY, double upperY,
                                             double leftX_TexCoord,  double rightX_TexCoord,
                                             double lowerY_TexCoord, double upperY_TexCoord);

        /// @brief Draws character text to the screen starting at specified values.
        ///
        /// Draws the string text to the screen with the lower left starting point of the
        /// text provided.
        /// @param alias The reference name of the font previously loaded.
        /// @param text The string of characters that is desired to be outputted to the screen.
        /// @param x The left x starting point of where the text will be drawn from.
        /// @param y The lower y starting point of where the text will be drawn from.
        void                drawText(string alias, string text, double x, double y);

        /// @brief Draws an integer to the screen starting at specified values.
        ///
        /// Draws the integer to the screen with the lower left starting point of the
        /// text provided.
        /// @param alias The reference name of the font previously loaded.
        /// @param numText The integer that is desired to be outputted to the screen.
        /// @param x The left x starting point of where the text will be drawn from.
        /// @param y The lower y starting point of where the text will be drawn from.
		void				drawText(string alias, int numText, double x, double y);

		/// @brief Draws an unsigned integer to the screen starting at specified values.
        ///
        /// Draws the unsigned integer to the screen with the lower left starting point of the
        /// text provided.
        /// @param alias The reference name of the font previously loaded.
        /// @param numText The unsigned integer that is desired to be outputted to the screen.
        /// @param x The left x starting point of where the text will be drawn from.
        /// @param y The lower y starting point of where the text will be drawn from.
		void                drawText(string alias, unsigned int numText, double x, double y);

		/// @brief Draws a double to the screen starting at specified values.
        ///
        /// Draws the double to the screen with the lower left starting point of the
        /// text provided.
        /// @param alias The reference name of the font previously loaded.
        /// @param numText The double that is desired to be outputted to the screen.
        /// @param x The left x starting point of where the text will be drawn from.
        /// @param y The lower y starting point of where the text will be drawn from.
		void				drawText(string alias, double numText, double x, double y);

        /// @brief Draws character text to the screen starting at specified screen percentages.
        ///
        /// Draws the string text to the screen with the lower left starting point percentage
        /// of the screen to begin drawing the text. The text will be drawin in the same spot
        /// regardless the coordinate system.
        /// @param alias The reference name of the font previously loaded.
        /// @param text The string of characters that is desired to be outputted to the screen.
        /// @param percentX The left x percentage of the screen where the text will be drawn from.
        /// Values range from 0.0 to 1.0. 0.0 is the left side of the screen. 1.0 is the right side.
        /// @param y The lower y starting point of where the text will be drawn from.
		void                drawTextOverlay(string alias, string text, double percentX, double percentY);

		/// @brief Draws an integer to the screen starting at specified screen percentages.
        ///
        /// Draws the integer to the screen with the lower left starting point percentage
        /// of the screen to begin drawing the text. The text will be drawin in the same spot
        /// regardless the coordinate system.
        /// @param alias The reference name of the font previously loaded.
        /// @param numText The integer that is desired to be outputted to the screen.
        /// @param percentX The left x percentage of the screen where the text will be drawn from.
        /// Values range from 0.0 to 1.0. 0.0 is the left side of the screen. 1.0 is the right side.
        /// @param y The lower y starting point of where the text will be drawn from.
		void                drawTextOverlay(string alias, int numText, double percentX, double percentY);

		/// @brief Draws an unsigned integer to the screen starting at specified screen percentages.
        ///
        /// Draws the unsigned integer to the screen with the lower left starting point percentage
        /// of the screen to begin drawing the text. The text will be drawin in the same spot
        /// regardless the coordinate system.
        /// @param alias The reference name of the font previously loaded.
        /// @param numText The unsigned integer that is desired to be outputted to the screen.
        /// @param percentX The left x percentage of the screen where the text will be drawn from.
        /// Values range from 0.0 to 1.0. 0.0 is the left side of the screen. 1.0 is the right side.
        /// @param y The lower y starting point of where the text will be drawn from.
		void                drawTextOverlay(string alias, unsigned int numText, double percentX, double percentY);

		/// @brief Draws a double to the screen starting at specified screen percentages.
        ///
        /// Draws the double to the screen with the lower left starting point percentage
        /// of the screen to begin drawing the text. The text will be drawin in the same spot
        /// regardless the coordinate system.
        /// @param alias The reference name of the font previously loaded.
        /// @param numText The double that is desired to be outputted to the screen.
        /// @param percentX The left x percentage of the screen where the text will be drawn from.
        /// Values range from 0.0 to 1.0. 0.0 is the left side of the screen. 1.0 is the right side.
        /// @param y The lower y starting point of where the text will be drawn from.
		void				drawTextOverlay(string alias, double numText, double percentX, double percentY);

        ///@brief Frees a specific image from memory.
        ///
        /// This will unload the image that matches the given alias from memory.
        /// Any want to draw this image afterward requires reloading it using
        /// loadImage.
        /// @param alias The name that references the image file. Should
		/// match the alias that was passed in during loadImage for that image.
		void                deleteImage(string alias);

		///@brief Frees a specific music from memory.
        ///
        /// This will unload the music that matches the given alias from memory. Any want to play
        /// this music afterward requires reloading it using loadMusic.
        /// @param alias The name that references the music file. Should
        /// match the alias that was passed in during loadMusic for that music.
		void                deleteMusic(string alias);

		///@brief Frees a specific sound from memory.
        ///
        /// This will unload the sound that matches the given alias from memory.
        /// Any want to play this sound afterward requires reloading it using
        /// loadSound.
        /// @param alias The name that references the sound file. Should
		/// match the alias that was passed in during loadSound for that sound.
		void                deleteSound(string alias);

		///@brief Frees a specific font from memory.
        ///
        /// This will unload the font that matches the given alias from memory.
        /// Any want to draw with this font afterward requires reloading it using
        /// loadFont.
        /// @param alias The name that references the font file. Should
		/// match the alias that was passed in during loadFont for that font.
		void                deleteFont (string alias);

        ///@brief Frees all loaded images from memory.
        ///
        /// This will unload all the loaded images from memory. Any want to draw images after this
        /// requires reloading the sounds using the loadImage function.
		void                deleteAllImages();

		///@brief Frees all loaded music from memory.
        ///
        /// This will unload all the loaded music from memory. Any want to play music after this
        /// requires reloading music using the loadMusic function.
		void                deleteAllMusic();

		///@brief Frees all loaded sounds from memory.
        ///
        /// This will unload all the loaded sounds from memory. Any want to play sounds after this
        /// requires reloading the sounds using the loadSound function.
		void                deleteAllSounds();

		///@brief Frees all loaded fonts from memory.
        ///
        /// This will unload all the loaded fonts from memory. Any want to draw text after this
        /// requires reloading the fonts using the loadFont function.
        void                deleteAllFonts();

};

#endif
///@}

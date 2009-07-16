/*
  This source file is part of the Cing project
  For the latest info, see http://www.cing.cc

  Copyright (c) 2006-2009 Julio Obelleiro and Jorge Cano

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef VIDEO_H_
#define VIDEO_H_

#include "VideoPrereqs.h"

// Ogre
#include "Ogre3d/include/OgreTimer.h"

#include <string>

namespace Cing
{

/**
 * @brief This class represents a video file that can be loaded from disk and which
 * frames can be grabbed individually. It supports all video codecs installed in the computer
 * 
 * @note This implementation is based on Open CV library
 */
class OCVMovie
{
public:

    // Initialization/Destruction
    OCVMovie();
    ~OCVMovie();

    // Init / end
    bool load(const char* fileName );
    void end();

		// Movie control
		void	play		();
		void	loop		();
		void	noLoop	();
		void	stop		();
		void	setFps	( int fps );

		// Read data from movie
		void read			( Image &image );

    // Queries
		bool						isValid		() const;
		unsigned short	getWidth	() const    { return m_width; }
		unsigned short	getHeight	() const    { return m_height; }
		unsigned short	getFps		() const    { return m_fps; }
		bool						newFrame	();
		bool						isPlaying	() const { return m_playing; }
		bool						isFinished() const { return m_finished;}

private:

    // Attributes
    CvCapture*      m_capture;      			///< OpenCV capture device
		std::string			m_fileName;						///< Name of the file loaded
		Ogre::Timer			m_timer;							///< Timer used to control the playback speed
		unsigned long		m_timeBetweenFramesMs;///< Time between frames (depends on the frames per second of the playback) in microseconds
		unsigned short	m_fps;								///< Frames per second of the video
    unsigned short  m_width;        			/// Movie's width
    unsigned short  m_height;       			/// Movie's height
		double					m_nFrames;						/// Movie's number of frames
		bool            m_loop;         			///< Loop video
		bool						m_playing;						///< Indicates whether the video is playing or not. If not playing it wont return images
    bool            m_finished;     			///< True when the video has finished
		bool						m_firstFrame;					///< True for the first read() call. Used to also give the first frame, regardles of the time passed
};

}

#endif

/*
  This source file is part of the Vision project
  For the latest info, see http://www.XXX.org

  Copyright (c) 2008 XXX

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

#ifndef _BaseCameraInput_H_
#define _BaseCameraInput_H_

#include "CameraInputPrereqs.h"

// OpenCV
#include "externLibs/OpenCV/cxcore/include/cxtypes.h"

// Graphics
#include "Graphics/TexturedQuad.h"

namespace CameraInput
{

/**
 * @internal
 * Base class for all the camera input (capture) devices.
 */
class BaseCameraInput
{
public:

	// Constructor / Destructor
  BaseCameraInput ();
  virtual ~BaseCameraInput();
  
	// Init / Release / Update (to be implemented in subclasses)
	virtual bool    init            ( int width = 320, int height = 240, int fps = 25, bool color = true );
	virtual void    end             ();
  virtual void    update          ();

  // Misc
  void            draw();

	// Query methods
	bool            isValid         () const { return m_bIsValid;   }
  bool            haveNewFrame    () const { return m_newFrame;   }
  int             getWidth        () const { return m_width;      }
  int             getHeight       () const { return m_height;     }
  int             getFPS          () const { return m_fps;        }
  int             getNumChannels  () const { return m_nChannels;  }
  IplImage*       getImage        () const { return m_currentCameraImage; }
  unsigned char*  getImageData    () const { return reinterpret_cast< unsigned char* >( m_currentCameraImage->imageData ); }
	 
protected:

  // Protected methods
  void  setNewFrameData         ( unsigned char* data, unsigned int size );
  void  setNewFrame             ( bool newFrame ) { m_newFrame = newFrame;    }  
  void  setWidth                ( int width   )   { m_width   = width;  }
  void  setHeight               ( int height  )   { m_height  = height; }
  void  setFPS                  ( int fps     )   { m_fps   = fps;  } 

private:
	// Attributes
  Graphics::TexturedQuad  m_texturedQuad;       ///< To render the camera images if required
  IplImage*               m_currentCameraImage; ///< Image captured from the camera 
  int                     m_width, m_height;    ///< Capture resolution
  int                     m_fps;                ///< Capture frames per second
  int                     m_nChannels;          ///< Number of channels of the camera captured images
  bool                    m_newFrame;           ///< True when the camera has a new frame captured
	bool                    m_bIsValid;	          ///< Indicates whether the class is valid or not. If invalid none of its methods except init should be called.

};

} // namespace CameraInput

#endif // _BaseCameraInput_H_
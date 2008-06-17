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

#ifndef _Vision_H_
#define _Vision_H_


/**
 * @internal
 * @file This is the entry include file from applications
 * It should include all the necessary files for the vision library, so the users don't need to 
 * worry about including files or namespaces
 */

#include <cstdio>
#include <cstring>
#include <stdlib.h>

// Graphics
#include "graphics/Object3D.h"
#include "graphics/Box.h"
#include "graphics/Plane.h"
#include "graphics/Sphere.h"
#include "graphics/PointLight.h"
#include "graphics/GraphicsTypes.h"
#include "graphics/Image.h"
#include "graphics/GraphicsUserAPI.h"
#include "graphics/LightingUserAPI.h"

// CameraInput
#include "cameraInput/OCVCamera.h"
#include "cameraInput/PVCamera.h"
#include "cameraInput/VICamera.h"

// Framework 
#include "framework/AppMain.h"
#include "framework/AppFramework.h"
#include "framework/UserAppGlobals.h"

// Common
#include "common/MathUtils.h"
#include "common/LogManager.h"
#include "common/CommonUserAPI.h"

// Input
#include "input/InputTypes.h"

// Computer Vision
#include "computervision/BlobFinder.h"
#include "computervision/BackgroundSubtraction.h"

// Physics
#include "physics/PhysicsUserAPI.h"
#include "physics/PhysicsBox.h"
#include "physics/PhysicsPlane.h"
#include "physics/PhysicsSphere.h"
#include "physics/PhysicsObject.h"

// Audio
#include "audio/SoundFMOD.h"
#include "audio/MicroFMOD.h"

// Movie
#include "movies/OCVMovie.h"

// GUI
#include "gui/GUIUserAPI.h"

// OGRE -> this is included because some Ogre objects are exposed to user application
// just in case an advanced user wants to use them...
#include "externLibs/Ogre3d/include/OgreSceneManager.h"
#include "externLibs/Ogre3d/include/OgreCamera.h"


// namespaces (the library user don't need to know about them...)
using namespace Framework;
using namespace CameraInput;
using namespace Graphics;
using namespace ComputerVision;
using namespace Globals;
using namespace Common;
using namespace Input;
using namespace Physics;
using namespace Audio;
using namespace	Movies;
using namespace GUI;

// Classes used by user

// Camera
typedef	VICamera Capture;

// Sound and Mic
typedef SoundFMOD Sound;
typedef MicroFMOD	Micro;

// Movie
typedef OCVMovie	Movie;

#endif // _Vision_H_
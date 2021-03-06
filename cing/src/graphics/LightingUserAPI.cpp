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

// Precompiled headers
#include "Cing-Precompiled.h"

#include "LightingUserAPI.h"
#include "GraphicsManager.h"

// Ogre
#include "OgreSceneManager.h"

// Framework
#include "framework/Application.h"

namespace Cing
{

/**
 * @brief Sets the ambient light of the scene. The ambient light affects all objects in the scene from all directions
 *
 * @param gray Gray value for the ambient light, this is, red, green and blue are equal
 */
void ambientLight( float gray )
{
  // Check application correctly initialized (could not be if the user didn't calle size function)
  Application::getSingleton().checkSubsystemsInit();

	GraphicsManager::getSingleton().getSceneManager().setAmbientLight( Color(gray , gray , gray).normalized() );
}

/**
 * @brief Sets the ambient light of the scene. The ambient light affects all objects in the scene from all directions
 *
 * @param red		Red value for the ambient light
 * @param green Green value for the ambient light
 * @param blue	Blue value for the ambient light
 */
void ambientLight( float red, float green, float blue )
{
  // Check application correctly initialized (could not be if the user didn't calle size function)
  Application::getSingleton().checkSubsystemsInit();

	GraphicsManager::getSingleton().getSceneManager().setAmbientLight( Color(red , green , blue).normalized() );
}

} // namespace Cing
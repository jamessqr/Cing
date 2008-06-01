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

#include "PointLight.h"

namespace Graphics
{

/**
 * @internal
 * @brief Constructor. Initializes class attributes.
 */
PointLight::PointLight():
  m_bIsValid( false )
{
}

/**
 * @internal
 * @brief Destructor. Class release.
 */
PointLight::~PointLight()
{
  // Release resources
  end();
}

/**
 * @internal
 * @brief Initializes the class so it becomes valid.
 *
 * @param[in] r Red component of the diffuse color of the light.    Value Range: 0..1
 * @param[in] g Green component of the diffuse color of the light.  Value Range: 0..1
 * @param[in] b Blue component of the diffuse color of the light.   Value Range: 0..1
 * @param[in] x x coordinate (horizontal axis) of the light in the scene
 * @param[in] y y coordinate (vertical axis) of the light in the scene
 * @param[in] z z coordinate (depth) of the light in the scene
 * @return true if the initialization was ok | false otherwise
 */
bool PointLight::init( float r, float g, float b, float x, float y, float z )
{
  // Check if the class is already initialized
  if ( isValid() )
    return true;

  // Init base light
  BaseLight::init();

  // Setup light
  setPosition( x, y, z );
  setDiffuseColor( r, g, b );

  // Set light type
  setLightType( Light::LT_POINT );

	// The class is now initialized
	m_bIsValid = true;

	return true;
}

/**
 * @internal
 * @brief Releases the class resources. 
 * After this method is called the class is not valid anymore.
 */
void PointLight::end()
{
  // Check if the class is already released
  if ( !isValid() )
    return;

  // Release base light
  BaseLight::end();

	// The class is not valid anymore
	m_bIsValid = false;
}

} // namespace Graphics
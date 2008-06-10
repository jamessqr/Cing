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

#ifndef _PhysicsObject_h_
#define _PhysicsObject_h_

#include "PhysicsPrereqs.h"

// Graphics
#include "graphics/Object3D.h"

namespace Physics
{

/**
 * @internal
 * @brief Controls the physics associated with an object of the scene.
 * This physics object creates a triangle based physic mesh, so if the 3d object is a simple primitive
 * such as a box or a sphere, specialized classes should be used to get better performance (like BoxPhysicsObject...)
 */
class PhysicsObject
{
public:

	// Constructor / Destructor
	PhysicsObject					();
	virtual ~PhysicsObject();

	// Init / Release / Update
	virtual void	init 			( Graphics::Object3D& object, bool statcObject );
	void					end				();	


	// Query  Methods
	bool					isValid	() { return m_bIsValid; }

protected:

	// Rigid bodies and collison shapes
	OgreBulletCollisions::CollisionShape*		buildTriMeshShape			( Graphics::Object3D& object );
	OgreBulletCollisions::CollisionShape*		buildBoxShape					( Graphics::Box& box );
	OgreBulletCollisions::CollisionShape*		buildStaticPlaneShape	( Graphics::Plane& plane );
	OgreBulletCollisions::CollisionShape*		buildSphereShape			( Graphics::Sphere& sphere );
	void																		createRigidBody	( Graphics::Object3D& object, OgreBulletCollisions::CollisionShape* collisionShape, bool staticBody );

private:

	// Attributes
	OgreBulletDynamics::RigidBody*	m_rigidBody;	///< Physics rigid body that will control and define the physics of this object
	bool														m_bIsValid;	  ///< Indicates whether the class is valid or not. If invalid none of its methods except init should be called.

};

} // namespace Physics

#endif // _PhysicsObject_h_
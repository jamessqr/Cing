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

#include "PhysicsManager.h"

// Common
#include "common/Release.h"

// Ogre bullet
#include "externLibs/OgreBullet/Dynamics/include/OgreBulletDynamicsWorld.h"
#include "externLibs/OgreBullet/Collisions/include/Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "externLibs/OgreBullet/Collisions/include/Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "externLibs/OgreBullet/Collisions/include/OgreBulletCollisionsShape.h"
#include "externLibs/OgreBullet/Collisions/include/Shapes/OgreBulletCollisionsBoxShape.h"
#include "externLibs/OgreBullet/Collisions/include/Shapes/OgreBulletCollisionsStaticPlaneShape.h"
#include "externLibs/OgreBullet/Collisions/include/Shapes/OgreBulletCollisionsSphereShape.h"
#include "externLibs/OgreBullet/Dynamics/include/OgreBulletDynamicsRigidBody.h"


namespace Physics
{

// Static member init
long	PhysicsManager::m_rigidObjectCounter				= 0;


/**
 * @internal
 * @brief Constructor. Initializes class attributes.
 */
PhysicsManager::PhysicsManager():
	m_physicsWorld				( NULL ),
	m_physicsDebugDrawer	( NULL ),
	m_bIsValid						( false )
{
}

/**
 * @internal
 * @brief Destructor. Class release.
 */
PhysicsManager::~PhysicsManager()
{
	// Release resources
	end();
}

/**
 * @internal
 * @brief Initializes the physics engine.
 *
 * @param sceneManager	General Scene manager
 * @param gravityVector	Gravity used in physics calculations
 * @param bounds				Bounds of the physics affected world
 */
void PhysicsManager::init( Ogre::SceneManager&	sceneManager, 
													 const Vector&				gravityVector /*= Vector3(0,-9.81,0)*/,
													 const AABox&					bounds				/*= AABox (Vector3 (-10000, -10000, -10000), Vector3 (10000,  10000,  10000))*/ )
{
	if ( isValid() )
		return;

	// Start Bullet Physics engine
	m_physicsWorld = new OgreBulletDynamics::DynamicsWorld ( &sceneManager, bounds, gravityVector );

	// add Debug info display tool
	m_physicsDebugDrawer = new OgreBulletCollisions::DebugDrawer();

	// Set the active debug drawer for physics
	m_physicsWorld->setDebugDrawer( m_physicsDebugDrawer );
	//m_physicsWorld->setShowDebugShapes( true );
	//m_physicsDebugDrawer->setDrawWireframe( true );

	// Attach it to the scene
	Ogre::SceneNode *node = sceneManager.getRootSceneNode()->createChildSceneNode( "physicsDebugDrawer", Vector::ZERO );
	node->attachObject(static_cast < Ogre::SimpleRenderable *>( m_physicsDebugDrawer ));

	m_bIsValid = true;
}

/**
 * @internal
 * @brief Releases the class resources. 
 * After this call no method of this object can be called without calling init method again.
 */	
void PhysicsManager::end()
{
	// Release bullet related stuff
	Common::Release( m_physicsWorld );

	m_bIsValid = false;
}

/**
 * @brief Updates the physics state
 *
 * @param elapsedSec Time elapsed since last frame in seconds
 */
void PhysicsManager::update( unsigned long elapsedSec )
{
	m_physicsWorld->stepSimulation( elapsedSec, MAX_SIMULATION_SUBSTEPS, FIXED_TIME_STEP );
}

/**
 * @brief Allows to debug physics, by drawing all physics volumes and contact points.
 *
 * @param draw if true, physics data will be drawn. Pass falseo to deactivate physics data rendering
 */
void PhysicsManager::drawPhysics( bool draw )
{
	m_physicsWorld->setShowDebugShapes( draw );
	m_physicsWorld->setShowDebugContactPoints( draw );
}


/**
 * @internal 
 * @brief Creates a collision shape based on a triangle mesh.
 * 
 * This method should be used when there is no primitive shape that fits well for a specific mesh
 *
 * @param object Object for which the shape will be created
 */
OgreBulletCollisions::CollisionShape* PhysicsManager::buildTriMeshShape( Graphics::Object3D& object )
{
	// Convert the triangle mesh of the object to a collision shape
	OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter	= new OgreBulletCollisions::StaticMeshToShapeConverter( object.getEntity() );
	OgreBulletCollisions::TriangleMeshCollisionShape *triMeshShape = trimeshConverter->createTrimesh();
	delete trimeshConverter;

	return triMeshShape;
}

/**
 * @internal 
 * @brief Creates a collision for a Box object
 *
 * @param width		Width of the box
 * @param height	Height of the box
 * @param depth		Depth of the box
 */
OgreBulletCollisions::CollisionShape* PhysicsManager::buildBoxShape( float width, float heigh, float depth )
{
	// Obtain box correct size
	Vector size ( width, heigh, depth );
	size /= 2.0f; // bullet expects half box size
	size /= Graphics::Object3D::OGRE_SCALE_CORRECTION; // To correct scale problems between ogre and maya exporter

	// Create the shape
	OgreBulletCollisions::BoxCollisionShape *boxShape = new OgreBulletCollisions::BoxCollisionShape( size );

	return boxShape;
}

/**
 * @internal 
 * @brief Creates a collision for a Plane object
 *
 * @param width		Width of the plane
 * @param height	Height of the plane
 */
OgreBulletCollisions::CollisionShape* PhysicsManager::buildStaticPlaneShape( float width, float heigh )
{
	// Calculate plane normal and distance
	Vector p1, p2, p3;
	float halfWidth		= width / 2.0f;
	float halfHeight	= heigh / 2.0f;
	p1.x = -halfWidth; p1.z = -halfHeight;	p1.y = 0.0f;
	p2.x = halfWidth;  p2.z = -halfHeight;	p2.y = 0.0f;
	p3.x = -halfWidth; p3.z = halfHeight;	p3.y = 0.0f;

	// Edges vectors
	Vector v12( p2 - p1 );
	Vector v13( p3 - p1 );

	// Calculate normal
	Vector normal( v13.crossProduct( v12 ) );
	normal.normalise();
	float	 distance = 0.0f;

	// Create collision shape
	OgreBulletCollisions::StaticPlaneCollisionShape* planeShape = new OgreBulletCollisions::StaticPlaneCollisionShape( normal, distance );

	return planeShape;
}

/**
 * @internal 
 * @brief Creates a collision for a Sphere object
 *
 * @param radius Radius of the collision sphere to be created
 */
OgreBulletCollisions::CollisionShape* PhysicsManager::buildSphereShape( float radius )
{
	// Create the sphere collision shape
	float correctedRadius = radius / Graphics::Object3D::OGRE_SCALE_CORRECTION; // To correct scale problems between ogre and maya exporter
	OgreBulletCollisions::SphereCollisionShape *sphereShape = new OgreBulletCollisions::SphereCollisionShape( correctedRadius );

	return sphereShape;
}

/**
 * @brief Creates a rigid body for the physics object received and assigns it a collision shape
 *
 * @param		object					3D Object for which the rigid body will be created
 * @param		collisionShape	Collision shape that will be use to control the collisions of the object
 * @param		staticBody			If true, the rigid body created will be static. Therefore, it will affect collisions of other
 * physics objects, but it won't move.
 */
OgreBulletDynamics::RigidBody* PhysicsManager::createRigidBody( Graphics::Object3D& object, OgreBulletCollisions::CollisionShape* collisionShape, bool staticBody )
{
	// Create the rigid body
	m_rigidObjectCounter++;
	OgreBulletDynamics::RigidBody* rigidBody = new OgreBulletDynamics::RigidBody( object.getName() + "RigidBody" + Ogre::StringConverter::toString( m_rigidObjectCounter ), 
																																								m_physicsWorld );

	// Attach the collision shape
	if ( staticBody )
	{
		rigidBody->setStaticShape(	collisionShape, 
																DEFAULT_DYNAMIC_BODY_RESTITUTION, 
																DEFAULT_DYNAMIC_BODY_FRICTION, object.getPosition(), object.getOrientation() );
}
	else
	{
		// Note: The position and rotation of the object are stored here (and not as references)
		// because the Ogrebullet lib has a bug, and resets the node position to zero, even when you speficy one...
		// So, I store position and orientation to pass them by value, instead of by reference
		Vector pos = object.getPosition();
		Quaternion orientation = object.getOrientation();

		rigidBody->setShape(	object.getSceneNode(), 
													collisionShape, 
													DEFAULT_DYNAMIC_BODY_RESTITUTION, 
													DEFAULT_DYNAMIC_BODY_FRICTION, 
													DEFAULT_DYNAMIC_BODY_MASS,
													pos,
													orientation );

	}

	return rigidBody;
}
} // namespace Physics
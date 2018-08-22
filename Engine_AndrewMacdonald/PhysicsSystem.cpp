//PhysicsSystem.cpp
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(void)
{
    //Create Box2D World
    _gravity = b2Vec2( 0.0f, -9.81f );
    _world = new b2World( _gravity );

    timeStep = 1.0f / 60.0f;      
    velocityIterations = 8;
    positionIterations = 3;

    componentMask = Position::getMask() | RigidBody::getMask();

    //Initialize timer
    _lastWorldStepTime = system_clock::now();
}

PhysicsSystem::~PhysicsSystem(void)
{
    //Destroy Box2D world
    delete _world;
}

void PhysicsSystem::update( void )
{
    float physicsScale = Engine::instance().physicsScale;

    //Determine if it's time to update the Box2D world
    duration< float > delta = system_clock::now() - _lastWorldStepTime;
    if( delta.count() > timeStep )
    {
        //Update timer
        _lastWorldStepTime = system_clock::now();
        
        //Update Box2D world
        _world->Step( timeStep, velocityIterations, positionIterations );
    }

    //Loop through all entities
    for( Entity& entity : Entity::getEntityList()  )
    {
        if( ( entity.getComponentMask() & Position::getMask() ) == Position::getMask() )
        {
            Position& position = entity.getComponent< Position >();

            //Circle Collider
            if( ( entity.getComponentMask() & CircleCollider::getMask() ) == CircleCollider::getMask() )
            {
                if( _bodies.count( entity.getID() ) < 1 )
                {
                    b2Body* body = createBody( entity.getID(), position, physicsScale );
                    body->SetType( b2BodyType::b2_staticBody );
                }

                b2Body* body = _bodies[ entity.getID() ];

                //Check if the body has a collider shape (fixture)
                if( body->GetFixtureList() == nullptr )
                {
                    b2CircleShape shape = b2CircleShape();
                    CircleCollider& collider = entity.getComponent< CircleCollider >();
                    
                    shape.m_radius = collider.radius / physicsScale;
                    body->CreateFixture( &shape, 1.0f );
                }
            }
            //Rectangle Collider
            else if( ( entity.getComponentMask() & RectangleCollider::getMask() ) == RectangleCollider::getMask() )
            {
                if( _bodies.count( entity.getID() ) < 1 )
                {  
                    b2Body* body = createBody( entity.getID(), position, physicsScale );
                    body->SetType( b2BodyType::b2_staticBody );
                }

                b2Body* body = _bodies[ entity.getID() ];

                //Check if the body has a collider shape (fixture)
                if( body->GetFixtureList() == nullptr )
                {
                    b2PolygonShape shape;
                    RectangleCollider& collider = entity.getComponent< RectangleCollider >();

                    //Box2D uses "half-extent" sizes
                    shape.SetAsBox( collider.width / 2.0f / physicsScale, collider.height / 2.0f / physicsScale );

                    body->CreateFixture( &shape, 0.0f );
                }
            }
   
            //Rigidbody
            if( ( entity.getComponentMask() & RigidBody::getMask() ) == RigidBody::getMask() )
            { 
                if( _bodies.count( entity.getID() ) < 1 )
                {  
                    b2Body* body = createBody( entity.getID(), position, physicsScale );
                }
 
                b2Body* body = _bodies[ entity.getID() ];
                if( body->GetType() != b2BodyType::b2_dynamicBody )
                {
                    body->SetType( b2BodyType::b2_dynamicBody );
                }

                //Update the Position Component based on the Physics Engine
                b2Vec2 bodyPos = _bodies[ entity.getID() ]->GetPosition();
                position.x = bodyPos.x * physicsScale;
                position.y = bodyPos.y * physicsScale;
            }
        }
    }
}

b2Body* PhysicsSystem::createBody( size_t entityID, Position& position, float physicsScale )
{
    //Create a new b2Body
    b2BodyDef bodyDef;
    bodyDef.position.x = position.x / physicsScale;
    bodyDef.position.y = position.y / physicsScale;

    //Add the body to the Box2D world
    b2Body* body = _world->CreateBody( &bodyDef );
    _bodies[ entityID ] = body;
    return body;
}
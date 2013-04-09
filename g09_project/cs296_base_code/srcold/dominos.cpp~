/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
  /*    
    //Top horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }*/
/*
    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
 */     
    //Another horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(11.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      b2FixtureDef pltfd;
      pltfd.friction=0.9f;
      pltfd.shape=&shape;
      bd.position.Set(-4.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 23.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {	b2FixtureDef *bobf = new b2FixtureDef;
	bobf->restitution=0.3f;
	bobf->density=2.0f;
	b2PolygonShape shape;
	shape.SetAsBox(.25f, .25f);
	bobf->shape=&shape;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-45.0f, 38.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(bobf);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 35.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    //The train of small spheres
    {
      b2Body* spherebody1;
	
      b2CircleShape circle;
      circle.m_radius = 0.75;
	
      

      b2FixtureDef ballfd2;
      ballfd2.shape = &circle;
      ballfd2.density = 4.0f;
      ballfd2.friction = 0.0f;
      ballfd2.restitution =0.0f;
	/////////////////////////////////////////////////
	//pipe
	{


	b2BodyDef *bd = new b2BodyDef;
      //bd->type = b2_dynamicBody;
      bd->position.Set(-33.5f,28.85f);
      bd->fixedRotation = true;
	
      
      
	b2FixtureDef *fd2a = new b2FixtureDef;
      fd2a->density = 0.0;
      fd2a->friction = 0.0;
      fd2a->restitution = 1.f;
      fd2a->shape = new b2PolygonShape;
      b2PolygonShape bs2a;
      bs2a.SetAsBox(0.1,1.5, b2Vec2(-.85f,0.75f), 0);
      fd2a->shape = &bs2a;
      b2FixtureDef *fd3a = new b2FixtureDef;
      fd3a->density = 0.0;
      fd3a->friction = 0.0;
      fd3a->restitution = 1.f;
      fd3a->shape = new b2PolygonShape;
      b2PolygonShape bs3a;	
      bs3a.SetAsBox(0.1,1.5, b2Vec2(.85f,0.75f), 0);
      fd3a->shape = &bs3a;
      b2Body* box1 = m_world->CreateBody(bd);
      b2Body* box2 = m_world->CreateBody(bd);
      box1->CreateFixture(fd2a);
      box2->CreateFixture(fd3a);	
	}
	
	
	
	
	
	
	
	
	/////////////////////////////////////////////
	//bottom-most ball
	{
	  b2FixtureDef ballfd1;
      	  ballfd1.shape = &circle;
      	  ballfd1.density = 4.0f;
      	  ballfd1.friction = 0.0f;
	  ballfd1.restitution =0.3f;
      
	  b2BodyDef ballbd1;
	  ballbd1.type = b2_dynamicBody;
	  ballbd1.position.Set(-33.5f , 26.6f);
	  spherebody1 = m_world->CreateBody(&ballbd1);
	  spherebody1->CreateFixture(&ballfd1);
	}

	//beech ki
	{
	  b2FixtureDef ballfd1;
      	  ballfd1.shape = &circle;
      	  ballfd1.density = 4.0f;
      	  ballfd1.friction = 0.4f;
	  ballfd1.restitution =0.0f;
      
	  b2BodyDef ballbd1;
	  ballbd1.type = b2_dynamicBody;
	  ballbd1.position.Set(-33.5f, 28.1f);
	  spherebody1 = m_world->CreateBody(&ballbd1);
	  spherebody1->CreateFixture(&ballfd1);
	}	
	
	//sabse upar wali
	{
	  b2FixtureDef ballfd1;
      	  ballfd1.shape = &circle;
      	  ballfd1.density = 4.0f;
      	  ballfd1.friction = 0.0f;
	  ballfd1.restitution =0.0f;
      
	  b2BodyDef ballbd1;
	  ballbd1.type = b2_dynamicBody;
	  ballbd1.position.Set(-33.5f , 29.6f);
	  spherebody1 = m_world->CreateBody(&ballbd1);
	  spherebody1->CreateFixture(&ballfd1);
	}
	
	//uss side wali balls
	for (int i=0; i<3 ; i++)
	{b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(3.1f, 20.95f+6*i);
	  spherebody1 = m_world->CreateBody(&ballbd);
	  spherebody1->CreateFixture(&ballfd2);
	}
	
    }

    //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,17);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 5.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.0f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.2f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 5.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.1,1.3, b2Vec2(1.9f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 5.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.1,1.3, b2Vec2(-1.9f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      /*//The bar
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);*/
      
      
       //The open box
      b2FixtureDef *fd1a = new b2FixtureDef;
      fd1a->density = 5.0;
      fd1a->friction = 0.5;
      fd1a->restitution = 0.f;
      fd1a->shape = new b2PolygonShape;
      b2PolygonShape bs1a;
      bs1a.SetAsBox(2,0.2, b2Vec2(0.f,-1.2f), 0);
      fd1a->shape = &bs1a;
      b2FixtureDef *fd2a = new b2FixtureDef;
      fd2a->density = 5.0;
      fd2a->friction = 0.5;
      fd2a->restitution = 1.f;
      fd2a->shape = new b2PolygonShape;
      b2PolygonShape bs2a;
      bs2a.SetAsBox(0.1,1.3, b2Vec2(1.9f,0.f), 0);
      fd2a->shape = &bs2a;
      b2FixtureDef *fd3a = new b2FixtureDef;
      fd3a->density = 5.0;
      fd3a->friction = 0.5;
      fd3a->restitution = 0.f;
      fd3a->shape = new b2PolygonShape;
      b2PolygonShape bs3a;	
      bs3a.SetAsBox(0.1,1.3, b2Vec2(-1.9f,0.f), 0);
      fd3a->shape = &bs3a;
      
      b2BodyDef *bd2 = new b2BodyDef;
      bd2->type = b2_dynamicBody;
      bd2->position.Set(2,17);
      bd2->fixedRotation = true;
       
      b2Body* box2 = m_world->CreateBody(bd2);
      box2->CreateFixture(fd1a);
      box2->CreateFixture(fd2a);
      box2->CreateFixture(fd3a);
      

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(2, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 37); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(2, 37); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }



//static platform	
	{
      b2PolygonShape shape1;
      shape1.SetAsBox(0.4f, 0.2f);
	
      b2BodyDef bd1;
      bd1.position.Set(3.0f, 40.0f);
      //bd.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;
      body1->CreateFixture(fd1);
	

	
      b2PolygonShape shape2;
      shape2.SetAsBox(0.4f, 0.2f);
	
      b2BodyDef bd2;
      bd2.position.Set(3.0f, 26.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 24.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body2->CreateFixture(fd2);
	

	
      b2PolygonShape shape3;
      shape3.SetAsBox(0.4f, 0.2f);
	
      b2BodyDef bd3;
      bd3.position.Set(3.0f, 32.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 24.0f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape3;
      body3->CreateFixture(fd3);
	
	

	
      b2PolygonShape shape5;
      shape5.SetAsBox(0.4f, 0.2f);
	
      b2BodyDef bd5;
      bd5.position.Set(3.0f, 20.0f);
      bd5.type = b2_dynamicBody;
      b2Body* body5 = m_world->CreateBody(&bd5);
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 24.0f;
      fd5->shape = new b2PolygonShape;
      fd5->shape = &shape5;
      body5->CreateFixture(fd5);
	

	 b2PrismaticJointDef jd1,jd2,jd3,jd4;
      jd4.bodyA= body1;
      jd4.bodyB= body5;
	jd4.localAnchorA.Set(0,0);
	jd4.localAnchorB.Set(0,0);
	jd4.localAxisA.Set(0,1);
	jd4.enableLimit = true;
	jd4.lowerTranslation=-20.0f;
	jd4.upperTranslation=40.0f;
	(b2PrismaticJoint*)m_world->CreateJoint( &jd4 );	

	jd3.bodyA= body1;
      jd3.bodyB= body2;
	jd3.localAnchorA.Set(0,0);
	jd3.localAnchorB.Set(0,0);
	jd3.localAxisA.Set(0,1);
	jd3.enableLimit = true;
	jd3.lowerTranslation=-14.0f;
	jd3.upperTranslation=40.0f;
	(b2PrismaticJoint*)m_world->CreateJoint( &jd3 );	

jd2.bodyA= body1;
      jd2.bodyB= body3;
	jd2.localAnchorA.Set(0,0);
	jd2.localAnchorB.Set(0,0);
	jd2.localAxisA.Set(0,1);
	jd2.enableLimit = true;
	jd2.lowerTranslation=-8.0f;
	jd2.upperTranslation=40.0f;
	(b2PrismaticJoint*)m_world->CreateJoint( &jd2 );	

      //jd2.Initialize(body1, body3, anchor);
     // jd3.Initialize(body1, body4, anchor);
      //jd4.Initialize(body1, body5, anchor);
	
		
 //     m_world->CreateJoint(&jd1);
   //   m_world->CreateJoint(&jd4);
    //  m_world->CreateJoint(&jd3);
      //m_world->CreateJoint(&jd2);

   }
        	


	/*
    //The revolving horizontal platform 1
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(5.5f, 19.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(5.5f, 19.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);
      

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(5.5f, 19.0f);
      jd.Initialize(body, body2, anchor);
      m_world->CreateJoint(&jd);
    }
    */
    /*
    //Revolving Platform 2
     {
      b2PolygonShape shape;
      shape.SetAsBox(4.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(10.5f, 17.5f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(10.5f, 17.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);
      

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(10.5f, 17.5f);
      jd.Initialize(body, body2, anchor);
      m_world->CreateJoint(&jd);
    }
    
    //Revolving Platform 3
   
    {
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(2.5,0);
      vertices[1].Set(-2.5,0);
      vertices[2].Set(0,-0.1);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(7.5f, 21.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
    }
   */
   /* //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }*/


    //The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(10.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(10.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(10.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction =0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(2.0f, 2.9f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
      }
      {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(18.0f,2.9f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
      }
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

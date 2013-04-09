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
#include <iostream>
using namespace std;

#include "dominos.hpp"
#include <math.h>






//!Namespace for the project is CS296.

namespace cs296
{
   //!Elements in the Box2D Simulation World
  extern float globalx;
  extern float globaly;
  dominos_t::dominos_t()
  {
  
     
	   /*!<ul><li><b>Ground</b> is the static body in this simulation world. It acts as a base for all the dynamics involved.</li>
	   <li>There is a static <b>platform</b> through which the balls pass and fall into the container attached to the pulley when hit by the pendulum.</li>
	   <li>The <b>pendulum</b> is a dynamic body that knocks off the ball into the container one by one.</li>
	   <li>The joint that joins the pendulum bob with the static roof point is a <b>revolute joint</b>.</li>
	   <li>The <b>cylindrical pipe</b> in which the balls are kept initially is a static body.
	   <li>The <b>balls</b> to be knocked off are filled in the cylindrical pipe.</li>
	   <li>The Pulley System consists of two <b>open boxes</b> as containers on both sides.</li>
	   <li>The <b>pulley joints</b> are of the type b2Joint.</li>
	   <li>The <b>balls</b> on the other side are placed on sequential <b>dynamic platforms</b> which all are respectively joined to the uppermost static platform through <b>prismatic joints</b>. Prismatic joints allow movement of the parts joined along a specific axis only.</li>
	   <li>There is a pair of <b>scissors</b> that cuts the string going over the pulley connecting the two open boxes. Technically, there is a <b>contact listener</b> that <b>destroys the pulley joints</b> when there is a contact made to theses scissors.(The scissors itself is a static body)</li>
	   <li>There are two <b>see-saw systems</b> on the ground. These involve the simple <b>b2Joints</b> between the plank and the triangular wedge.</li>
	   <li>The see saw system on the right maintains balance with the help of two balls. When the second box filled with the balls falls on one end,it is no longer in equilibrium. The <b>ball on the right arm</b> goes to the respective candidate's block(equal to the number of balls).</li>
	   <li>The ball on the left arm opens up a <b>curtain</b> declaring the result.The curtain is a dynamic body connected to a <b> Prismatic joint</b> allowing movement along the x axis only. </li>
	   <li>The <b>candidate blocks</b> on the left are also attached to the <b>prismatic joints</b> allowing movement only along x axis.</li>
	   
	   </ul>*/
	   
	  //Ground 
	    {
	      b2Body* b1;
	      b2EdgeShape shape;
	      shape.Set(b2Vec2(-90.0f, -5.0f), b2Vec2(90.0f, -5.0f));
	
	      b2BodyDef bd;
	      b1 = m_world->CreateBody(&bd);
	      b1->CreateFixture(&shape, 0.0f);
	    }

	 //Platform
	    {
	      	b2PolygonShape shape;
	      	shape.SetAsBox(11.0f, 0.25f);
	      	b2BodyDef bd2;
	      	bd2.position.Set(-24.0f, 26.0f);
	      	b2Body* body = m_world->CreateBody(&bd2);
	      	b2FixtureDef *fd2 = new b2FixtureDef;
	      	fd2->density = 1.f;
	      	fd2->shape = new b2PolygonShape;
	      	fd2->shape = &shape;
	      	body->CreateFixture(fd2);
	    }
	  
         //holder
	    {
	      	b2PolygonShape shape;
	      	shape.SetAsBox(0.01f, 0.01f);
	      	b2BodyDef bd2;
	      	bd2.position.Set(-33.75f, 26.26f);
	      	b2Body* body = m_world->CreateBody(&bd2);
	      	b2FixtureDef *fd2 = new b2FixtureDef;
	      	fd2->density = 1.f;
	      	fd2->shape = new b2PolygonShape;
	      	fd2->shape = &shape;
	      	body->CreateFixture(fd2);
	    }
    	//Pendulum
     	{
     
           {
		b2Body* b2;
		b2PolygonShape shape;
		shape.SetAsBox(0.25f, 1.5f);
		  
		b2BodyDef bd;
		bd.position.Set(-37.0f, 23.0f);
		b2 = m_world->CreateBody(&bd);
		b2->CreateFixture(&shape, 10.0f);
	      	
		b2Body* b4;
		b2FixtureDef *bobf = new b2FixtureDef;
		bobf->restitution=0.0f;
		bobf->density=2.0f;
		shape.SetAsBox(.25f, .25f);
		bobf->shape=&shape;
		b2BodyDef bd2;
		bd2.type = b2_dynamicBody;
		bd2.position.Set(-45.0f, 38.0f);
		b4 = m_world->CreateBody(&bd2);
		b4->CreateFixture(bobf);
	
	  
	       	b2RevoluteJointDef jd;
	       	b2Vec2 anchor;
	       	anchor.Set(-37.0f, 35.0f);
	       	jd.Initialize(b2, b4, anchor);
	       	m_world->CreateJoint(&jd);
      	   }
      
    	}
      
    	//the balls on the left side
    	{
	      	b2Body* spherebody1;
	
	      	b2CircleShape circle;
	      	circle.m_radius = 0.75;
		b2FixtureDef ballfd2;
	      	ballfd2.shape = &circle;
	      	ballfd2.density = 4.0f;
	      	ballfd2.friction = 0.0f;
	      	ballfd2.restitution =0.6f;

	
	//pipe
	{
	      	b2PolygonShape shape1;
	      	shape1.SetAsBox(.1f, 2.25f);
	
	      	b2BodyDef bd1;
	      	bd1.position.Set(-34.35f, 30.1f);
	      	b2Body* body1 = m_world->CreateBody(&bd1);
	      	b2FixtureDef *fd1 = new b2FixtureDef;
	      	fd1->density = 0.f;
	      	fd1->shape = new b2PolygonShape;
	      	fd1->shape = &shape1;
	      	body1->CreateFixture(fd1);
	}
	
	
	{
	      	b2PolygonShape shape1;
	      	shape1.SetAsBox(.1f, 2.25f);
	      	b2BodyDef bd1;
	      	bd1.position.Set(-32.65f, 30.1f);
	      	b2Body* body1 = m_world->CreateBody(&bd1);
	      	b2FixtureDef *fd1 = new b2FixtureDef;
	      	fd1->density = 0.f;
	      	fd1->shape = new b2PolygonShape;
	      	fd1->shape = &shape1;
	      	body1->CreateFixture(fd1);
	}

	//bottom-most ball
	{
	      	b2FixtureDef ballfd1;
	      	ballfd1.shape = &circle;
	      	ballfd1.density = 4.0f;
	      	ballfd1.friction = 0.0f;
	      	ballfd1.restitution =0.3f;
	      	b2BodyDef ballbd1;
	      	ballbd1.type = b2_dynamicBody;
	      	ballbd1.position.Set(-33.5f , 27.0f);
	      	spherebody1 = m_world->CreateBody(&ballbd1);
	      	spherebody1->CreateFixture(&ballfd1);
	  
	}

	//second ball
	{
		  b2FixtureDef ballfd1;
	      	  ballfd1.shape = &circle;
	      	  ballfd1.density = 4.0f;
	      	  ballfd1.friction = 0.0f;
		  ballfd1.restitution =0.0f;
	      
		  b2BodyDef ballbd1;
		  ballbd1.type = b2_dynamicBody;
		  ballbd1.position.Set(-33.5f, 28.5f);
		  spherebody1 = m_world->CreateBody(&ballbd1);
		  spherebody1->SetLinearDamping(.03);
		  spherebody1->SetLinearDamping(globalx);
		  std::cout<<globalx<<std::endl;
		  spherebody1->CreateFixture(&ballfd1);
	}	
	
	//third ball
	{
		  b2FixtureDef ballfd1;
	      	  ballfd1.shape = &circle;
	      	  ballfd1.density = 4.0f;
	      	  ballfd1.friction = 0.0f;
		  ballfd1.restitution =0.0f;
	      
		  b2BodyDef ballbd1;
		  ballbd1.type = b2_dynamicBody;
		  ballbd1.position.Set(-33.5f , 30.0f);
		  spherebody1 = m_world->CreateBody(&ballbd1);
		  spherebody1->SetLinearDamping(.06);
		  spherebody1->SetLinearDamping(globaly);
		  std::cout<<globalx<<std::endl;
		  spherebody1->CreateFixture(&ballfd1);
	}
	
	//fourth ball
	{
		  b2FixtureDef ballfd1;
	      	  ballfd1.shape = &circle;
	      	  ballfd1.density = 4.0f;
	      	  ballfd1.friction = 0.0f;
		  ballfd1.restitution =0.0f;
	      
		  b2BodyDef ballbd1;
		  ballbd1.type = b2_dynamicBody;
		  ballbd1.position.Set(-33.5f , 31.5f);
		  spherebody1 = m_world->CreateBody(&ballbd1);
		  spherebody1->CreateFixture(&ballfd1);
	}
	
	//the balls on the right side
	for (int i=0; i<3 ; i++)
	{
		  b2BodyDef ballbd;
		  ballbd.type = b2_dynamicBody;
		  ballbd.position.Set(3.1f, 20.95f+6*i);
		  spherebody1 = m_world->CreateBody(&ballbd);
		  spherebody1->CreateFixture(&ballfd2);
	}
}

      //The pulley system
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,17);
      bd->fixedRotation = true;
      
      //The open box 1
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
      bs2.SetAsBox(0.2,1.3, b2Vec2(1.9f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 5.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,1.3, b2Vec2(-1.9f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      
      //The open box 2
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
      bs2a.SetAsBox(0.2,1.3, b2Vec2(1.9f,0.f), 0);
      fd2a->shape = &bs2a;
      b2FixtureDef *fd3a = new b2FixtureDef;
      fd3a->density = 5.0;
      fd3a->friction = 0.5;
      fd3a->restitution = 0.f;
      fd3a->shape = new b2PolygonShape;
      b2PolygonShape bs3a;	
      bs3a.SetAsBox(0.2,1.3, b2Vec2(-1.9f,0.f), 0);
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
      b2Vec2 worldAnchorOnBody1(-10, 15); 
      b2Vec2 worldAnchorOnBody2(2, 15);
      b2Vec2 worldAnchorGround1(-10, 37); 
      b2Vec2 worldAnchorGround2(2, 37); 
      float32 ratio = 1.0f; 
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      b2Joint* mj=m_world->CreateJoint(myjoint);
      
     
      //first circle
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = .5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.05f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;
      b2BodyDef ballbd;
      ballbd.position.Set(-10.0f,37.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
        
      //second circle	
      b2Body* sbody1;
      b2CircleShape circle1;
      circle1.m_radius = .5;
	
      b2FixtureDef ballfd1;
      ballfd1.shape = &circle1;
      ballfd1.density = 0.05f;
      ballfd1.friction = 0.0f;
      ballfd1.restitution = 1.0f;
      b2BodyDef ballbd1;
      ballbd1.position.Set(2.0f,37.0f);
      sbody1 = m_world->CreateBody(&ballbd1);
      sbody1->CreateFixture(&ballfd1);	
    	

	//new Prismatic joints
	b2PrismaticJointDef jd1,jd2;
	jd1.bodyA = box1;
	jd1.bodyB = sbody;
	jd1.localAnchorA.Set(0,0);
	jd1.localAnchorB.Set(0,0);
	jd1.localAxisA.Set(0,1);
	b2Joint* j1 = (b2PrismaticJoint*)m_world->CreateJoint( &jd1 );
	
	jd2.bodyA = box2;
	jd2.bodyB = sbody1;
	jd2.localAnchorA.Set(0,0);
	jd2.localAnchorB.Set(0,0);
	jd2.localAxisA.Set(0,1);
	b2Joint* j2 = (b2PrismaticJoint*)m_world->CreateJoint( &jd2 );
	
	
	//Scissors	
	Sci scissors(m_world,mj, j1, j2);

        	
	{
	      //shape 1
	
	      b2PolygonShape shape1;
	      shape1.SetAsBox(0.4f, 0.2f);
	
	      b2BodyDef bd1;
	      bd1.position.Set(3.0f, 40.0f);
	      b2Body* body1 = m_world->CreateBody(&bd1);
	      b2FixtureDef *fd1 = new b2FixtureDef;
	      fd1->density = 1.f;
	      fd1->shape = new b2PolygonShape;
	      fd1->shape = &shape1;
	      body1->CreateFixture(fd1);
	

	      //shape 2
	      b2PolygonShape shape2;
	      shape2.SetAsBox(0.4f, 0.01f);
	
	      b2BodyDef bd2;
	      bd2.position.Set(3.0f, 26.0f);
	      bd2.type = b2_dynamicBody;
	      b2Body* body2 = m_world->CreateBody(&bd2);
	      b2FixtureDef *fd2 = new b2FixtureDef;
	      fd2->density = 24.0f;
	      fd2->shape = new b2PolygonShape;
	      fd2->shape = &shape2;
	      body2->CreateFixture(fd2);
	
	
	      //shape 3
	      b2PolygonShape shape3;
	      shape3.SetAsBox(0.4f, 0.01f);
	
	      b2BodyDef bd3;
	      bd3.position.Set(3.0f, 32.0f);
	      bd3.type = b2_dynamicBody;
	      b2Body* body3 = m_world->CreateBody(&bd3);
	      b2FixtureDef *fd3 = new b2FixtureDef;
	      fd3->density = 24.0f;
	      fd3->shape = new b2PolygonShape;
	      fd3->shape = &shape3;
	      body3->CreateFixture(fd3);
	      
	
	
	      //shape 4
	      b2PolygonShape shape4;
	      shape4.SetAsBox(0.4f, 0.2f);
	
	      b2BodyDef bd4;
	      bd4.position.Set(3.0f, 20.0f);
	      bd4.type = b2_dynamicBody;
	      b2Body* body4 = m_world->CreateBody(&bd4);
	      b2FixtureDef *fd4 = new b2FixtureDef;
	      fd4->density = 24.0f;
	      fd4->shape = new b2PolygonShape;
	      fd4->shape = &shape4;
	      body4->CreateFixture(fd4);
	
	
        //Prismatic joints
	b2PrismaticJointDef jd1,jd2,jd3,jd4;
        jd4.bodyA= body1;
        jd4.bodyB= body4;
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
  }
        	



    //The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0.0);
      vertices[1].Set(1,0.0);
      vertices[2].Set(0,3.0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(10.0f, -5.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(10.0f, -2.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(10.0f, -3.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
     
      //ball1 on the see saw
      {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.00;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.05f;
      ballfd.friction =0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;

      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(3.0f, -1.1f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
      }
      
      //ball2 on the see saw 
      {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.00;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.05f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(17.0f,-1.1f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
      }
  }

    {
      //right wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1.25,0.0);
      vertices[1].Set(1.25,0.0);
      vertices[2].Set(0,2.0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(-23.5f, -5.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.01f);
      b2BodyDef bd2;
      bd2.position.Set(-23.0f, -3.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-23.5f, -3.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
     
    }
    
    // curtain 
    {
      b2PolygonShape shape1;
      shape1.SetAsBox(2.0f, 0.1f);
	
      b2BodyDef bd1;
      bd1.position.Set(-33.0f, 5.0f);
      b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;
	
      //actual curtain	
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 5.0f);
	
      b2BodyDef bd2;
      bd2.position.Set(-33.0f, 5.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body2->CreateFixture(fd2);
      
        b2PrismaticJointDef jd3;
        jd3.bodyA= body1;
        jd3.bodyB= body2;
	jd3.localAnchorA.Set(0,0);
	jd3.localAnchorB.Set(0,0);
	jd3.localAxisA.Set(1,0);
	jd3.enableLimit = false;
	jd3.lowerTranslation=-2.0f;
	jd3.upperTranslation=10.0f;
	(b2PrismaticJoint*)m_world->CreateJoint( &jd3 );
	}
	
	//candidates
	{
	      b2PolygonShape shape1;
	      shape1.SetAsBox(1.0f, 0.10f);
	
	      b2BodyDef bd1;
	      bd1.position.Set(38.0f, 20.6f);
	      b2Body* body1 = m_world->CreateBody(&bd1);
	      b2FixtureDef *fd1 = new b2FixtureDef;
	      fd1->density = 1.f;
	      fd1->shape = new b2PolygonShape;
	      fd1->shape = &shape1;
	      body1->CreateFixture(fd1);
	

	
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, .50f);
	
      b2BodyDef bd2;
      bd2.position.Set(38.0f, 20.6f);
      bd2.type = b2_dynamicBody;
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body2->CreateFixture(fd2);
      b2PrismaticJointDef jd3;
      jd3.bodyA= body1;
      jd3.bodyB= body2;
      jd3.localAnchorA.Set(0,0);
      jd3.localAnchorB.Set(0,0);
      jd3.localAxisA.Set(1,0);
      jd3.enableLimit = false;
      jd3.lowerTranslation=0.0f;
      jd3.upperTranslation=0.0f;
      (b2PrismaticJoint*)m_world->CreateJoint( &jd3 );
      }
	
	
	{
     b2PolygonShape shape1;
      shape1.SetAsBox(1.0f, 0.1f);
	
      b2BodyDef bd1;
      bd1.position.Set(38.0f, 18.9f);
      //bd1.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;
      body1->CreateFixture(fd1);
	

	
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, .50f);
	
      b2BodyDef bd2;
      bd2.position.Set(38.0f, 18.9f);
      bd2.type = b2_dynamicBody;
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.0f;
      // fd2->restitution = 0.2f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body2->CreateFixture(fd2);
      b2PrismaticJointDef jd3;
      jd3.bodyA= body1;
      jd3.bodyB= body2;
      jd3.localAnchorA.Set(0,0);
      jd3.localAnchorB.Set(0,0);
      jd3.localAxisA.Set(1,0);
      jd3.enableLimit = false;
      jd3.lowerTranslation=0.0f;
      jd3.upperTranslation=0.0f;
      (b2PrismaticJoint*)m_world->CreateJoint( &jd3 );
      }
	
	{
     b2PolygonShape shape1;
      shape1.SetAsBox(1.0f, 0.1f);
	
      b2BodyDef bd1;
      bd1.position.Set(38.0f, 17.2f);
      //bd1.type = b2_dynamicBody;
      b2Body* body1 = m_world->CreateBody(&bd1);
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.f;
      fd1->shape = new b2PolygonShape;
      fd1->shape = &shape1;
      body1->CreateFixture(fd1);
	

	
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, .50f);
	
      b2BodyDef bd2;
      bd2.position.Set(38.0f, 17.2f);
      bd2.type = b2_dynamicBody;
      b2Body* body2 = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 0.0f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body2->CreateFixture(fd2);
      b2PrismaticJointDef jd3;
      jd3.bodyA= body1;
      jd3.bodyB= body2;
      jd3.localAnchorA.Set(0,0);
      jd3.localAnchorB.Set(0,0);
      jd3.localAxisA.Set(1,0);
      jd3.enableLimit = false;
      jd3.lowerTranslation=0.0f;
      jd3.upperTranslation=0.0f;
      (b2PrismaticJoint*)m_world->CreateJoint( &jd3 );
	}
	
    //hitting platform	
	{
	      b2PolygonShape shape1;
	      shape1.SetAsBox(1.0f, 0.1f);
	
	      b2BodyDef bd1;
	      bd1.position.Set(13.4f, 0.9f);
	      bd1.angle =  -45*180/3.14;
	      b2Body* body1 = m_world->CreateBody(&bd1);
	      b2FixtureDef *fd1 = new b2FixtureDef;
	      fd1->density = 1.f;
	      fd1->restitution = 1.5f;
	     
	      
	      fd1->shape = new b2PolygonShape;
	      fd1->shape = &shape1;
	      body1->CreateFixture(fd1);
        }    
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

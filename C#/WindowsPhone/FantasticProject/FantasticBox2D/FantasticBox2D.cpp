// FantasticBox2D.cpp
#include "pch.h"
#include "FantasticBox2D.h"

using namespace FantasticBox2D;
using namespace Platform;
using namespace std;

B2FixturePRT^ B2BodyPRT::CreateFixture(B2PolygonShapePRT^ shape, float32 density)
{
	return ref new B2FixturePRT(this->body->CreateFixture(shape->GetPolygonShape(), density));
}

B2FixturePRT^ B2BodyPRT::CreateFixture(B2FixtureDefPRT^ fixtureDef)
{
	return ref new B2FixturePRT(this->body->CreateFixture(fixtureDef->GetFixtureDef()));
}

B2WorldPRT::B2WorldPRT(B2Vec2PRT^ gravity, bool doSleep)
{
	// create a box2d world
	world = new b2World(gravity->GetVec2(), doSleep);
}

B2WorldPRT::~B2WorldPRT()
{
	if (this->world != NULL)
		delete this->world;
}

B2BodyPRT^ B2WorldPRT::CreateBody(B2BodyDefPRT^ bodyDef)
{
	return ref new B2BodyPRT(this->world->CreateBody(bodyDef->GetBodyDef()));
}

void B2WorldPRT::Step(float32 timeStep, int32 velocityIterations, int32 positionIterations)
{
	this->world->Step(timeStep, velocityIterations, positionIterations);
}

void B2WorldPRT::CreateTestWorld()
{
	b2Vec2 gravity(0.0f, -10.0f);
	bool doSleep = true;
	b2World world(gravity, doSleep);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	for (int32 i = 0; i < 60; ++i)
	{
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		wchar_t buffer[50];
		memset(buffer,0,50);
		swprintf(buffer, 50, L"%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		OutputDebugString(buffer);
	}
}


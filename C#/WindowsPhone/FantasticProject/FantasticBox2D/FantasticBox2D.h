#pragma once

#include "Box2D\Box2D.h"

namespace FantasticBox2D
{
	public ref class B2PolygonShapePRT sealed
	{
	public:
		B2PolygonShapePRT() { this->polygonShape = new b2PolygonShape(); }
		virtual ~B2PolygonShapePRT() { if (this->polygonShape != NULL) delete this->polygonShape; }
	internal:
		B2PolygonShapePRT(b2PolygonShape* polygonShape) : polygonShape(polygonShape)
		{
		}
	public:
		void SetAsBox(float hx, float hy)
		{
			this->polygonShape->SetAsBox(hx, hy);
		}
	internal:
		b2PolygonShape* GetPolygonShape() { return this->polygonShape; }
	private:
		b2PolygonShape* polygonShape;
	};

	public enum class B2BodyTypePRT
	{
		B2_StaticBody = 0,
		B2_KinematicBody,
		B2_DynamicBody

	};
	
	public ref class B2Vec2PRT sealed
	{
	public:
		B2Vec2PRT(float x, float y)
		{
			this->vec2 = new b2Vec2(x, y);
		}
		virtual ~B2Vec2PRT() { if (this->vec2 != NULL) delete vec2; }
	internal:
		B2Vec2PRT(b2Vec2& vec2) : vec2(&vec2)
		{}
	public: 
		property float X
		{
			float get() { return this->vec2->x; }
			void set(float value)
            {
				this->vec2->x = value;
            }
		}
		property float Y
		{
			float get() { return this->vec2->y; }
			void set(float value)
            {
				this->vec2->y = value;
            }
		}
	public:
		void Set(float x, float y)
		{
			this->vec2->x = x;
			this->vec2->y = y;
		}
	internal:
		b2Vec2& GetVec2() { return *(this->vec2); }
	private:
		b2Vec2* vec2;
	};

	public ref class B2BodyDefPRT sealed
	{
	public:
		B2BodyDefPRT() { this->bodyDef = new b2BodyDef(); }
		virtual ~B2BodyDefPRT() { if(this->bodyDef != NULL) delete this->bodyDef; }
	public:
		property B2Vec2PRT^ Position
		{
			B2Vec2PRT^ get() { return ref new B2Vec2PRT(this->bodyDef->position); }
			void set(B2Vec2PRT^ pos)
			{
				this->bodyDef->position.Set(pos->X, pos->Y);
			}
		}
		property B2BodyTypePRT Type
		{
			B2BodyTypePRT get() { return (B2BodyTypePRT)this->bodyDef->type; }
			void set(B2BodyTypePRT type)
			{
				this->bodyDef->type = (b2BodyType) type;
			}
		}
		property float32 Angle
		{
			float32 get() { return this->bodyDef->angle; }
			void set(float32 angle)
			{
				this->bodyDef->angle = angle;
			}
		}
	internal:
		b2BodyDef* GetBodyDef() { return this->bodyDef; }
	private:
		b2BodyDef* bodyDef;
	};

	public ref class B2FixturePRT sealed
	{
	internal:
		B2FixturePRT(b2Fixture* fixtureDef) : fixtureDef(fixtureDef) {}
		b2Fixture* GetFixtureDef() { return this->fixtureDef; }
	private:
		b2Fixture* fixtureDef;
	};

	public ref class B2FixtureDefPRT sealed
	{
	public:
		B2FixtureDefPRT() { this->fixtureDef = new b2FixtureDef(); };
		virtual ~B2FixtureDefPRT() { if(this->fixtureDef != NULL) delete this->fixtureDef; }
	public:
		property B2PolygonShapePRT^ Shape
		{
			B2PolygonShapePRT^ get() {  return ref new B2PolygonShapePRT((b2PolygonShape*)this->fixtureDef->shape); }
			void set(B2PolygonShapePRT^ shape)
			{
				this->fixtureDef->shape = shape->GetPolygonShape();
			}
		}
		property float Density
		{
			float get() { return this->fixtureDef->density; }
			void set(float density) { this->fixtureDef->density = density; }
		}
		property float Friction
		{
			float get() { return this->fixtureDef->friction; }
			void set(float friction) { this->fixtureDef->friction = friction; }
		}
		property float Restitution
		{
			float get() { return this->fixtureDef->restitution; }
			void set(float restitution) { this->fixtureDef->restitution = restitution; }
		}
	internal:
		b2FixtureDef* GetFixtureDef() { return this->fixtureDef; }
	private:
		b2FixtureDef* fixtureDef;
	};

	public ref class B2BodyPRT sealed
	{
	public:
		B2FixturePRT^ CreateFixture(B2PolygonShapePRT^ shape, float32 density);
		B2FixturePRT^ CreateFixture(B2FixtureDefPRT^ fixtureDef);
	public:
		B2Vec2PRT^ GetPosition() { return ref new B2Vec2PRT((b2Vec2&)this->body->GetPosition()); }
		float32 GetAngle() { return this->body->GetAngle(); }
	internal:
		B2BodyPRT(b2Body* body) : body(body)
		{}		
	internal:
		b2Body* GetBody() { return this->body; }
	private:
		b2Body* body;
	};

    public ref class B2WorldPRT sealed
    {
    public:
        B2WorldPRT(B2Vec2PRT^ gravity, bool doSleep);	
		virtual ~B2WorldPRT();
	public:
		B2BodyPRT^ CreateBody(B2BodyDefPRT^ bodyDef);
		void Step(	float32 timeStep, int32 velocityIterations, int32 positionIterations);
		// test use
		static void CreateTestWorld();
	internal:
		b2World* GetWorld() { return this->world; }
	private:
		// b2world
		b2World* world;
    };
}
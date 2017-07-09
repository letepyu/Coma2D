/*
* The MIT License (MIT)
*
* Copyright (c) 2015 Heonyang Ju
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
* MIT ���̼��� (MIT)
*
* ���۱�(C) 2015 �����
*
* �� ������ ����, �Ʒ��� ������ ������ �� ���� ���� ����Ʈ��� �ٷ�� ����
* ����Ʈ������ ���纻�� ���õ� ����("����Ʈ����")�� ȹ���ϴ� ������� ������
* ������ ��� �ȴ�. ���� ������ ���, ����, ����, ����, ����, ����, ���� ���̼���
* �׸���/�Ǵ� ����Ʈ������ ���纻�� �Ǹſ� ���޵� ����Ʈ��� ���� �������
* �׷��� �� �� �ֵ��� �㰡�ϴ� ���ѿ� ���� ������ ���� �Ѵ�.
*
* ���� ���۱� ǥ�ÿ� �� �㰡 ǥ�ô� ��� ����Ʈ������ ���纻 �Ǵ� ����� �Ϻκп�
* ���ԵǾ�� �Ѵ�.
*
* �� ����Ʈ����� Ư���� ������ ħ�� ������ ���� �����, ���ռ��� ��������
* ���ѵǴ� ���� �ƴ� ����� �Ǵ� �������� ��� ������ �������� "�ִ� �״��"
* ���� �ȴ�. ��� ��쿡�� ������ �Ǵ� ���۱��ڴ� ����Ʈ������ ���� �Ȱ� ��
* �Ǵ� ����Ʈ������ ��� �Ǵ� �ŷ��κ��� �߻��ϴ� ���, �ҹ� ���� �Ǵ� ��Ÿ ���࿡
* ����, ��� �Ҽ�, ���� �Ǵ� �ٸ� å���� ���ؼ��� å���� ����.
*
* ������ MIT���̼��� ������ �������̸�, ��� �ؼ��� ������ �����Ѵ�.
*/

/*
* filename	GameObject.cpp
* fileinfo	���� ǥ�� ��ü Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "GameObject.h"

COMA_USING_NS

b2World* GameObject::physicsWorld = nullptr;
float GameObject::pixelPerMeter = 20;
float GameObject::meterPerPixel = 1 / 20.f;

GameObject::GameObject()
	:DisplayObjectContainer(), usePhysics(false)
{
	collider = new b2PolygonShape();

	//Point pos = localToWorld(Point{ getLocalPosition().x+ getLocalSize().width/2, getLocalPosition().y + getLocalSize().height/2 });
	//Point pos2 = localToWorld(getLocalPosition());

	bodyDef.type = b2_dynamicBody;
	//bodyDef->position.Set(pos.x * meterPerPixel, pos.y * meterPerPixel);

	//((b2PolygonShape*)collider)->SetAsBox((pos.x - pos2.x)*meterPerPixel, (pos.y - pos2.y)*meterPerPixel);

	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
}


GameObject::~GameObject()
{
	if(collider) delete collider;
}

void GameObject::setPhysicsWorld(b2World* world)
{
	physicsWorld = world;
}
void GameObject::setPixelPerMeter(float pixel)
{
	pixelPerMeter = pixel;
	meterPerPixel = 1.f / pixel;
}

void GameObject::createPhysics(bool setDefault)
{
	if (!physicsWorld)
		return;
	if (setDefault)
	{
		Point pos = localToWorld(Point{ getLocalPosition().x + getLocalSize().width / 2, getLocalPosition().y + getLocalSize().height / 2 });
		Point pos2 = localToWorld(getLocalPosition());
		bodyDef.position.Set(pos.x * meterPerPixel, pos.y * meterPerPixel);
		((b2PolygonShape*)collider)->SetAsBox((pos.x - pos2.x)*meterPerPixel, (pos.y - pos2.y)*meterPerPixel);
	}
	body = physicsWorld->CreateBody(&bodyDef);
	fixtureDef.shape = collider;
	body->CreateFixture(&fixtureDef);
	usePhysics = true;
}
void GameObject::destroyPhysics()
{
	usePhysics = false;
}

void GameObject::setBodyType(b2BodyType type)
{
	bodyDef.type = type;
}
void GameObject::setColliderPosition(Point point)
{
	Point pos = localToWorld(point);
	bodyDef.position.Set(pos.x*meterPerPixel, pos.y*meterPerPixel);
}
void GameObject::setColliderPosition(float x, float y)
{
	setColliderPosition(Point{ x, y });
}
void GameObject::setBoxCollider(float width, float height)
{
	if (collider) delete collider;
	collider = new b2PolygonShape();
	Point pos = localToWorld(Point{ 0, 0 });
	Point pos2 = localToWorld(Point{width, height});
	((b2PolygonShape*)collider)->SetAsBox((pos2.x - pos.x)*meterPerPixel, (pos2.y - pos.y)*meterPerPixel);
}
void GameObject::setCircleCollider(float radius)
{
	if (collider) delete collider;
	collider = new b2CircleShape();
	Point pos = localToWorld(Point{ 0, 0 });
	Point pos2 = localToWorld(Point{ radius, radius });
	((b2CircleShape*)collider)->m_radius = ((pos2.x - pos.x) + (pos2.y - pos.y))/2 * meterPerPixel;
}
void GameObject::setCollider(b2Shape* shape)
{
	if (collider) delete collider;
	collider = shape;
}

void GameObject::setDensity(float value)
{
	fixtureDef.density = value;
}
void GameObject::setFriction(float value)
{
	fixtureDef.friction = value;
}
void GameObject::setRestitution(float value)
{
	fixtureDef.restitution = value;
}


void GameObject::update(double deltaTime)
{
	if (body && IsBadReadPtr(body, MAX_PATH))
	{
		return;
	}
	DisplayObjectContainer::update(deltaTime);
	if (!usePhysics || IsBadReadPtr(body, MAX_PATH))
		return;
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	this->setPosition(position.x*pixelPerMeter, position.y*pixelPerMeter);
	this->setRotation(angle*(180.0f/PI));
	
}
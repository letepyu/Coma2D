/*
* filename	SpriteEvent.h
* fileinfo	�ִϸ��̼� ��������Ʈ Ŭ���� �̺�Ʈ ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Event.h"
#include "Sprite.h"

COMA_NS_BEGIN

class SpriteEvent :
	public Event
{
public:
	SpriteEvent(const std::string& type, Sprite* target);
	virtual ~SpriteEvent();

	static const std::string ENTER_FRAME;
	static const std::string STOPPED;
	static const std::string PLAY;

	Sprite* getTarget(){ return target; }
	unsigned int getCurrentFrame(){ return target->getCurrentFrame(); }
	unsigned int getTotalFrame(){ return target->getTotalFrame(); }
private:
	Sprite* target;
};

COMA_END
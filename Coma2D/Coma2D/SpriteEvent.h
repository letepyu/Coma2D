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

	Sprite* GetTarget() const { return target_; }
	unsigned int GetCurrentFrame() const { return target_->getCurrentFrame(); }
	unsigned int GetTotalFrame() const { return target_->getTotalFrame(); }

private:
	Sprite* target_;
};

COMA_END
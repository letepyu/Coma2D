/*
* filename	SpriteEvent.cpp
* fileinfo	�ִϸ��̼� ��������Ʈ Ŭ���� �̺�Ʈ ���� ����
* author	����� (Heonyang Ju)
*/

#include "SpriteEvent.h"

COMA_USING_NS

const std::string SpriteEvent::ENTER_FRAME = "sprite_enterFrame";
const std::string SpriteEvent::STOPPED = "sprite_stopped";
const std::string SpriteEvent::PLAY = "sprite_play";

SpriteEvent::SpriteEvent(std::string type, Sprite* target)
:Event(type), target(target)
{
}


SpriteEvent::~SpriteEvent()
{
}

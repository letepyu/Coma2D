/*
* filename	ObjectEvent.cpp
* fileinfo	ǥ�ð�ü �̺�Ʈ ���� ����
* author	����� (Heonyang Ju)
*/

#include "ObjectEvent.h"
#include "DisplayObject.h"

COMA_USING_NS

const std::string ObjectEvent::UPDATE = "object_update";
const std::string ObjectEvent::RENDER = "object_render";
const std::string ObjectEvent::ADDED = "object_added";
const std::string ObjectEvent::REMOVED = "object_removed";

ObjectEvent::ObjectEvent(const std::string& type, DisplayObject* target, double deltaTime)
	:Event(type), target_(target), time_(deltaTime)
{
}


ObjectEvent::~ObjectEvent()
{
}

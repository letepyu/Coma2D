/*
* filename	Event.h
* fileinfo	�̺�Ʈ ���� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

/*===================================================================================
Event.h
EventŬ������ �̺�Ʈ�� ������ ��� Ŭ�����̴�. EventDispatcher�� dispatchEvent���� ��
�ڷ� ���ȴ�. �� ���, ��ϵ� �������� �Լ��� ���ڷ� ���޵ȴ�. ��, �߻��� �̺�Ʈ��
���� ������ �ش� �Լ��� �˸� �� �ִٴ� ���̴�.

�̺�Ʈ �߻� ����
dispatchEvent(new Event("mouseEvent"))
=> type�� "mouseEvent"�� ������ Ž��
=> ������ ��� �ش� �Լ� ���� (Event* ���� ����)

�̺�Ʈ ��� ����
void mouseListener(Event* event);
EventDispatcher->setEventListener("mouseEvent", BIND(mouseListener));
=> �̺�Ʈ �߻� �� mouseListener�Լ� ȣ��


static const std::string�� �̿��Ͽ� �̺�Ʈ Ÿ���� ������ �� �ִ�.
���� ����� �޾�, �̺�Ʈ�� ���õ� �����͸� ������ ���� �ִ�.

��) MouseEvent (EventŬ���� ���)
dispatchEvent(new MouseEvent( MouseEvent::CLICK, x, y ));
setEventListener(MouseEvent::CLICK, BIND(mouseListener));
void mouseListener(Event* event)
{
	MouseEvent* mouseEvent = (MouseEvent*) event;
	mouseEvent->getX();
	mouseEvent->getY();
}
====================================================================================*/

#pragma once
#include <string>
#include "comaUtil.h"

COMA_NS_BEGIN

class Event
{
public:
	explicit Event(const std::string& type);
	virtual ~Event();
	const std::string& getType() const
	{
		return type;
	}
private:
	const std::string type;
};

COMA_END
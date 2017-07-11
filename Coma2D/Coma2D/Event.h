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
DispatchEvent(new Event("mouseEvent"))
=> type�� "mouseEvent"�� ������ Ž��
=> ������ ��� �ش� �Լ� ���� (Event* ���� ����)

�̺�Ʈ ��� ����
void mouseListener(Event* event);
EventDispatcher->SetEventListener("mouseEvent", BIND(mouseListener));
=> �̺�Ʈ �߻� �� mouseListener�Լ� ȣ��


static const std::string�� �̿��Ͽ� �̺�Ʈ Ÿ���� ������ �� �ִ�.
���� ����� �޾�, �̺�Ʈ�� ���õ� �����͸� ������ ���� �ִ�.

��) MouseEvent (EventŬ���� ���)
DispatchEvent(new MouseEvent( MouseEvent::CLICK, x, y ));
SetEventListener(MouseEvent::CLICK, BIND(mouseListener));
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
	const std::string& GetType() const
	{
		return type_;
	}
private:
	const std::string type_;
};

COMA_END
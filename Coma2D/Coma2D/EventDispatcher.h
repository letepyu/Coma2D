/*
* filename	EventDispatcher.h
* fileinfo	�̺�Ʈ �й� �� ó�� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

/*===================================================================================
EventDispatcher.h
EventDispatcherŬ������ �̺�Ʈ�� �����ϰ� ���, ����, �߻��� ����ϴ� �⺻ Ŭ�����̴�.
��κ��� Coma2D Ŭ������ EventDispatcher�� ��ӹ�����, �̺�Ʈ�� �����ϱ� ���ؼ� �� Ŭ
������ ��ӹ޾ƾ� �Ѵ�.

void setEventListener(string, EventFunction)
�̺�Ʈ �����ʸ� ����Ʈ�� �߰��ϴ� ������ �Ѵ�. ��Ͻÿ��� void(Event*)������ �Լ���
bind�ϰ�, �̺�Ʈ�� �������� Ÿ��(string)�� �����ؾ� �Ѵ�.
�Ϲ������� type�� �ش� Ÿ���� �����ϴ� EventŬ�������� static const std::string��
���·� �����ȴ�.

void removeEventListener(string, EventFunction)
�̺�Ʈ �����ʸ� ����Ʈ���� �����ϴ� ������ �Ѵ�.

bool hasEventListener(string);
�ش� �̺�Ʈ Ÿ���� �����ʿ� ������ ��� true�� ��ȯ�Ѵ�.

void dispatchEvent(Event*)
�̺�Ʈ�� �߻���Ų��. �ش� �̺�Ʈ�� ������ Ÿ���� ���� �����ʸ� ��� �����Ų��. �Լ���
����� Event��ü�� ���ڷ� �����Ѵ�.
====================================================================================*/

#pragma once
#include <functional>
#include <vector>
#include <string>
#include "Event.h"
#define BIND(T) std::bind(&T, this, std::placeholders::_1)

COMA_NS_BEGIN

typedef std::function<void(Event*)> EventFunction;

struct Listener
{
	std::string type;
	EventFunction function;	//���� �Լ�
	void* target; //�̺�Ʈ�� ������ Ŭ����
};


class EventDispatcher
{
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	//�̺�Ʈ ������ ��ü�� ����Ѵ�.
	void setEventListener(const std::string& type, EventFunction function, void* target = nullptr); 

	//�̺�Ʈ ������ ��ü�� �����Ѵ�.
	void removeEventListener(const std::string& type, void* target);
	
	//�ش� Ÿ���� �����ʰ� ������ ��� true��ȯ
	bool hasEventListener(const std::string& type);
	
	//�̺�Ʈ�� �߻���Ų�� (��ϵ� �ش� ������ ����)
	void dispatchEvent(Event* event);

private:
	std::vector<Listener> listenerList;
};

COMA_END
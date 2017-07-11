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

void SetEventListener(string, EventFunction)
�̺�Ʈ �����ʸ� ����Ʈ�� �߰��ϴ� ������ �Ѵ�. ��Ͻÿ��� void(Event*)������ �Լ���
bind�ϰ�, �̺�Ʈ�� �������� Ÿ��(string)�� �����ؾ� �Ѵ�.
�Ϲ������� type�� �ش� Ÿ���� �����ϴ� EventŬ�������� static const std::string��
���·� �����ȴ�.

void RemoveEventListener(string, EventFunction)
�̺�Ʈ �����ʸ� ����Ʈ���� �����ϴ� ������ �Ѵ�.

bool HasEventListener(string);
�ش� �̺�Ʈ Ÿ���� �����ʿ� ������ ��� true�� ��ȯ�Ѵ�.

void DispatchEvent(Event*)
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

typedef std::function<void(Event*)> EventCallback;

struct Listener
{
	std::string type;
	EventCallback function;	// �ݹ� �Լ�
	void* target; // �̺�Ʈ�����ʸ� �߰��� Ŭ����
};


class EventDispatcher
{
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	//�̺�Ʈ ������ ��ü�� ����Ѵ�.
	void SetEventListener(const std::string& type, EventCallback function, void* target = nullptr); 

	//�̺�Ʈ ������ ��ü�� �����Ѵ�.
	void RemoveEventListener(const std::string& type, void* target);
	
	//�ش� Ÿ���� �����ʰ� ������ ��� true��ȯ
	bool HasEventListener(const std::string& type);
	
	//�̺�Ʈ�� �߻���Ų�� (��ϵ� �ش� ������ ����)
	void DispatchEvent(Event* event);

private:
	std::vector<Listener> listenerList_;
};

COMA_END
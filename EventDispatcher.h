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

namespace coma2d
{
	typedef std::function<void(Event*)> EventFunction;
	
	struct Listener	//�̺�Ʈ �����ʸ� �����ϴ� ����ü
	{
		std::string type;		//�̺�Ʈ Ÿ��
		EventFunction function;	//���� �Լ�
	};
	

	class EventDispatcher
	{
	public:
		EventDispatcher();
		virtual ~EventDispatcher();
		
		void setEventListener(std::string type, EventFunction function);		//�̺�Ʈ ������ ��ü�� ����Ѵ�.
		void removeEventListener(std::string type, EventFunction function);		//�̺�Ʈ ������ ��ü�� �����Ѵ�.
		bool hasEventListener(std::string type);								//�ش� Ÿ���� �����ʰ� ������ ��� true��ȯ
		void dispatchEvent(Event* event);										//�̺�Ʈ�� �߻���Ų�� (��ϵ� �ش� ������ ����)
	private:
		std::vector<Listener> listenerList;	//�̺�Ʈ �����ʰ� ����� ����Ʈ
	};
}
/*
* filename	Scene.h
* fileinfo	��� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "DisplayObjectContainer.h"

COMA_NS_BEGIN

class Scene :
	public DisplayObjectContainer
{
protected:
	Scene();
public:
	virtual ~Scene();
	bool _registerParent(DisplayObjectContainer* parent) { return false; }	//(�������̵�) Scene��ü�� addChild�� �߰��� �� ����.
	bool _unregisterParent(){ return false; }								//(�������̵�) Scene��ü�� addChild�� �߰��� �� ����.
};

COMA_END
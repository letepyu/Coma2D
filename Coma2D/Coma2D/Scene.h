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
public:
	Scene();
public:
	virtual ~Scene();
	bool _RegisterParent(DisplayObjectContainer* parent) { return false; }	//(�������̵�) Scene��ü�� addChild�� �߰��� �� ����.
	bool _UnregisterParent(){ return false; }								//(�������̵�) Scene��ü�� addChild�� �߰��� �� ����.
};

COMA_END
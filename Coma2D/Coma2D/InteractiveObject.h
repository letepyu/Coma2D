/*
* filename	InteractiveObject.h
* fileinfo	��ȣ�ۿ� ǥ�� ��ü Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "comaUtil.h"
#include "DisplayObject.h"
COMA_NS_BEGIN

class InteractiveObject :
	public DisplayObject
{
public:
	InteractiveObject();
	virtual ~InteractiveObject();
};

COMA_END
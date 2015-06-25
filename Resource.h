#pragma once
#include "comaUtil.h"

COMA_NS_BEGIN

class Resource
{
public:
	virtual bool loadResource() = 0;
	virtual bool unloadResource() = 0;
	virtual bool isLoaded() = 0;

	//��� ���ҽ��� �ε���� ���� ���·� ������ �� �ִ�.
};

COMA_END
/*
* filename	Resource.h
* fileinfo	���ҽ� �������̽�
* author	����� (Heonyang Ju)
*/

#pragma once
#include "comaUtil.h"

COMA_NS_BEGIN

class Resource
{
public:
	virtual bool LoadResource() = 0;
	virtual bool UnloadResource() = 0;
	virtual bool IsLoaded() = 0;

	//��� ���ҽ��� �ε���� ���� ���·� ������ �� �ִ�.
};

COMA_END
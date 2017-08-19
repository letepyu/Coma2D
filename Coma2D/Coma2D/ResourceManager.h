/*
* filename	ResourceManager.h
* fileinfo	���ҽ� ���� Ŭ������ ���� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Manager.h"
#include "Resource.h"
#include <vector>
COMA_NS_BEGIN

class ResourceManager :
	public Manager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourceManager* Push(Resource* resource);
	bool Clear();

	bool LoadResources();
	bool UnloadResources();

	int GetResourceNumbers() const { return resourceList_.size(); }
	bool IsLoading() const { return loading_; }

private:
	std::vector<Resource*> resourceList_;
	bool loading_;

private:
	void CompleteListener(const Event* event);
};

COMA_END
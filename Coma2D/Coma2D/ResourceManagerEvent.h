/*
* filename	ResourceManagerEvent.h
* fileinfo	���ҽ� �Ŵ��� Ŭ������ �̺�Ʈ ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Event.h"
#include "ResourceManager.h"
COMA_NS_BEGIN

class ResourceManagerEvent :
	public Event
{
public:
	ResourceManagerEvent(const std::string& type, ResourceManager* manager, int resourceNumbers = 0, int processedResourceNumbers = 0);
	virtual ~ResourceManagerEvent();

public:
	static const std::string LOAD_BEGIN;
	static const std::string LOADING;
	static const std::string LOAD_COMPLETE;

	static const std::string UNLOAD_BEGIN;
	static const std::string UNLOADING;
	static const std::string UNLOAD_COMPLETE;

public:
	//ó���� ���ҽ� ����
	int GetResourceNumbers() const { return resourceNumbers_; }

	//ó������ ���� ���ҽ� ����
	int GetLeftResourceNumbers() const { return leftResourceNumbers_; }

	//ó���� ���ҽ� ����
	int GetProcessedResourceNumbers() const { return processedResourceNumbers_; }

	//���൵ (0.0f ~ 1.0f)
	float GetProgress() const { return (float)processedResourceNumbers_ / (float)resourceNumbers_; }

	ResourceManager* GetTarget() const { return target_; }

private:
	int resourceNumbers_;
	int leftResourceNumbers_;
	int processedResourceNumbers_;
	ResourceManager* target_;
};

COMA_END
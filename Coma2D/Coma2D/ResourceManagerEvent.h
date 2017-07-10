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
	ResourceManagerEvent(std::string type, ResourceManager* manager, int resourceNumbers=0, int processedResourceNumbers = 0);
	virtual ~ResourceManagerEvent();

public:
	static const std::string LOAD_BEGIN;
	static const std::string LOADING;
	static const std::string LOAD_COMPLETE;

	static const std::string UNLOAD_BEGIN;
	static const std::string UNLOADING;
	static const std::string UNLOAD_COMPLETE;
public:
	int getResourceNumbers(){ return resourceNumbers; }	//ó���� ���ҽ� ����
	int getLeftResourceNumbers(){ return leftResourceNumbers; }	//ó������ ���� ���ҽ� ����
	int getProcessedResourceNumbers(){ return processedResourceNumbers; } //ó���� ���ҽ� ����
	float getProgress(){ return (float)processedResourceNumbers / (float)resourceNumbers; } //���൵ (0.0f ~ 1.0f)
	ResourceManager* getTarget(){ return target; }//Ÿ��
private:
	int resourceNumbers;
	int leftResourceNumbers;
	int processedResourceNumbers;
	ResourceManager* target;
};

COMA_END
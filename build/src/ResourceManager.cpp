/*
* The MIT License (MIT)
*
* Copyright (c) 2015 Heonyang Ju
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
* MIT ���̼��� (MIT)
*
* ���۱�(C) 2015 �����
*
* �� ������ ����, �Ʒ��� ������ ������ �� ���� ���� ����Ʈ��� �ٷ�� ����
* ����Ʈ������ ���纻�� ���õ� ����("����Ʈ����")�� ȹ���ϴ� ������� ������
* ������ ��� �ȴ�. ���� ������ ���, ����, ����, ����, ����, ����, ���� ���̼���
* �׸���/�Ǵ� ����Ʈ������ ���纻�� �Ǹſ� ���޵� ����Ʈ��� ���� �������
* �׷��� �� �� �ֵ��� �㰡�ϴ� ���ѿ� ���� ������ ���� �Ѵ�.
*
* ���� ���۱� ǥ�ÿ� �� �㰡 ǥ�ô� ��� ����Ʈ������ ���纻 �Ǵ� ����� �Ϻκп�
* ���ԵǾ�� �Ѵ�.
*
* �� ����Ʈ����� Ư���� ������ ħ�� ������ ���� �����, ���ռ��� ��������
* ���ѵǴ� ���� �ƴ� ����� �Ǵ� �������� ��� ������ �������� "�ִ� �״��"
* ���� �ȴ�. ��� ��쿡�� ������ �Ǵ� ���۱��ڴ� ����Ʈ������ ���� �Ȱ� ��
* �Ǵ� ����Ʈ������ ��� �Ǵ� �ŷ��κ��� �߻��ϴ� ���, �ҹ� ���� �Ǵ� ��Ÿ ���࿡
* ����, ��� �Ҽ�, ���� �Ǵ� �ٸ� å���� ���ؼ��� å���� ����.
*
* ������ MIT���̼��� ������ �������̸�, ��� �ؼ��� ������ �����Ѵ�.
*/

/*
* filename	ResourceManager.cpp
* fileinfo	���ҽ� ���� Ŭ������ ���� ����
* author	����� (Heonyang Ju)
*/

#include "ResourceManager.h"
#include "ResourceManagerEvent.h"
#include <thread>

COMA_USING_NS

ResourceManager::ResourceManager() : loading(false)
{
	setEventListener(ResourceManagerEvent::LOAD_COMPLETE, BIND(ResourceManager::completeListener));
	setEventListener(ResourceManagerEvent::UNLOAD_COMPLETE, BIND(ResourceManager::completeListener));
}


ResourceManager::~ResourceManager()
{
	clear();
}

ResourceManager* ResourceManager::push(Resource* resource)
{
	if (resource)
		resourceList.push_back(resource);
	return this;
}

bool ResourceManager::clear()
{
	resourceList.clear();
	return true;
}

void thread_loadResources(ResourceManager* manager, std::vector<Resource*> resources)
{
	int resourceNumbers = resources.size();
	int loadedResourceNumbers = 0;
	manager->dispatchEvent(new ResourceManagerEvent(ResourceManagerEvent::LOAD_BEGIN, manager, resourceNumbers, loadedResourceNumbers));
	for (unsigned int i = 0; i < resources.size(); i++)
	{
		if (resources[i])
			if (!resources[i]->isLoaded())
				resources[i]->loadResource();
		loadedResourceNumbers++;
		manager->dispatchEvent(new ResourceManagerEvent(ResourceManagerEvent::LOADING, manager, resourceNumbers, loadedResourceNumbers));
	}
	manager->dispatchEvent(new ResourceManagerEvent(ResourceManagerEvent::LOAD_COMPLETE, manager, resourceNumbers, loadedResourceNumbers));
}
void thread_unloadResources(ResourceManager* manager, std::vector<Resource*> resources)
{
	int resourceNumbers = resources.size();
	int unloadedResourceNumbers = 0;
	manager->dispatchEvent(new ResourceManagerEvent(ResourceManagerEvent::UNLOAD_BEGIN, manager, resourceNumbers, unloadedResourceNumbers));
	for (unsigned int i = 0; i < resources.size(); i++)
	{
		if (resources[i])
			if (resources[i]->isLoaded())
				resources[i]->unloadResource();
		unloadedResourceNumbers++;
		manager->dispatchEvent(new ResourceManagerEvent(ResourceManagerEvent::UNLOADING, manager, resourceNumbers, unloadedResourceNumbers));
	}
	manager->dispatchEvent(new ResourceManagerEvent(ResourceManagerEvent::UNLOAD_COMPLETE, manager, resourceNumbers, unloadedResourceNumbers));
}

bool ResourceManager::loadResources()
{
	if (loading)
		return false;
	std::thread trd(thread_loadResources, this, resourceList);
	trd.detach();
	loading = true;
	return true;
}

bool ResourceManager::unloadResources()
{
	if (loading)
		return false;
	std::thread trd(thread_unloadResources, this, resourceList);
	trd.detach();
	loading = true;
	return true;
}

void ResourceManager::completeListener(Event* event)
{
	loading = false;
}
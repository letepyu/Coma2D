/*
* filename	SceneEvent.h
* fileinfo	���(Scene) Ŭ������ �̺�Ʈ ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Event.h"
#include "Scene.h"

COMA_NS_BEGIN

class SceneEvent :
	public Event
{
public:
	SceneEvent(const std::string& type, const Scene* target);
	virtual ~SceneEvent();

public:
	static const std::string CHANGED;
	const Scene* getScene() const{ return scene; }
private:
	const Scene* scene;
};

COMA_END
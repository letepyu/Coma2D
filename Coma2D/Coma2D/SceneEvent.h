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
	SceneEvent(const std::string& type, Scene* target);
	virtual ~SceneEvent();

public:
	static const std::string CHANGED;
	Scene* GetScene() const { return scene_; }

private:
	Scene* scene_;
};

COMA_END
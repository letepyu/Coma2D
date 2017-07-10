/*
* filename	SceneEvent.cpp
* fileinfo	���(Scene) Ŭ������ �̺�Ʈ ���� ����
* author	����� (Heonyang Ju)
*/

#include "SceneEvent.h"

COMA_USING_NS

const std::string SceneEvent::CHANGED = "scene_sceneChanged";

SceneEvent::SceneEvent(const std::string& type, const Scene* scene)
:Event(type), scene(scene)
{

}


SceneEvent::~SceneEvent()
{
}

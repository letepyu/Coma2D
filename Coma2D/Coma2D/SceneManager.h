/*
* filename	SceneManager.h
* fileinfo	��� ���� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Manager.h"
#include "Scene.h"

COMA_NS_BEGIN

class SceneManager :
	public Manager
{
public:
	SceneManager();
	virtual ~SceneManager();
public:
	void changeScene(Scene* scene);
	Scene* getScene(){ return scene; }
private:
	Scene* scene;
};

COMA_END
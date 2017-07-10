/*
* filename	Camera.h
* fileinfo	DisplayObject�� ī�޶� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "comaUtil.h"

COMA_NS_BEGIN

class DisplayObject;

class Camera :
	public DisplayObject
{
public:
	Camera(float width, float height);
	virtual ~Camera();

	void update();
	void render(ID2D1HwndRenderTarget* renderTarget);

	void on();
	void off();
	bool isCameraOn();

	Matrix3x2 getMatrix();
	bool _registerParent(DisplayObjectContainer* parent);
	bool _unregisterParent();

private:
	ID2D1SolidColorBrush* brush;
	bool cameraOn;
	int ref;
};

COMA_END
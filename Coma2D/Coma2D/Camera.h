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

	virtual void Update();
	virtual void Render(ID2D1HwndRenderTarget* renderTarget);

	void On();
	void Off();
	bool IsCameraOn() const;

	Matrix3x2 GetMatrix();
	bool _RegisterParent(DisplayObjectContainer* parent);
	bool _UnregisterParent();

private:
	ID2D1SolidColorBrush* cameraBrush_;
	bool cameraOn_;
	int ref_;
};

COMA_END
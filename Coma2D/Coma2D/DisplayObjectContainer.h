/*
* filename	DisplayObjectContainer.h
* fileinfo	ȭ�� ǥ�� ��ü �����̳� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "InteractiveObject.h"
#include <vector>

COMA_NS_BEGIN

class DisplayObjectContainer :
	public InteractiveObject
{
public:
	DisplayObjectContainer();
	virtual ~DisplayObjectContainer();

	virtual void Update(double deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* renderTarget, double deltaTime); // �ڽ� ��ü�� ��� �׸���.

	void AddChild(DisplayObject* object);
	void AddChildCenter(DisplayObject* object);
	void RemoveChild(DisplayObject* object);

	void _UpdateSize(); //�ڽ� ��ü�� ũ��� ��ġ�� �°� ����� �ٽ� �����Ѵ�.
private:
	std::vector<DisplayObject*> objectList_;
protected:
	virtual void DrawOutline(ID2D1HwndRenderTarget* renderTarget);
};

COMA_END
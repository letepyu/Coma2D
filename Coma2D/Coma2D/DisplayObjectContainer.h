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

	virtual void update(double deltaTime);
	virtual void render(ID2D1HwndRenderTarget* renderTarget, double deltaTime); // �ڽ� ��ü�� ��� �׸���.

	void addChild(DisplayObject* object);	//�ڽ� ��ü �߰�
	void addChildCenter(DisplayObject* object); // �ڽİ�ü �߾ӿ� �߰�
	void removeChild(DisplayObject* object);//�ڽ� ��ü ����

	void _resetSize();				//�ڽ� ��ü�� ũ��� ��ġ�� �°� ����� �ٽ� �����Ѵ�.
private:
	std::vector<DisplayObject*> objectList;
protected:
	virtual void drawOutline(ID2D1HwndRenderTarget* renderTarget);
};

COMA_END
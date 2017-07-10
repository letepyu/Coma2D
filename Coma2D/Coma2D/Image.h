/*
* filename	Image.h
* fileinfo	�̹��� ǥ�ð�ü Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "DisplayObject.h"
#include "Bitmap.h"

COMA_NS_BEGIN

class Image :
	public DisplayObject
{
public:
	explicit Image(Bitmap* bitmap);
	Image(Bitmap* bitmap, Size size);
	Image(Bitmap* bitmap, float width, float height);
	virtual ~Image();
	virtual void render(ID2D1HwndRenderTarget* renderTarget, double deltaTime);
	Bitmap* getBitmap(){ return bitmap; }
protected:
	bool sizeFixed;
	Bitmap* bitmap;
};

COMA_END
/*
* filename	Image.cpp
* fileinfo	�̹��� ǥ�ð�ü Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "Image.h"

COMA_USING_NS

Image::Image(Bitmap* bitmap) : bitmap(bitmap), sizeFixed(false)
{
	if (bitmap->isLoaded())
	{
		SetLocalSize(bitmap->getResource()->GetSize());
		sizeFixed = true;
	}
}
Image::Image(Bitmap* bitmap, Size size) : bitmap(bitmap), sizeFixed(true)
{
	SetLocalSize(size.width, size.height);
}
Image::Image(Bitmap* bitmap, float width, float height) : bitmap(bitmap), sizeFixed(true)
{
	SetLocalSize(width, height);
}



Image::~Image()
{
	
}
void Image::Render(ID2D1HwndRenderTarget* renderTarget, double deltaTime)
{
	DisplayObject::Render(renderTarget, deltaTime);
	if (!IsVisible())
		return;
	if (bitmap->isLoaded())
	{
		if (!sizeFixed)
		{
			SetLocalSize(bitmap->getResource()->GetSize());
			sizeFixed = true;
		}
		renderTarget->SetTransform(GetScreenMatrix());
		D2D1_RECT_F size = { 0, 0, GetLocalSize().width, GetLocalSize().height };
		renderTarget->DrawBitmap(bitmap->getResource(), size, GetScreenAlpha(), D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	}
}
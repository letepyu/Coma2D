/*
* filename	TextView.h
* fileinfo	�ؽ�Ʈ ��� ǥ�ð�ü Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "DisplayObject.h"
#include <dwrite.h>

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

COMA_NS_BEGIN

class TextView :
	public DisplayObject
{
public:
	TextView(Size layoutSize, const std::wstring& text = L"", const std::wstring& fontName = L"����", float fontSize = 12, const Color& color = Color{ 0, 0, 0 }, int textAlign = ALIGN_LEFT);
	virtual ~TextView();

	virtual void render(ID2D1HwndRenderTarget* renderTarget, double deltaTime);

	void setColor(Color color);
	void setColor(float r, float g, float b);
	void setText(const std::wstring& text);

private:
	static IDWriteFactory* factory;
	static void initFactory();
	static bool factoryAvailable;

	IDWriteTextFormat* format;
	ID2D1SolidColorBrush* textBrush_;

	std::wstring text;
	Color color;
	float tempScreenAlpha;
	int textAlign;
};

COMA_END
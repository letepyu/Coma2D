/*
* The MIT License (MIT)
*
* Copyright (c) 2015 Heonyang Ju
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
* MIT ���̼��� (MIT)
*
* ���۱�(C) 2015 �����
*
* �� ������ ����, �Ʒ��� ������ ������ �� ���� ���� ����Ʈ��� �ٷ�� ����
* ����Ʈ������ ���纻�� ���õ� ����("����Ʈ����")�� ȹ���ϴ� ������� ������
* ������ ��� �ȴ�. ���� ������ ���, ����, ����, ����, ����, ����, ���� ���̼���
* �׸���/�Ǵ� ����Ʈ������ ���纻�� �Ǹſ� ���޵� ����Ʈ��� ���� �������
* �׷��� �� �� �ֵ��� �㰡�ϴ� ���ѿ� ���� ������ ���� �Ѵ�.
*
* ���� ���۱� ǥ�ÿ� �� �㰡 ǥ�ô� ��� ����Ʈ������ ���纻 �Ǵ� ����� �Ϻκп�
* ���ԵǾ�� �Ѵ�.
*
* �� ����Ʈ����� Ư���� ������ ħ�� ������ ���� �����, ���ռ��� ��������
* ���ѵǴ� ���� �ƴ� ����� �Ǵ� �������� ��� ������ �������� "�ִ� �״��"
* ���� �ȴ�. ��� ��쿡�� ������ �Ǵ� ���۱��ڴ� ����Ʈ������ ���� �Ȱ� ��
* �Ǵ� ����Ʈ������ ��� �Ǵ� �ŷ��κ��� �߻��ϴ� ���, �ҹ� ���� �Ǵ� ��Ÿ ���࿡
* ����, ��� �Ҽ�, ���� �Ǵ� �ٸ� å���� ���ؼ��� å���� ����.
*
* ������ MIT���̼��� ������ �������̸�, ��� �ؼ��� ������ �����Ѵ�.
*/

/*
* filename	TextView.cpp
* fileinfo	�ؽ�Ʈ ��� ǥ�ð�ü Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "TextView.h"

COMA_USING_NS

IDWriteFactory* TextView::factory = 0;
bool TextView::factoryAvailable = false;

TextView::TextView(Size layoutSize, std::wstring text, std::wstring fontName, float fontSize, Color color)
{
	if (!factoryAvailable)
		initFactory();
	
	factory->CreateTextFormat(fontName.c_str(), 0, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ko", &format);
	setLocalSize(layoutSize);
	this->text = text;
	this->color = color;
	this->color.a = getScreenAlpha();
}


TextView::~TextView()
{
	if(factory) factory->Release();
	factoryAvailable = false;
	if (format)format->Release();
	if (brush) brush->Release();
}


void TextView::initFactory()
{
	HRESULT hr;
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&factory
		);

	if (FAILED(hr))
		return;
	factoryAvailable = true;
}

void TextView::render(ID2D1HwndRenderTarget* renderTarget, double deltaTime)
{
	DisplayObject::render(renderTarget, deltaTime);
	if (!isVisible())
		return;
	if (std::roundf(getScreenAlpha() * 1000) != tempScreenAlpha)
	{
		tempScreenAlpha = std::roundf(getScreenAlpha() * 1000);
		color.a = getScreenAlpha();
		if (brush)brush->Release();
		brush = nullptr;
	}
	if (!brush)
	{
		renderTarget->CreateSolidColorBrush(color, &brush);
	}
	
	renderTarget->SetTransform(getScreenMatrix());
	Rect rect = { 0, 0, getLocalSize().width, getLocalSize().height };
	renderTarget->DrawTextW(text.c_str(), text.length(), format, rect, brush);
}

void TextView::setColor(Color color)
{
	this->color = color;
	color.a = getScreenAlpha();
	if (brush) brush->Release();
	brush = nullptr;
}
void TextView::setColor(float r, float g, float b)
{
	setColor(Color{ r, g, b });
}
void TextView::setText(std::wstring text)
{
	this->text = text;
}
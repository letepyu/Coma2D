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
* filename	DisplayObjectContainer.cpp
* fileinfo	ȭ�� ǥ�� ��ü �����̳� Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/
#include "InteractiveObject.h"
#include "DisplayObjectContainer.h"

COMA_USING_NS

DisplayObjectContainer::DisplayObjectContainer()
:InteractiveObject()
{
}


DisplayObjectContainer::~DisplayObjectContainer()
{
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->_unregisterParent();
	}
}

void DisplayObjectContainer::addChild(DisplayObject* object)
{
	if (object->getParent())
		return;
	for (unsigned int i = 0; i < objectList.size(); i++)
		if (objectList[i] == object) return;
	if (!object->_registerParent(this)) return;
	objectList.push_back(object);
	_resetSize();
}
void DisplayObjectContainer::removeChild(DisplayObject* object)
{
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] == object)
		{
			if (!object->_unregisterParent())
				return;
			objectList.erase(objectList.begin() + i);
			_resetSize();
			return;
		}
	}
}

void DisplayObjectContainer::_resetSize()
{
	Rect rect{ 10000000, 10000000, -10000000, -10000000 };
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		Matrix3x2 matrix = objectList[i]->getMatrix() * objectList[i]->getCameraMatrix();

		Point point[4] = {
			matrix.TransformPoint(Point{ objectList[i]->getLocalPosition().x,										objectList[i]->getLocalPosition().y }),
			matrix.TransformPoint(Point{ objectList[i]->getLocalPosition().x + objectList[i]->getLocalSize().width, objectList[i]->getLocalPosition().y }),
			matrix.TransformPoint(Point{ objectList[i]->getLocalPosition().x + objectList[i]->getLocalSize().width, objectList[i]->getLocalPosition().y + objectList[i]->getLocalSize().height }),
			matrix.TransformPoint(Point{ objectList[i]->getLocalPosition().x,										objectList[i]->getLocalPosition().y + objectList[i]->getLocalSize().height })
		};

		for (int i = 0; i < 4; i++)
		{
			if (point[i].x < rect.left)
				rect.left = point[i].x;
			if (point[i].y < rect.top)
				rect.top = point[i].y;
			if (point[i].x > rect.right)
				rect.right = point[i].x;
			if (point[i].y > rect.bottom)
				rect.bottom = point[i].y;
		}
	}
	setLocalSize(rect.right - rect.left,rect.bottom - rect.top);
	setLocalPosition(rect.left, rect.top);
}

void DisplayObjectContainer::render(ID2D1HwndRenderTarget* renderTarget, double deltaTime)
{
	DisplayObject::render(renderTarget, deltaTime);
	if (!isVisible())
		return;
	for (unsigned int i = 0; i < objectList.size(); i++)
	{

		objectList[i]->setDrawOutline(isOutlineDrawing());
		objectList[i]->render(renderTarget, deltaTime);
	}
}
void DisplayObjectContainer::update(double deltaTime)
{
	DisplayObject::update(deltaTime);
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->update(deltaTime);
	}
}


void DisplayObjectContainer::drawOutline(ID2D1HwndRenderTarget* renderTarget)
{
	if (!brush)
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brush);
	brush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	Point position = localToScreen(getLocalPosition());
	Point position2 = localToScreen(Point{ getLocalPosition().x + getLocalSize().width, getLocalPosition().y + getLocalSize().height });
	renderTarget->DrawRectangle(Rect{ position.x, position.y, position2.x, position2.y }, brush);
	renderTarget->SetTransform(getScreenMatrix());
	renderTarget->DrawEllipse(D2D1::Ellipse(Point{ 0, 0 }, 2, 2), brush);
	brush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
	renderTarget->DrawEllipse(D2D1::Ellipse(getAnchorPoint(), 1.7f,1.7f),brush);
}
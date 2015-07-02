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
	object->_registerParent(this);
	objectList.push_back(object);
	_resetSize();
}
void DisplayObjectContainer::removeChild(DisplayObject* object)
{
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] == object)
		{
			object->_unregisterParent();
			objectList.erase(objectList.begin() + i);
			_resetSize();
			return;
		}
	}
}

void DisplayObjectContainer::_resetSize()
{
	Rect rect{ 0, 0, 0, 0 };
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i]->getX() < rect.left)
			rect.left = objectList[i]->getX();
		if (objectList[i]->getY() < rect.top)
			rect.top = objectList[i]->getY();
		if (objectList[i]->getWidth() + objectList[i]->getX() > rect.right)
			rect.right = objectList[i]->getWidth() + objectList[i]->getX();
		if (objectList[i]->getHeight() + objectList[i]->getY() > rect.bottom)
			rect.bottom = objectList[i]->getHeight() + objectList[i]->getY();
	}
	setLocalSize(rect.bottom - rect.top, rect.right - rect.left);
}

void DisplayObjectContainer::render(ID2D1HwndRenderTarget* renderTarget)
{
	if (!isVisible())
		return;
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->render(renderTarget);
	}
}
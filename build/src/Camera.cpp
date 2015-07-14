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
* filename	Camera.cpp
* fileinfo	DisplayObject�� ī�޶� Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "DisplayObject.h"
#include "Camera.h"
COMA_USING_NS

Camera::Camera(float width, float height)
:DisplayObject(), ref(0), cameraOn(false)
{
	setLocalSize(width, height);
	setVisible(false);
	setAnchorPoint(width / 2.0f, height / 2.0f);
}


Camera::~Camera()
{
	if(brush)brush->Release();
}

void Camera::update()
{
	
}
void Camera::render(ID2D1HwndRenderTarget* renderTarget)
{
	if (!isVisible())
		return;
	if (!brush)
	{
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(0.8f, 0.1f, 0.1f, getAlpha()), &brush);
	}
	renderTarget->SetTransform(getScreenMatrix());
	renderTarget->DrawRectangle(Rect{ 0, 0, getLocalSize().width, getLocalSize().height }, brush);
}

void Camera::on(){ cameraOn = true; }
void Camera::off(){ cameraOn = false; }
bool Camera::isCameraOn(){ return cameraOn; }

Matrix3x2 Camera::getMatrix()
{
	if (isCameraOn())
	{
		return DisplayObject::getMatrix();
	}
	return Matrix3x2::Identity();
}
void Camera::_registerParent(DisplayObjectContainer* parent) {
	if (!getParent() && parent)
	{
		DisplayObject::_registerParent(parent);
		ref++;
	}
}
void Camera::_unregisterParent()
{
	ref--;
	if (ref <= 0)
	{
		DisplayObject::_unregisterParent();
	}
}
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
* filename	MouseEvent.cpp
* fileinfo	���콺 �̺�Ʈ ���� ����
* author	����� (Heonyang Ju)
*/

#include "MouseEvent.h"

COMA_USING_NS

const std::string MouseEvent::MIDDLE_CLICK		= "mouse_middleClick";
const std::string MouseEvent::MIDDLE_MOUSE_DOWN = "mouse_middleMouseDown";
const std::string MouseEvent::MIDDLE_MOUSE_UP	= "mouse_middleMouseUp";
const std::string MouseEvent::CLICK				= "mouse_click";
const std::string MouseEvent::MOUSE_DOWN		= "mouse_mouseDown";
const std::string MouseEvent::MOUSE_UP			= "mouse_mouseUp";
const std::string MouseEvent::MOUSE_MOVE		= "mouse_mouseMove";
const std::string MouseEvent::MOUSE_OUT			= "mouse_mouseOut";
const std::string MouseEvent::MOUSE_OVER		= "mouse_mouseOver";
const std::string MouseEvent::MOUSE_WHEEL		= "mouse_mouseWheel";
const std::string MouseEvent::RIGHT_CLICK		= "mouse_rightClick";
const std::string MouseEvent::RIGHT_MOUSE_DOWN	= "mouse_rightMouseDown";
const std::string MouseEvent::RIGHT_MOUSE_UP	= "mouse_rightMouseUp";
const std::string MouseEvent::ROLL_OVER			= "mouse_rollOver";
const std::string MouseEvent::ROLL_OUT			= "mouse_rollOut";

MouseEvent::MouseEvent(std::string type, bool buttonDown, bool altKey, bool ctrlKey, bool shiftKey, int delta, float stageX, float stageY, float localX, float localY)
:Event(type), buttonDown(buttonDown), altKey(altKey), ctrlKey(ctrlKey), shiftKey(shiftKey), delta(delta), stageX(stageX), stageY(stageY), localX(localX), localY(localY)
{
}


MouseEvent::~MouseEvent()
{
}

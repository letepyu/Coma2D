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
* filename	WindowEvent.cpp
* fileinfo	������ ���� Ŭ������ �̺�Ʈ ���� ����
* author	����� (Heonyang Ju)
*/

#include "WindowEvent.h"
COMA_USING_NS

const std::string WindowEvent::CREATED			= "window_created";
const std::string WindowEvent::DESTROY			= "window_destroy";

const std::string WindowEvent::ACTIVATED		= "window_activated";
const std::string WindowEvent::INACTIVATED		= "window_inactivated";

const std::string WindowEvent::MINIMIZED		= "window_minimized";
const std::string WindowEvent::MAXIMIZED		= "window_maximized";
const std::string WindowEvent::RESTORED			= "window_restored";
const std::string WindowEvent::ENTER_FULLSCREEN	= "window_enterFullscreen";
const std::string WindowEvent::EXIT_FULLSCREEN	= "window_exitFullscreen";

const std::string WindowEvent::ENTER_RESIZEMOVE	= "window_enterResizeMove";
const std::string WindowEvent::EXIT_RESIZEMOVE	= "window_exitResizeMove";
const std::string WindowEvent::RESIZE			= "window_resize";
const std::string WindowEvent::RESIZING			= "window_resizing";
const std::string WindowEvent::MOVE				= "window_move";
const std::string WindowEvent::MOVING			= "window_moving";

const std::string WindowEvent::UPDATE			= "window_update";

WindowEvent::WindowEvent(std::string type, ComaWindow* target, WPARAM wParam, LPARAM lParam)
	:Event(type)
{
	this->target = target;
	this->wParam = wParam;
	this->lParam = lParam;
}


WindowEvent::~WindowEvent()
{
}

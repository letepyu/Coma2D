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
* filename	ComaDevice.cpp
* fileinfo	�����ӿ�ũ ���� �̱��� Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "ComaDevice.h"

#include "Bitmap.h"

COMA_USING_NS

ComaDevice* ComaDevice::device;

bool ComaDevice::setWindow(ComaWindow* window)
{
	if (initialized)
		return false;
	this->window = window;
	return true;
}
bool ComaDevice::setRenderer(ComaRenderer* renderer)
{
	if (initialized)
		return false;
	this->renderer = renderer;
	return true;
}
bool ComaDevice::setWindowRenderer(ComaWindow* window, ComaRenderer* renderer)
{
	if (!setWindow(window))
		return false;
	if (!setRenderer(renderer))
		return false;
	return true;
}

bool ComaDevice::initDevice()
{
	if (initialized)
		return false;
	if (!initWindow())
		return false;
	if (!initRenderer())
		return false;
	initialized = true;
	return true;
}
bool ComaDevice::initDevice(HINSTANCE hInstance)
{
	if (initialized)
		return false;
	if (!initWindow(hInstance))
		return false;
	if (!initRenderer())
		return false;
	if (!initManagers())
		return false;
	if (!initOthers())
		return false;
	initialized = true;
	return true;
}

bool ComaDevice::run()
{
	if (running || !initialized || !window || !renderer)
		return false;
	running = true;

	if (!renderer->isRunning())
		renderer->run();

	if (!window->isRunning())
		window->run();

	return true;
}

bool ComaDevice::initWindow()
{
	if (!window)
		return false;
	if (!window->isCreated())
		if (!window->createWindow())
			return false;

	window->setEventListener(WindowEvent::DESTROY,			BIND(ComaDevice::windowDestroyListener			));
	window->setEventListener(WindowEvent::MINIMIZED,		BIND(ComaDevice::windowMinimizeListener			));
	window->setEventListener(WindowEvent::RESTORED,			BIND(ComaDevice::windowRestoreListener			));
	window->setEventListener(WindowEvent::RESIZE,			BIND(ComaDevice::windowResizeListener			));
	window->setEventListener(WindowEvent::ENTER_RESIZEMOVE, BIND(ComaDevice::windowEnterResizeMoveListener	));
	window->setEventListener(WindowEvent::EXIT_RESIZEMOVE,	BIND(ComaDevice::windowExitResizeMoveListener	));
	window->setEventListener(WindowEvent::UPDATE,			BIND(ComaDevice::windowUpdateListener			));
	return true;
}
bool ComaDevice::initWindow(HINSTANCE hInstance)
{
	if (window)
		return initWindow();

	window = new ComaWindow(hInstance);
	return initWindow();
}

bool ComaDevice::initRenderer()
{
	if (!window)
		return false;

	if (!renderer)
		renderer = new ComaRenderer();

	if (!renderer->isInitialized())
		if (!renderer->initRenderer(window->getWindow()))
			return false;

	renderer->setEventListener(RendererEvent::UPDATE, BIND(ComaDevice::rendererUpdateListener));
	renderer->setEventListener(RendererEvent::RENDER, BIND(ComaDevice::rendererRenderListener));
		
	return true;
}
bool ComaDevice::initManagers()
{
	resourceManager = new ResourceManager();
	return true;
}
bool ComaDevice::initOthers()
{
	Bitmap::setRenderer(renderer);
	return true;
}

void ComaDevice::windowDestroyListener(Event* event)
{
	
}
void ComaDevice::windowMinimizeListener(Event* event)
{
	renderer->pause();
}
void ComaDevice::windowRestoreListener(Event* event)
{
	renderer->run();
}
void ComaDevice::windowEnterResizeMoveListener(Event* event)
{
	renderer->pause();
}
void ComaDevice::windowExitResizeMoveListener(Event* event)
{
	renderer->resetSize();
	renderer->run();
}
void ComaDevice::windowUpdateListener(Event* event)
{
	renderer->update();
}
void ComaDevice::windowResizeListener(Event* event)
{
	if (!window->isResizing() && !window->isMinimized())
		renderer->resetSize();
}

void ComaDevice::rendererUpdateListener(Event* event)
{

}
void ComaDevice::rendererRenderListener(Event* event)
{

}
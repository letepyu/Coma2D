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
* filename	ComaRenderer.cpp
* fileinfo	�׷��� ������ ��� Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "ComaRenderer.h"
#include "RendererEvent.h"
COMA_USING_NS


ComaRenderer::ComaRenderer()
	:initialized(false), running(false), deltaTime(0.0), fps(0.0f), frameCount(0), factory(nullptr), renderTarget(nullptr)
{
	timer = new RenderTimer();
	backgroundColor = D2D1::ColorF(0.0f, 0.0f, 0.0f);
	maxFrameTime = 0.05f;
	minFrameTime = 0.01f;
}


ComaRenderer::~ComaRenderer()
{
	dispatchEvent(new RendererEvent(RendererEvent::UNLOAD_RESOURCES_REQ, this));
	if (factory)factory->Release();
	if (renderTarget)renderTarget->Release();
	delete timer;
}

bool ComaRenderer::initRenderer(HWND hWnd)
{
	if (initialized)
		return false;

	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory) != S_OK)
		return false;
	if (!createRenderTarget(hWnd))
		return false;

	timer->reset();

	targetWindow = hWnd;
	initialized = true;
	return true;
}

bool ComaRenderer::createRenderTarget(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	if (factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom), D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&renderTarget
		) != S_OK)
		return false;
	dispatchEvent(new RendererEvent(RendererEvent::RENDER_TARGET_CREATED, this));
	return true;
}
void ComaRenderer::releaseRenderTarget()
{
	if (renderTarget)
	{
		dispatchEvent(new RendererEvent(RendererEvent::UNLOAD_RESOURCES_REQ, this));
		renderTarget->Release();
		dispatchEvent(new RendererEvent(RendererEvent::RENDER_TARGET_RELEASED, this));
	}
}

bool ComaRenderer::run()
{
	if (!initialized || running)
		return false;
	timer->start();
	running = true;
	dispatchEvent(new RendererEvent(RendererEvent::RUN, this));
	return true;
}
bool ComaRenderer::pause()
{
	if (!initialized || !running)
		return false;
	timer->stop();
	running = false;
	dispatchEvent(new RendererEvent(RendererEvent::PAUSED, this));
	return true;
}
bool ComaRenderer::update()
{
	if (!initialized || !running)
		return false;

	//Time Process
	timer->tick();
	deltaTime = timer->getDeltaTime();
	if (deltaTime > maxFrameTime)
		deltaTime = maxFrameTime;
	else if (deltaTime < minFrameTime)
	{
		Sleep((DWORD)((minFrameTime-deltaTime)*1000));
		deltaTime = minFrameTime;
	}
	fps = 1 / (float)deltaTime;
	dispatchEvent(new RendererEvent(RendererEvent::UPDATE, this));

	//RenderProcess
	renderTarget->BeginDraw();
	renderTarget->Clear(backgroundColor);

	dispatchEvent(new RendererEvent(RendererEvent::RENDER, this));

	if (renderTarget->EndDraw() != S_OK)
	{
		restoreDevice();
		if (renderTarget->EndDraw() != S_OK)
		{
			return false;
		}
	}
	

	frameCount++;
	return true;
}
bool ComaRenderer::resetSize()
{
	if (!initialized)
		return false;
	RECT rect;
	GetClientRect(targetWindow, &rect);

	if(renderTarget->Resize(D2D1::SizeU(rect.right, rect.bottom)) == S_OK)
		return true;
	return false;
}
void ComaRenderer::restoreDevice()
{
	pause();
	releaseRenderTarget();
	Sleep(100);
	dispatchEvent(new RendererEvent(RendererEvent::LOAD_RESOURCE_REQ, this));
	createRenderTarget(targetWindow);
	run();
}
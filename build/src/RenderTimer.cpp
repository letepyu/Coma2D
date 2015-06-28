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
* filename	RenderTimer.cpp
* fileinfo	�������� Ÿ�̸� ��ƿ��Ƽ Ŭ���� ���� ����
* author	����� (Heonyang Ju)
*/

#include "RenderTimer.h"


RenderTimer::RenderTimer()
	:baseTime(0), pausedTime(0), stopTime(0), prevTime(0), currentTime(0), secondsPerCount(0), deltaTime(0), running(false)
{
	__int64 freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	secondsPerCount = 1.0 / freq;
}


RenderTimer::~RenderTimer()
{
}

void RenderTimer::reset()
{
	running = false;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	baseTime = currentTime;
	stopTime = currentTime;
	prevTime = currentTime;
	pausedTime = 0;
}

void RenderTimer::start()
{
	if (running)
		return;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	pausedTime += currentTime - stopTime;

	prevTime = currentTime;

	running = true;
}

void RenderTimer::stop()
{
	if (!running)
		return;
	
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	stopTime = currentTime;
	running = false;
}

void RenderTimer::tick()
{
	if (!running)
		return;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	deltaTime = (currentTime - prevTime) * secondsPerCount;
	prevTime = currentTime;
}

double RenderTimer::getTotalTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	return (currentTime - baseTime)*secondsPerCount;
}

double RenderTimer::getRunningTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	if (!running)
		return (currentTime - baseTime - pausedTime - (currentTime-stopTime))*secondsPerCount;
	return (currentTime - baseTime - pausedTime)*secondsPerCount;
}

double RenderTimer::getPausedTime()
{
	if (!running)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		return (pausedTime + (currentTime - stopTime))*secondsPerCount;
	}
	return pausedTime*secondsPerCount;
}

double RenderTimer::getDeltaTime()
{
	return deltaTime;
}
#pragma once
#include <Windows.h>
class RenderTimer
{
public:
	RenderTimer();
	~RenderTimer();

public:
	void reset();
	void start();
	void stop();
	void tick();

	double getDeltaTime();
	double getTotalTime();
	double getRunningTime();
	double getPausedTime();

public:
	bool isRunning(){ return running; }

private:
	bool running;
	
	double secondsPerCount;
	double deltaTime;

	__int64 baseTime; // ���� �ð�
	__int64 prevTime; // ���� �ð�
	__int64 currentTime; // ���� �ð�

	__int64 stopTime; // ���� ������ �ð�
	__int64 pausedTime; // ���� ���� �ð�

};


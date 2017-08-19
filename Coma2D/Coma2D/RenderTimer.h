/*
* filename	RenderTimer.h
* fileinfo	�������� Ÿ�̸� ��ƿ��Ƽ Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include <Windows.h>
class RenderTimer
{
public:
	RenderTimer();
	~RenderTimer();

public:
	void Reset();
	void Start();
	void Stop();
	void Tick();

	double GetDeltaTime();
	double GetTotalTime();
	double GetRunningTime();
	double GetPausedTime();

public:
	bool IsRunning(){ return running_; }

private:
	bool running_;
	
	double secondsPerCount_;
	double deltaTime_;

	__int64 baseTime_; // ���� �ð�
	__int64 prevTime_; // ���� �ð�
	__int64 currentTime_; // ���� �ð�

	__int64 stopTime_; // ���� ������ �ð�
	__int64 pausedTime_; // ���� ���� �ð�

};


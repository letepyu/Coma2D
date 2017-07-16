/*
* filename	InputManager.h
* fileinfo	����� �Է� ���� Ŭ���� ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Manager.h"
#include "Gamepad.h"

COMA_NS_BEGIN

class InputManager :
	public Manager
{
public:
	InputManager();
	virtual ~InputManager();

public:
	bool CreateInputEvent(UINT uMsg, WPARAM wParam, LPARAM lParam); //�̺�Ʈ�� ó������ ���� ���, false�� ��ȯ�Ѵ�.
	bool IsKeyDown(unsigned int keyCode) const { return pressedKey_[keyCode]; }
	bool IsLeftMouseDowned() const { return leftMouseDowned_; }
	bool IsRightMouseDowned() const { return rightMouseDowned_; }
	bool IsMiddleMouseDowned() const { return middleMouseDowned_; }
	Point GetMousePosition() const { return mousePosition_; }

	void UpdateGamepad(double deltaTime);
	Gamepad* GetGamepad(UINT index) const;

private:
	bool pressedKey_[256];
	char charIn_;
	std::string inputString_;

	Point mousePosition_;
	bool leftMouseDowned_;
	bool rightMouseDowned_;
	bool middleMouseDowned_;

	Gamepad* gamePads_[MAX_CONTROLLERS];

	void UpdateMousePosition(LPARAM lParam);
	void UpdateGamepadConnected();
};

COMA_END
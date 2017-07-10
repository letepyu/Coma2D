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
	bool createInputEvent(UINT uMsg, WPARAM wParam, LPARAM lParam); //�̺�Ʈ ó���� �߻����� ���� ���, false�� ��ȯ�Ѵ�.
	bool isKeyDown(unsigned int keyCode){ return pressedKey[keyCode]; }
	bool isLeftMouseDowned(){ return leftMouseDowned; }
	bool isRightMouseDowned(){ return rightMouseDowned; }
	bool isMiddleMouseDowned(){ return middleMouseDowned; }
	Point getMousePosition(){ return mousePosition; }

	void updateGamepad(double deltaTime);
	Gamepad* getGamepad(UINT index){ if (index > MAX_CONTROLLERS - 1) return gamePads[MAX_CONTROLLERS - 1]; return gamePads[index]; }

private:
	bool pressedKey[256];
	char charIn;
	std::string inputString;

	Point mousePosition;
	bool leftMouseDowned;
	bool rightMouseDowned;
	bool middleMouseDowned;

	Gamepad* gamePads[MAX_CONTROLLERS];

	void updateMousePosition(LPARAM lParam);

	void updateGamepadConnected();

};

COMA_END
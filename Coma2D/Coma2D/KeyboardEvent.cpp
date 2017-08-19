/*
* filename	KeyboardEvent.cpp
* fileinfo	Ű���� �̺�Ʈ ���� ����
* author	����� (Heonyang Ju)
*/

#include "KeyboardEvent.h"

COMA_USING_NS

const std::string KeyboardEvent::KEY_DOWN = "keyboard_keyDown";
const std::string KeyboardEvent::KEY_UP = "keyboard_keyUp";
const std::string KeyboardEvent::KEY_CHAR = "keyboard_keyChar";

KeyboardEvent::KeyboardEvent(const std::string& type, unsigned int charCode, unsigned int keyCode, bool altKey, bool ctrlKey, bool shiftKey)
	:Event(type), charCode_(charCode), keyCode_(keyCode), altKey_(altKey), ctrlKey_(ctrlKey), shiftKey_(shiftKey)
{
}


KeyboardEvent::~KeyboardEvent()
{
}

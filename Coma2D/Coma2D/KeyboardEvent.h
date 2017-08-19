/*
* filename	KeyboardEvent.h
* fileinfo	Ű���� �̺�Ʈ ��� ����
* author	����� (Heonyang Ju)
*/

#pragma once
#include "Event.h"

COMA_NS_BEGIN

class KeyboardEvent :
	public Event
{
public:
	KeyboardEvent(const std::string& type, unsigned int charCode = 0, unsigned int keyCode = 0, bool altKey = false, bool ctrlKey = false, bool shiftKey = false);
	virtual ~KeyboardEvent();

public:
	static const std::string KEY_DOWN;
	static const std::string KEY_UP;
	static const std::string KEY_CHAR;

public:
	unsigned int GetCharCode() const { return charCode_; }
	unsigned int GetKeyCode() const { return keyCode_; }

	bool GetAltKey() const { return altKey_; }
	bool GetCtrlKey() const { return ctrlKey_; }
	bool GetShiftKey() const { return shiftKey_; }

private:
	unsigned int charCode_;
	unsigned int keyCode_;
	unsigned int keyLocation_;

	bool altKey_;
	bool ctrlKey_;
	bool shiftKey_;
};

COMA_END
#pragma once

namespace Keys
{
	enum class Keys
	{
		NONE = 0,
		BACKSPACE = 8,
		TAB = 9,
		RETURN = 13,
		ESCAPE = 27,
		SPACE = 32,
		EXCLAMATION = 33,
		QUOTATION = 34,
		HASH = 35,
		DOLLAR = 36,
		PERCENT = 37,
		AMPERSAND = 38,
		APOSTROPHE = 39,
		LEFT_BRACKET = 40,
		RIGHT_BRACKET = 41,
		ASTERISK = 42,
		ADD = 43,
		COMMA = 44,
		SUBTRACT = 45,
		PERIOD = 46,
		FORWARD_SLASH = 47,
		ZERO = 48,
		ONE = 49,
		TWO = 50,
		THREE = 51,
		FOUR = 52,
		FIVE = 53,
		SIX = 54,
		SEVEN = 55,
		EIGHT = 56,
		NINE = 57,
		COLON = 58,
		SEMI_COLON = 59,
		LEFT_CHEVRON = 60,
		EQUALS = 61,
		RIGHT_CHEVRON = 62,
		QUESTION_MARK = 63,
		ASPERAND = 64,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		SQUARE_BRACKET_LEFT = 91,
		BACKSLASH = 92,
		SQUARE_BRACKET_RIGHT = 93,
		CARET = 94,
		UNDERSCORE = 95,
		GRAVE = 96,
		//Where lower-case characters should be
		LEFT_BRACE = 123,
		PIPE = 124,
		RIGHT_BRACE = 125,
		TILDE = 126,
		DEL = 127
	};

	enum class SpecialKeys
	{
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		LEFT_ARROW,
		UP_ARROW,
		RIGHT_ARROW,
		DOWN_ARROW,
		PAGE_UP,
		PAGE_DOWN,
		HOME,
		END,
		INSERT,
		LEFT_SHIFT,
		RIGHT_SHIFT,
		LEFT_CONTROL,
		RIGHT_CONTROL,
		LEFT_ALT,
		NONE
	};

	enum class MouseKeys
	{
		LEFT_MOUSE = 0,
		MIDDLE_MOUSE = 1,
		RIGHT_MOUSE = 2,
		NONE
	};

	enum class MouseMovement
	{
		NONE,
		PASSIVE,
		BUTTON_DOWN
	};

	inline SpecialKeys CastToSpecialKey(const int key)
	{
		switch (key)
		{
		case 1:
			return SpecialKeys::F1;
		case 2:
			return SpecialKeys::F2;
		case 3:
			return SpecialKeys::F3;
		case 4:
			return SpecialKeys::F4;
		case 5:
			return SpecialKeys::F5;
		case 6:
			return SpecialKeys::F6;
		case 7:
			return SpecialKeys::F7;
		case 8:
			return SpecialKeys::F8;
		case 9:
			return SpecialKeys::F9;
		case 10:
			return SpecialKeys::F10;
		case 11:
			return SpecialKeys::F11;
		case 12:
			return SpecialKeys::F12;
		case 100:
			return SpecialKeys::LEFT_ARROW;
		case 101:
			return SpecialKeys::UP_ARROW;
		case 102:
			return SpecialKeys::RIGHT_ARROW;
		case 103:
			return SpecialKeys::DOWN_ARROW;
		case 104:
			return SpecialKeys::PAGE_UP;
		case 105:
			return SpecialKeys::PAGE_DOWN;
		case 106:
			return SpecialKeys::HOME;
		case 108:
			return SpecialKeys::INSERT;
		case 112:
			return SpecialKeys::LEFT_SHIFT;
		case 113:
			return SpecialKeys::RIGHT_SHIFT;
		case 114:
			return SpecialKeys::LEFT_CONTROL;
		case 115:
			return SpecialKeys::RIGHT_CONTROL;
		case 116:
			return SpecialKeys::LEFT_ALT;
		default:
			return SpecialKeys::NONE;
		}
	}

	inline Keys CastToKey(unsigned char key)
	{
		if (key >= 97 && key <= 122)
		{
			key -= 32;
		}
		return static_cast<Keys>(key);
	}

	inline MouseKeys CastToMouseButton(const int key)
	{
		return static_cast<MouseKeys>(key);
	}
}
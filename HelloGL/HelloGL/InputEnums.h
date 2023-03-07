#pragma once

namespace Keys
{
	enum Keys
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
		a = 97,
		b = 98,
		c = 99,
		d = 100,
		e = 101,
		f = 102,
		g = 103,
		h = 104,
		i = 105,
		j = 106,
		k = 107,
		l = 108,
		m = 109,
		n = 110,
		o = 111,
		p = 112,
		q = 113,
		r = 114,
		s = 115,
		t = 116,
		u = 117,
		v = 118,
		w = 119,
		x = 120,
		y = 121,
		z = 122,
		LEFT_BRACE = 123,
		PIPE = 124,
		RIGHT_BRACE = 125,
		TILDE = 126,
		DEL = 127,
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
		LEFT_ALT
	};

	inline Keys GetSpecialKeyFromInt(const int key)
	{
		switch (key)
		{
		case 1:
			return F1;
		case 2:
			return F2;
		case 3:
			return F3;
		case 4:
			return F4;
		case 5:
			return F5;
		case 6:
			return F6;
		case 7:
			return F7;
		case 8:
			return F8;
		case 9:
			return F9;
		case 10:
			return F10;
		case 11:
			return F11;
		case 12:
			return F12;
		case 100:
			return LEFT_ARROW;
		case 101:
			return UP_ARROW;
		case 102:
			return RIGHT_ARROW;
		case 103:
			return DOWN_ARROW;
		case 104:
			return PAGE_UP;
		case 105:
			return PAGE_DOWN;
		case 106:
			return HOME;
		case 108:
			return INSERT;
		case 112:
			return LEFT_SHIFT;
		case 113:
			return RIGHT_SHIFT;
		case 114:
			return LEFT_CONTROL;
		case 115:
			return RIGHT_CONTROL;
		case 116:
			return LEFT_ALT;
		default:
			return NONE;
		}
	}

	inline Keys CastToKey(unsigned char key)
	{
		return static_cast<Keys>(key);
	}
}

namespace KeyState
{
	enum KeyState
	{
		NONE,
		DOWN,
		UP
	};
}
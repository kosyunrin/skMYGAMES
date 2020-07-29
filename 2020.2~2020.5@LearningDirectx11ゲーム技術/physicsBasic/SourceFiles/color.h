#pragma once

typedef unsigned char BYTE;

class Color
{
private:
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;

public:
	Color(BYTE r, BYTE g, BYTE b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	Color(BYTE r, BYTE g, BYTE b, BYTE a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	BYTE GetR() { return r; }
	BYTE GetG() { return g; }
	BYTE GetB() { return b; }
	BYTE GetA() { return a; }
};

namespace Colors
{
	const Color White(255, 255, 255, 255);
	const Color Black(0, 0, 0, 255);
	const Color Blue(0, 0, 255, 255);
	const Color Green(0, 255, 0, 255);
	const Color Red(255, 0, 0, 255);
}

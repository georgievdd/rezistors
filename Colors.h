#pragma once
#include "Libs.h"
class Color {
public:
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 1;

	Color() {}

	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color correction() {
		return Color(pow(r, 1 / 2.2), pow(g, 1 / 2.2), pow(b, 1 / 2.2), pow(a, 1 / 2.2));
	}

	Color changea(float a) {
		return Color(r, g, b, a);
	}

	Color operator * (float c) {
		return Color(r * c, g * c, b * c, a);
	}

	Color operator * (Color color) {
		return Color(r * color.r, g * color.g, b * color.b, a);
	}

	Color operator + (Color color) {
		return Color(r + color.r, g + color.g, b + color.b, a);
	}

	bool operator ==(Color color) {
		return this->r == color.r && this->g == color.g && this->b == color.b;
	}

	bool operator !=(Color color) {
		return this->r != color.r || this->g != color.g || this->b != color.b;
	}

};

Color black(0, 0, 0);
Color red(1, 0, 0);
Color green(0, 1, 0);
Color blue(0, 0, 1);
Color yellow(1, 1, 0);
Color gray(0.51, 0.54, 0.59);
Color cube_color(0.78, 0, 0.4, 0.3);
Color white(1, 1, 1);
Color sp(0.26, 0.71, 0.52);
Color buttoncolor(0.27, 0.29, 0.08);
Color defaultcolor(0.25, 0.63, 0.38);
Color but_color(0.25, 0.26, 0.23, 0.5);
Color blue_vers(0.18, 0.18, 0.27);
Color background(0.9, 0.9, 0.9);
Color rezistor_col(0.69, 0.17, 0.2);
Color battery_col(0.25, 0.63, 0.38);
Color line_col(0.1, 0.1, 0.1);
Color eraser_col(0.37, 0.42, 0.40);
Color rez_infofield_col(0.69, 0.67, 0.61);
Color delete_col = red;
Color addwin_col(0.24, 0.39, 0.53);


inline void SetColor(Color color) {
	glColor4f(color.r, color.g, color.b, color.a);
}

Color colrand() {
	float r = (float)(10 + rand() % 91) / 100;
	float g = (float)(10 + rand() % 91) / 100;
	float b = (float)(10 + rand() % 91) / 100;
	return Color(r, g, b);
}
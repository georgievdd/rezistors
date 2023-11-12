#pragma once
#include "Libs.h"

class Button {
public:
	float x1, x2, y1, y2;
	float x1_s, y1_s, x2_s, y2_s;
	bool pressstatus, rezult;
	Color color;

	Button() {}
	Button(float x1, float y1, float x2, float y2, Color color) {
		this->x1 = x1_s = x1;
		this->x2 = x2_s = x2;
		this->y1 = y1_s = y1;
		this->y2 = y2_s = y2;
		this->color = color;
		pressstatus = false;
	}

	void show() {
		SetColor(color);
		DrawSquare(x1_s, y1_s, x2_s, y2_s);
	}

	bool IsCursorOn() {
		rezult = cursor.PosXOnMap >= x1 && cursor.PosXOnMap <= x2 && cursor.PosYOnMap >= y1 && cursor.PosYOnMap <= y2;
		if (rezult && cursor.press) pressstatus = true;
		if (!cursor.press) pressstatus = false;
		return rezult;
	}

	bool IsKlickOn() {
		return IsCursorOn() && cursor.press;
	}

	bool IsUnklickOn() {
		return cursor.LeftKlickPosX >= x1 && cursor.LeftKlickPosX <= x2 && cursor.LeftKlickPosY >= y1 && cursor.LeftKlickPosY <= y2 &&
			IsCursorOn() && cursor.unpress;
	}

	bool KlickOnWas() {
	}
};
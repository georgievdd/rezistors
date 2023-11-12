#pragma once
#include "Libs.h"
#include "figures.h"
#include "List.h"
#include "TextInOut.h"

class Rezistor {
public:
	String value = "1";
	Int_list l_index;
	Int_list r_index;
	bool pressstatus = false, rezult;
	bool enabletomove = true;
	bool l_conectflag = false;
	int l_con_flag_in;
	bool r_conectflag = false;
	int r_con_flag_in;
	static bool enabletoinputtext;
	bool enabletosetinfo = false;
	static float h, l, r0;
	float r1 = r0;
	float r2 = r0;
	float x1, x2, y1, y2;
	float ix1, ix2, iy1, iy2;
	float fix1, fix2, fiy1, fiy2;
	Color color = rezistor_col;
	static Color c_color;
	Color c_col1 = c_color;
	Color c_col2 = c_color;
	Color ib_col = rez_infofield_col;

	Rezistor() {}

	Rezistor(vec pos) {
		x1 = pos.x - l / 2;
		x2 = pos.x + l / 2;
		y1 = pos.y - h / 2;
		y2 = pos.y + h / 2;
		ix1 = (x1 + x2) / 2 - 0.03;
		ix2 = (x1 + x2) / 2 + 0.03;
		iy1 = (y1 + y2) / 2 - 0.01;
		iy2 = (y1 + y2) / 2 + 0.01;
		fix1 = x1;
		fix2 = x2;
		fiy1 = y2 + 0.03;
		fiy2 = y2 + 0.07;
	}

	void center(float dx, float dy) {
		x1 += dx;
		x2 += dx;
		y1 += dy;
		y2 += dy;
		ix1 += dx;
		ix2 += dx;
		iy1 += dy;
		iy2 += dy;
		fix1 += dx;
		fix2 += dx;
		fiy1 += dy;
		fiy2 += dy;
	}

	friend ostream& operator<<(ostream& out, Rezistor& other) {
		SetColor(other.color);
		DrawSquare(other.x1, other.y1, other.x2, other.y2);
		SetColor(black);
		glLineWidth(10);
		glBegin(GL_LINE_LOOP);
		glVertex2f(other.x1, other.y1);
		glVertex2f(other.x2, other.y1);
		glVertex2f(other.x2, other.y2);
		glVertex2f(other.x1, other.y2);
		glEnd();
		glPushMatrix();
		glTranslatef(0, 0, -0.000000000001);
		SetColor(other.c_col1);
		DrawCircle(other.x1 + other.r0, other.y1 + h / 2, other.r1);
		SetColor(other.c_col2);
		DrawCircle(other.x2 - other.r0, other.y1 + h / 2, other.r2);
		SetColor(other.ib_col);
		DrawSquare(other.ix1, other.iy1, other.ix2, other.iy2);
		if (other.enabletosetinfo) {
			print(other.fix1, other.fiy2, other.value, black);
		}
		glPopMatrix();
		return out;
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

	bool IsKlickOnR() {
		return cursor.RightKlickPosX >= x1 && cursor.RightKlickPosX <= x2 && cursor.RightKlickPosY >= y1 
			&& cursor.RightKlickPosY <= y2 && cursor.pressR;
	}

	bool IsUnklickOn() {
		return cursor.LeftKlickPosX >= x1 && cursor.LeftKlickPosX <= x2 && cursor.LeftKlickPosY >= y1 && cursor.LeftKlickPosY <= y2 &&
			IsCursorOn() && cursor.unpress;
	}

	bool IsCursorOnCircle(int a) {
		if (a == 0)
			return (x1 + r1 - cursor.PosXOnMap) * (x1 + r1 - cursor.PosXOnMap) +
			(y1 + h / 2 - cursor.PosYOnMap) * (y1 + h / 2 - cursor.PosYOnMap) <= r1 * r1;
		return (x2 - r2 - cursor.PosXOnMap) * (x2 - r2 - cursor.PosXOnMap) +
			(y1 + h / 2 - cursor.PosYOnMap) * (y1 + h / 2 - cursor.PosYOnMap) <= r2 * r2;
	}
	
	bool IsKlickOnCircle(int a) {
		return IsCursorOnCircle(a) && cursor.unpress;
	}

	bool IsCursorOnInfoButton() {
		return cursor.PosXOnMap >= ix1 && cursor.PosXOnMap <= ix2 && cursor.PosYOnMap >= iy1 && cursor.PosYOnMap <= iy2;
	}

	bool IsCursorUnklickInfoButton() {
		return IsCursorOnInfoButton() && cursor.unpress;
	}

	bool IsCursorOnInfoField() {
		return cursor.PosXOnMap >= fix1 && cursor.PosXOnMap <= fix2 && cursor.PosYOnMap >= fiy1 && cursor.PosYOnMap <= fiy2;
	}

	bool IsCursorUnklickInfoField() {
		return IsCursorOnInfoField() && cursor.unpress;
	}
};
float Rezistor::l = 0.2;
float Rezistor::h = 0.1;
float Rezistor::r0 = Rezistor::h / 6;
bool  Rezistor::enabletoinputtext = false;
Color Rezistor::c_color = rezistor_col * 0.9;

typedef gdd_list::_list<Rezistor> Rezistor_list;
typedef gdd_list::__list<Rezistor>* Rezistor__ptr;



class Battery {
public:
	bool pressstatus = false, rezult;
	bool enabletomove = true;
	static float h, l, r0;
	float x1, x2, y1, y2;
	float r1 = r0, r2 = r0;
	Color color = battery_col;
	Color c_color = battery_col * 0.9;
	Color c_col1 = c_color;
	Color c_col2 = c_color;

	Battery() {}

	Battery(vec pos) {
		x1 = pos.x - l / 2;
		x2 = pos.x + l / 2;
		y1 = pos.y - h / 2;
		y2 = pos.y + h / 2;
	}

	void show() {
		SetColor(color);
		DrawSquare(x1, y1, x2, y2);
		SetColor(black);
		glLineWidth(4);
		glPushMatrix();
		glTranslatef(0, 0, -0.000001);
		glBegin(GL_LINES);
		glVertex2f(x2 - l / 4, y2 - h / 2);
		glVertex2f(x2, y2 - h / 2);
		glVertex2f(x2 - l / 8, y1 + h / 5);
		glVertex2f(x2 - l / 8, y2 - h / 5);
		glVertex2f(x1, y1 + h / 2);
		glVertex2f(x1 + l / 4, y1 + h / 2);

		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
		glEnd();
		glTranslatef(0, 0, -0.000001);
		SetColor(c_col1);
		DrawCircle(x1, y2, r1);
		SetColor(c_col2);
		DrawCircle(x2, y2, r2);
		glPopMatrix();
	}

	void center(vec pos) {
		x1 = pos.x - l / 2;
		x2 = pos.x + l / 2;
		y1 = pos.y - h / 2;
		y2 = pos.y + h / 2;
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

	bool IsKlickOnR() {
		return cursor.RightKlickPosX >= x1 && cursor.RightKlickPosX <= x2 && cursor.RightKlickPosY >= y1
			&& cursor.RightKlickPosY <= y2 && cursor.pressR;
	}

	bool IsUnklickOn() {
		return cursor.LeftKlickPosX >= x1 && cursor.LeftKlickPosX <= x2 && cursor.LeftKlickPosY >= y1 && cursor.LeftKlickPosY <= y2 &&
			IsCursorOn() && cursor.unpress;
	}

	bool IsCursorOnCircle(int a) {
		if (a == 0)
			return (x1 - cursor.PosXOnMap) * (x1 - cursor.PosXOnMap) +
			(y2 - cursor.PosYOnMap) * (y2 - cursor.PosYOnMap) <= r1 * r1;
		return (x2 - cursor.PosXOnMap) * (x2 - cursor.PosXOnMap) +
			(y2 - cursor.PosYOnMap) * (y2 - cursor.PosYOnMap) <= r2 * r2;
	}

	bool IsKlickOnCircle(int a) {
		return IsCursorOnCircle(a) && cursor.unpress;
	}
};
float Battery::l = 0.2;
float Battery::h = 0.1;
float Battery::r0 = Battery::h / 8;
typedef Battery* Battery_ptr;


struct xy {
	float x, y;
	xy() {}
	xy(float x, float y) { this->x = x; this->y = y; }
};
typedef gdd_list::__list<xy>* xy_ptr;

class Line {
private:
	inline float distance(xy p) {
		return sqrt((cursor.PosXOnMap - p.x) * (cursor.PosXOnMap - p.x) + (cursor.PosYOnMap - p.y) * (cursor.PosYOnMap - p.y));
	}
public:
	gdd_list::_list<xy> points;
	Color color = line_col;
	bool enable = true;
	float static line_len;
	int index = -1;
	
	Rezistor__ptr rc11 = nullptr;
	Rezistor__ptr rc12 = nullptr;
	Rezistor__ptr rc21 = nullptr;
	Rezistor__ptr rc22 = nullptr;
	Battery_ptr   rb1  = nullptr;
	Battery_ptr   rb2  = nullptr;

	Line() {}
	Line(xy point) {
		points.append(point);
	}

	friend ostream& operator <<(ostream& out, Line& other) {
		xy_ptr ptr = other.points.link_begin;
		if (!other.points.len) return out;
		SetColor(other.color);
		glLineWidth(5);
		glPushMatrix();
		glTranslatef(0, 0, -0.000000001);
		glBegin(GL_LINE_STRIP);
		do {
			glVertex2f(ptr->value.x, ptr->value.y);
			ptr = ptr->link_next;
		} while (ptr != nullptr);
		glEnd();
		glPopMatrix();
		return out;
	}

	void append(xy point) {
		points.append(point);
	}

	void draw() {
		if (distance(points.link_end->value) > line_len)
			points.append(xy(cursor.PosXOnMap, cursor.PosYOnMap));
	}

	bool IsCursorOn() {
		xy_ptr ptr = points.link_begin;
		if (!points.len) return false;
		do {
			if (distance(ptr->value) < line_len) return true;
			ptr = ptr->link_next;
		} while (ptr != nullptr);
	}
};
typedef gdd_list::_list<Line> Line_list;
typedef gdd_list::__list<Line>* Line_ptr;
float Line::line_len = 0.015;
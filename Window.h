#pragma once
#include "Libs.h"
#include "user.h"
#include "Button.h"
#include "Elements.h"
#include "Logic.h"


float Wall_Distance = 0.005, MIN = 0.00001;
float Lx = -1 / kx, Rx = 1 / kx;
float a = 0.1;

Button StartButton(1.5, 0.85 + Wall_Distance, Rx - Wall_Distance, 1 - Wall_Distance, red);
Button RezultField(1, 0.94 + Wall_Distance, 1.5 - Wall_Distance, 1 - Wall_Distance, gray);
Button PanelButton(Lx + Wall_Distance, 1 - Wall_Distance - a, Lx + Wall_Distance + a, 1 - Wall_Distance, background);
Button AddRezistor(-1.765, 0.6, -1.565, 0.7, rezistor_col);
Button AddBatary(-1.765, 0.4, -1.565, 0.5, battery_col);
Button Eraser(-1.765, 0.2, -1.565, 0.3, eraser_col);
Button Next(1.45, -0.8, 1.55, -0.7, blue_vers);
Button Previous(1.15, -0.8, 1.25, -0.7, blue_vers);
Button Delete(1, -0.8, 1.1, -0.7, delete_col);
Button AddWindow(1.6, -0.8, 1.7, -0.7, addwin_col);

Rezistor* rezistorforstringinput;
bool ShowPanelWithElementsFlag = true;
bool EraserMode = false;

int Window_Index = 0;

class Window {
private:
	vec baterypos0 = vec(-0, -0.5, 0);
	vec rezistorpos0 = vec((AddRezistor.x1 + AddRezistor.x2) / 2, (AddRezistor.y1 + AddRezistor.y2) / 2, 0);
	public: String rezult_string = "";
private :
	Rezistor_list rezistor_list;
	Battery battery = Battery(baterypos0);
	Line_list line_list;

	bool BatteryInit = false;
	bool not_append_yet = false;
	void ButtonEventHaldingWindow();
	void RezistorEventHalding();
	void BatteryEventHalding();
	void LineEventHalding();
	void ShowUserButtons();
	void PanelWithElementsEventHalding();
	static void ShowPanelWithElements();
	static void ShowPanelButton();
	void ShowDefolt();
	String get_rezult();
public:
	void Delete_All();
	void show();
};
typedef gdd_list::_list<Window> Window_list;
Window_list window_list;
void Window::ButtonEventHaldingWindow() {
	if (PanelButton.IsUnklickOn()) ShowPanelWithElementsFlag = !ShowPanelWithElementsFlag;

	if (StartButton.IsCursorOn()) StartButton.color = red * 0.9;
	else StartButton.color = red;

	if (StartButton.IsUnklickOn()) rezult_string = get_rezult();
	PanelWithElementsEventHalding();
}
void Window::RezistorEventHalding() {
	int ptr_index, klick_index, ptr_flag; ///
	klick_index = -1;
	Rezistor__ptr ptr = rezistor_list.link_begin;
	if (!rezistor_list.len) return;
	ptr_index = 0;
	if (battery.pressstatus) return;
	do {

		if (klick_index == -1) {
			ptr_flag = false;

			if (ptr->value.IsCursorOnInfoButton()) {
				ptr->value.ib_col = rez_infofield_col * 0.5;
				if (ptr->value.IsCursorUnklickInfoButton()) ptr->value.enabletosetinfo = !ptr->value.enabletosetinfo;
			}
			else ptr->value.ib_col = rez_infofield_col;

			if (ptr->value.IsCursorUnklickInfoField()) {
				rezistorforstringinput->enabletoinputtext = true;
				rezistorforstringinput = &ptr->value;
			}


			if (ptr->value.IsCursorOnCircle(0)) ptr->value.r1 = ptr->value.r0 * 2;
			else ptr->value.r1 = ptr->value.r0;
			if (ptr->value.IsCursorOnCircle(1)) ptr->value.r2 = ptr->value.r0 * 2;
			else ptr->value.r2 = ptr->value.r0;
			if (ptr->value.IsKlickOnCircle(0)) {
				ptr->value.c_col1 = black;
				ptr->value.enabletomove = false;

				if (line_list.len && line_list.link_end->value.enable) {
					line_list.link_end->value.enable = false;
					line_list.link_end->value.rc21 = ptr;
					return;
				}

				line_list.append(Line(xy(cursor.PosXOnMap, cursor.PosYOnMap)));
				line_list.link_end->value.rc11 = ptr;
				return;
			}
			if (ptr->value.IsKlickOnCircle(1)) {
				ptr->value.c_col2 = black;
				ptr->value.enabletomove = false;

				if (line_list.len && line_list.link_end->value.enable) {
					line_list.link_end->value.enable = false;
					line_list.link_end->value.rc22 = ptr;
					return;
				}

				line_list.append(Line(xy(cursor.PosXOnMap, cursor.PosYOnMap)));
				line_list.link_end->value.rc12 = ptr;
				return;
			}

			if (ptr->value.IsCursorOn()) {
				ptr->value.color = rezistor_col * 0.5;
				ptr_flag = true;
			}
			else ptr->value.color = rezistor_col;

			if (ptr->value.pressstatus && ptr->value.enabletomove) {
				ptr->value.center(cursor.PosXOnMap - cursor.lastPosX, cursor.PosYOnMap - cursor.lastPosY);
				ptr_flag = true;
				klick_index = ptr_index;
			}
			if (ptr->value.IsKlickOnR()) rezistor_list.clear(ptr_index);

			if (ptr_flag) return;
		}
		else {
			if (klick_index == ptr_index) {

				if (ptr->value.IsCursorOnInfoButton()) {
					ptr->value.ib_col = rez_infofield_col * 0.5;
					if (ptr->value.IsCursorUnklickInfoButton()) ptr->value.enabletosetinfo = !ptr->value.enabletosetinfo;
				}
				else ptr->value.ib_col = rez_infofield_col;

				if (ptr->value.IsCursorUnklickInfoField()) {
					rezistorforstringinput->enabletoinputtext = true;
					rezistorforstringinput = &ptr->value;
				}

				if (ptr->value.IsCursorOnCircle(0)) ptr->value.r1 = ptr->value.r0 * 2;
				else ptr->value.r1 = ptr->value.r0;
				if (ptr->value.IsCursorOnCircle(1)) ptr->value.r2 = ptr->value.r0 * 2;
				else ptr->value.r2 = ptr->value.r0;
				if (ptr->value.IsKlickOnCircle(0)) {
					ptr->value.c_col1 = black;
					ptr->value.enabletomove = false;

					if (line_list.len && line_list.link_end->value.enable) {
						line_list.link_end->value.enable = false;
						line_list.link_end->value.rc21 = ptr;
						return;
					}

					line_list.append(Line(xy(cursor.PosXOnMap, cursor.PosYOnMap)));
					line_list.link_end->value.rc11 = ptr;
					return;
				}
				if (ptr->value.IsKlickOnCircle(1)) {
					ptr->value.c_col2 = black;
					ptr->value.enabletomove = false;

					if (line_list.len && line_list.link_end->value.enable) {
						line_list.link_end->value.enable = false;
						line_list.link_end->value.rc22 = ptr;
						return;
					}

					line_list.append(Line(xy(cursor.PosXOnMap, cursor.PosYOnMap)));
					line_list.link_end->value.rc12 = ptr;
					return;
				}

				if (ptr->value.IsCursorOn()) ptr->value.color = rezistor_col * 0.5;
				else {
					ptr->value.color = rezistor_col;
					klick_index = -1;
				}

				if (ptr->value.pressstatus && ptr->value.enabletomove) ptr->value.center(cursor.PosXOnMap - cursor.lastPosX, cursor.PosYOnMap - cursor.lastPosY);
				if (ptr->value.IsKlickOnR()) rezistor_list.clear(ptr_index);
				return;
			}
		}
		ptr_index++;
		ptr = ptr->link_next;

	} while (ptr != nullptr);
}
void Window::BatteryEventHalding() {
	if (battery.IsCursorOn()) battery.color = battery_col * 0.5;
	else battery.color = battery_col;
	if (battery.IsKlickOnR()) {
		BatteryInit = false;
		battery.c_col1 = battery.c_col2 = battery.c_color;
	}
	if (battery.enabletomove && battery.pressstatus) battery.center(vec(cursor.PosXOnMap, cursor.PosYOnMap, 0));
	if (battery.IsCursorOnCircle(0)) battery.r1 = battery.r0 * 2;
	else battery.r1 = battery.r0;
	if (battery.IsCursorOnCircle(1)) battery.r2 = battery.r0 * 2;
	else battery.r2 = battery.r0;

	if (battery.IsKlickOnCircle(0)) {
		battery.c_col1 = black;
		battery.enabletomove = false;
		if (line_list.len && line_list.link_end->value.enable) {
			line_list.link_end->value.enable = false;
			line_list.link_end->value.rb1 = &battery;
			return;
		}
		line_list.append(Line(xy(cursor.PosXOnMap, cursor.PosYOnMap)));
		line_list.link_end->value.rb1 = &battery;
	}
	if (battery.IsKlickOnCircle(1)) {
		battery.c_col2 = black;
		battery.enabletomove = false;
		if (line_list.len && line_list.link_end->value.enable) {
			line_list.link_end->value.enable = false;
			line_list.link_end->value.rb2 = &battery;
			return;
		}
		line_list.append(Line(xy(cursor.PosXOnMap, cursor.PosYOnMap)));
		line_list.link_end->value.rb2 = &battery;
	}
}
void Window::LineEventHalding(){
	Line_ptr ptr = line_list.link_begin;
	if (!line_list.len) return;
	int ptr_index;
	ptr_index = 0;
	do {

		if (EraserMode) {
			if (ptr->value.IsCursorOn()) {
				if (ptr->value.rc11 != nullptr) {
					ptr->value.rc11->value.c_col1 = ptr->value.rc11->value.c_color;
					if (ptr->value.rc11->value.c_col1 == ptr->value.rc11->value.c_col2)
						ptr->value.rc11->value.enabletomove = true;
				}
				if (ptr->value.rc12 != nullptr) {
					ptr->value.rc12->value.c_col2 = ptr->value.rc12->value.c_color;
					if (ptr->value.rc12->value.c_col2 == ptr->value.rc12->value.c_col1)
						ptr->value.rc12->value.enabletomove = true;
				}

				if (ptr->value.rc21 != nullptr) {
					ptr->value.rc21->value.c_col1 = ptr->value.rc21->value.c_color;
					if (ptr->value.rc21->value.c_col1 == ptr->value.rc21->value.c_col2)
						ptr->value.rc21->value.enabletomove = true;
				}
				if (ptr->value.rc22 != nullptr) {
					ptr->value.rc22->value.c_col2 = ptr->value.rc22->value.c_color;
					if (ptr->value.rc22->value.c_col2 == ptr->value.rc22->value.c_col1)
						ptr->value.rc22->value.enabletomove = true;
				}
				if (ptr->value.rb1 != nullptr) {
					battery.c_col1 = battery.c_color;
					if (battery.c_col1 == battery.c_col2) battery.enabletomove = true;
				}
				if (ptr->value.rb2 != nullptr) {
					battery.c_col2 = battery.c_color;
					if (battery.c_col2 == battery.c_col1) battery.enabletomove = true;
				}

				line_list.clear(ptr_index);
				return;
			}
		}
		else {
			if (ptr->value.enable) {
				ptr->value.draw();
				if (cursor.pressR) {
					if (line_list.link_end->value.rc11 != nullptr) {
						line_list.link_end->value.rc11->value.c_col1 = line_list.link_end->value.rc11->value.c_color;
						if (line_list.link_end->value.rc11->value.c_col1 == line_list.link_end->value.rc11->value.c_col2)
							line_list.link_end->value.rc11->value.enabletomove = true;
					}
					if (line_list.link_end->value.rc12 != nullptr) {
						line_list.link_end->value.rc12->value.c_col2 = line_list.link_end->value.rc12->value.c_color;
						if (line_list.link_end->value.rc12->value.c_col2 == line_list.link_end->value.rc12->value.c_col1)
							line_list.link_end->value.rc12->value.enabletomove = true;
					}
					if (line_list.link_end->value.rb1 != nullptr) {
						battery.c_col1 = battery.c_color;
						if (battery.c_col1 == battery.c_col2) battery.enabletomove = true;
					}
					if (line_list.link_end->value.rb2 != nullptr) {
						battery.c_col2 = battery.c_color;
						if (battery.c_col2 == battery.c_col1) battery.enabletomove = true;
					}
					line_list.clear();
					return;
				}
			}
		}

		ptr_index++;
		ptr = ptr->link_next;

	} while (ptr != nullptr);
}
void Window::PanelWithElementsEventHalding() {
	if (!ShowPanelWithElementsFlag) return;
	if (AddRezistor.IsKlickOn() && not_append_yet) {
		not_append_yet = false;
		rezistor_list.append(Rezistor(rezistorpos0));
	}
	if (cursor.unpress) not_append_yet = true;

	if (BatteryInit) AddBatary.color = battery_col * 0.3;
	else AddBatary.color = battery_col;
	if (AddBatary.IsUnklickOn()) {
		BatteryInit = true;
		battery.center(baterypos0);
	}if (AddRezistor.IsCursorOn() && cursor.unpress) rezistor_list.append(Rezistor(rezistorpos0));

	if (BatteryInit) AddBatary.color = battery_col * 0.3;
	else AddBatary.color = battery_col;
	if (AddBatary.IsUnklickOn()) {
		BatteryInit = true;
		battery.center(baterypos0);
	}
}
void Window::Delete_All() {
	while (rezistor_list.len) rezistor_list.clear();
	while (line_list.len) line_list.clear();
	BatteryInit = false;
	battery.c_col1 = battery.c_col2 = battery.c_color;
	rezistorforstringinput = nullptr;
}
void Window::show() {
	ShowDefolt();
	ButtonEventHaldingWindow();
	RezistorEventHalding();
	LineEventHalding();
	if (BatteryInit) BatteryEventHalding();

	line_list.print();
	rezistor_list.print();
	if (BatteryInit) battery.show();
	
	ShowUserButtons();
}
void Window::ShowPanelWithElements() {
	SetColor(but_color * 1.5);
	DrawSquare(Lx, -1, -1.55, 1);
	glPushMatrix();
	glTranslatef(0, 0, -MIN);
	AddRezistor.show();
	AddBatary.show();
	Eraser.show();
	glPopMatrix();

	if (EraserMode) Eraser.color = eraser_col * 0.5;
	else Eraser.color = eraser_col;

	if (Eraser.IsUnklickOn()) EraserMode = !EraserMode;
}
void Window::ShowPanelButton() {
	SetColor(but_color);
	glPushMatrix();
	glTranslatef(0, 0, -MIN);
	SetColor(ShowPanelWithElementsFlag ? black : but_color);
	DrawOval(PanelButton.x1_s, PanelButton.y1_s + Wall_Distance, PanelButton.x2_s, PanelButton.y1_s + a / 3 - Wall_Distance);
	DrawOval(PanelButton.x1_s, PanelButton.y1_s + a / 3 + Wall_Distance, PanelButton.x2_s, PanelButton.y1_s + a / 3 * 2 - Wall_Distance);
	DrawOval(PanelButton.x1_s, PanelButton.y1_s + a / 3 * 2 + Wall_Distance, PanelButton.x2_s, PanelButton.y2_s - Wall_Distance);

	if (PanelButton.IsCursorOn()) {
		glLineWidth(1);
		glBegin(GL_LINE_LOOP);
		SetColor(black);
		glVertex2f(PanelButton.x1_s, PanelButton.y1_s);
		glVertex2f(PanelButton.x2_s, PanelButton.y1_s);
		glVertex2f(PanelButton.x2_s, PanelButton.y2_s);
		glVertex2f(PanelButton.x1_s, PanelButton.y2_s);
		glEnd();
	}
	glPopMatrix();
}
void Window::ShowDefolt() {
	ShowPanelButton();
	if (ShowPanelWithElementsFlag) ShowPanelWithElements();
	StartButton.show();
	RezultField.show();
	print(RezultField.x1 + 0.01, RezultField.y2 - 0.01, rezult_string, white);
}
String Window::get_rezult() {
	if (StartNull(rezistor_list) == -1) return String("-1");

	if (SetNumbersOfPoints(line_list) == -1) return String("-1");
	if (SetNumberOfRezistors(rezistor_list) == -1) return String("-1");
	InputValue(line_list, rezistor_list);
	String rezult = gdd_string::to_String(fun(NumberOfPoints));
	EndNull(line_list, rezistor_list);
	return rezult;
}
void Window::ShowUserButtons() {
	if (Next.IsCursorOn()) Next.color = blue_vers * 0.5;
	else Next.color = blue_vers;
	if (Previous.IsCursorOn()) Previous.color = blue_vers * 0.5;
	else Previous.color = blue_vers;
	if (Delete.IsCursorOn()) Delete.color = delete_col * 0.5;
	else Delete.color = delete_col;
	if (AddWindow.IsCursorOn()) AddWindow.color = addwin_col * 0.5;
	else AddWindow.color = addwin_col;
	Next.show();
	Previous.show();
	Delete.show();
	AddWindow.show();

	//text
	textsize = 0.01;
	print(Previous.x2 + 0.01, Previous.y2 - 0.01, to_String(Window_Index + 1, 3), black);
	textsize = 0.005;
	//text

	if (Next.IsUnklickOn())
		if (window_list.len - 1 > Window_Index)
			Window_Index++;
	if (Previous.IsUnklickOn())
		if (Window_Index != 0) Window_Index--;
	if (AddWindow.IsUnklickOn()) {
		window_list.append(++Window_Index, Window());
	}
	if (Delete.IsUnklickOn()) {
		//cout << "1" << endl;
		if (window_list.len != 1) {
			window_list[Window_Index].Delete_All();
			//cout << "2" << endl;
			window_list.clear(Window_Index);
		}
		//cout << Window_Index << endl;
		if (Window_Index == window_list.len && Window_Index) Window_Index--;
		//cout << Window_Index << endl;
	}
}

void WindowInit() {
	window_list.append(Window());
}


///from user 
void Key_Callback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mods) {
	//if (key == GLFW_KEY_SPACE) window_list[Window_Index].Delete_All();
	if (rezistorforstringinput->enabletoinputtext && rezistorforstringinput->enabletosetinfo) {
		if (action == GLFW_PRESS) switch (key) {
		case GLFW_KEY_BACKSPACE:
			rezistorforstringinput->value -= 1;
			break;
		default:
			rezistorforstringinput->value += key;
			break;
		}
	}
}

void ClearParametry() {
	cursor.lastPosX = cursor.PosXOnMap;
	cursor.lastPosY = cursor.PosYOnMap;
	cursor.unpress = false;

	if (rezistorforstringinput->enabletoinputtext == true)
		if (!(cursor.LeftKlickPosX >= rezistorforstringinput->fix1 &&
			cursor.LeftKlickPosX <= rezistorforstringinput->fix2 &&
			cursor.LeftKlickPosY >= rezistorforstringinput->fiy1 &&
			cursor.LeftKlickPosY <= rezistorforstringinput->fiy2) && rezistorforstringinput->enabletosetinfo)
			rezistorforstringinput->enabletoinputtext = false;
}


#pragma once
#include "figures.h"
///////////////////////////////////////////////////////////////////////////////////////initial parameters
int HeaderSize = 25;

int WIDTH = 1920;
int HEIGHT = 1080;
float kx = (float)HEIGHT / WIDTH;
float HeaderMapSize = (float)2 * (float)HeaderSize / (float)HEIGHT;

GLFWwindow* CreateInitialWindow() {
    GLFWwindow* glfwwindow;
    glfwInit();
    glfwwindow = glfwCreateWindow(WIDTH, HEIGHT, "Rezistors", NULL, NULL);
    glfwMakeContextCurrent(glfwwindow);
    return glfwwindow;
}

void InitSettings() {
    glScalef(kx, 1, 1);
}
///////////////////////////////////////////////////////////////////////////////////////initial parameters

int LocWIDTH, LocHEIGHT;
void CreateNewWindow(GLFWwindow* glfwwindow) {
    LocWIDTH = WIDTH;
    LocHEIGHT = HEIGHT;
    glfwGetWindowSize(glfwwindow, &WIDTH, &HEIGHT);
    HEIGHT += HeaderSize;
    if (LocWIDTH != WIDTH || LocHEIGHT != HEIGHT) {
        kx = (float)HEIGHT / WIDTH;
        glViewport(0, 0, WIDTH, HEIGHT);
        glLoadIdentity();
        InitSettings();
    }
}

///////////////////////////////////// Cursor

typedef struct {
    float PosX, PosY, PosXOnMap, PosYOnMap, lastPosX, lastPosY;
    float LeftKlickPosX, LeftKlickPosY, RightKlickPosX, RightKlickPosY;
    float LeftUnklickPosX, LeftUnklickPosY;
    bool press, unpress, pressR;
} Cursor;

Cursor cursor;
void Cursor_Pos_Callback(GLFWwindow*, double, double);
void Scroll_Callback(GLFWwindow*, double, double);
void Mouse_Callback(GLFWwindow*, int, int, int);
void Key_Callback(GLFWwindow*, int, int, int, int);


void EventHandling(GLFWwindow* glfwwindow) {
    glfwSetCursorPosCallback(glfwwindow, Cursor_Pos_Callback);
    glfwSetKeyCallback(glfwwindow, Key_Callback);
    glfwSetScrollCallback(glfwwindow, Scroll_Callback);
    glfwSetMouseButtonCallback(glfwwindow, Mouse_Callback);
    //ButtonEventHalding();
}


void Cursor_Pos_Callback(GLFWwindow* glfwwindow, double x, double y) {
    cursor.PosX = x;
    cursor.PosY = y;
    cursor.PosXOnMap = (2 * x / (float)WIDTH - 1) / kx;
    cursor.PosYOnMap = 1 - 2 * y / (float)(HEIGHT - HeaderSize);
}


void Scroll_Callback(GLFWwindow* glfwwindow, double x, double y) {

}


void Mouse_Callback(GLFWwindow* glfwwindow, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:

        if (action == GLFW_PRESS) {
            cursor.LeftKlickPosX = cursor.PosXOnMap;
            cursor.LeftKlickPosY = cursor.PosYOnMap;
            cursor.press = true;
        }

        if (action == GLFW_RELEASE) {
            cursor.press = false;
            cursor.unpress = true;
            cursor.LeftUnklickPosX = cursor.PosXOnMap;
            cursor.LeftUnklickPosY = cursor.PosYOnMap;
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_PRESS) {
            cursor.RightKlickPosX = cursor.PosXOnMap;
            cursor.RightKlickPosY = cursor.PosYOnMap;
            cursor.pressR = true;
        }
        if (action == GLFW_RELEASE) {
            cursor.pressR = false;
        }
        break;
    }
}
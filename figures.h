#pragma once
#include "Libs.h"
#define CountOfCirclePoint 25

inline void DrawSquare(float x1, float y1, float x2, float y2) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glEnd();
}

inline void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void DrawCircle(float x1, float y1, float r) {

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x1, y1);
    float a = M_PI * 2 / CountOfCirclePoint;
    for (int i = -1; i < CountOfCirclePoint; i++) {
        glVertex2f(x1 + r * sin(a * i), y1 + r * cos(a * i));
    }
    glEnd();
}

void DrawOval(float x1, float y1, float x2, float y2) {
    float r = (y2 - y1) / 2;
    DrawCircle(x1 + r, y1 + r, r);
    DrawCircle(x2 - r, y2 - r, r);
    DrawSquare(x1 + r, y1, x2 - r, y2);
}
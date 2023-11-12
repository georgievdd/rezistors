#pragma once
#include "Libs.h"

float textsize = 0.005;
int num_quads;

void print(float x, float y, String text, Color color) {

    static char buffer[99999];

    glPushMatrix();
    glTranslatef(x, y, -0.00001);
    glScalef(textsize, -textsize, 1);
    num_quads = stb_easy_font_print(0, 0, text.get_char_ptr(), NULL, buffer, sizeof(buffer));
    SetColor(color);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}
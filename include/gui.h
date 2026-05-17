#ifndef GUI_H
#define GUI_H

#include "raylib.h"

typedef struct {
    Vector2 pos;
    Vector2 dimensions;
    Color color;

    bool isActive;
} Button;


Button CreateButton(Vector2 pos, Vector2 dimensions, Color color);
bool CheckButtonCollision(Button *button);
void DrawButton(Button *button);
void DrawButtonText(Button *button, const char *text, int font_size, Color color);
void ActivateButton(Button *button);

#endif
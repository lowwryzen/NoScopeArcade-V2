#include "gui.h"

Button CreateButton(Vector2 pos, Vector2 dimensions, Color color){
    Button button = {
        .pos = pos,
        .dimensions = dimensions,
        .color = color
    };

    return button;
}

bool CheckButtonCollision(Button *button){
    Vector2 button_box_min = {
        button->pos.x, button->pos.y
    };

    Vector2 button_box_max = {
        button->pos.x + (button->dimensions.x), button->pos.y + (button->dimensions.y)
    };
    
    Vector2 mouse_pos = GetMousePosition();

    return(
        button_box_max.x >= mouse_pos.x && button_box_min.x <= mouse_pos.x &&
        button_box_max.y >= mouse_pos.y && button_box_min.y <= mouse_pos.y 
    );
}

void DrawButton(Button *button){
    DrawRectangle((int)button->pos.x, (int)button->pos.y, (int)button->dimensions.x, (int)button->dimensions.y, button->color);
}

void DrawButtonText(Button *button, const char *text, int font_size, Color color){
    DrawText(text, button->pos.x, button->pos.y, font_size, color);
}

void ActivateButton(Button *button){
    if (CheckButtonCollision(button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        button->isActive = 1;
    
    else button->isActive = 0;
}
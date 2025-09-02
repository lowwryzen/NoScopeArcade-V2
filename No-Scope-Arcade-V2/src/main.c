#include "raylib.h"

int main(){
    InitWindow(1280,720,"No Scope ArcadeV2");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        
        DrawText("Fase inicial do projeto, por favor aguarde novos updates", 
            200, 360, 30, BLACK);

        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
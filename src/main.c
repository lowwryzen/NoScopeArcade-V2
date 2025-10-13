#include "raylib.h"
#include "moveset.h"

int main(){
    InitWindow(1280,720,"No Scope ArcadeV2");
    SetTargetFPS(60);

    Camera3D cam = {
        .fovy=45.0f,
        .position=   (Vector3){1.0f,1.0f,1.0f},
        .target=     (Vector3){0.0f,0.0f,0.0f},
        .up=         (Vector3){0.0f,1.0f,0.0f},
        .projection= CAMERA_PERSPECTIVE,
    };

    Model cube = LoadModel("./assets/models/cube.obj");
    Texture2D cube_texture = LoadTexture("./assets/textures/texture.png");
    Vector3 cube_pos = (Vector3){.x=0.0f, .y=0.0f, .z=0.0f};

    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube_texture;

    while(!WindowShouldClose()){
        BeginDrawing();
        
        ClearBackground(WHITE);
            BeginMode3D(cam);
                movesetPlayer(&cam);
                movesetMouse(&cam);
                
                DrawModel(cube, cube_pos, 1.0f, WHITE);

                DrawGrid(10, 1.0f);


            EndMode3D();
        EndDrawing();
    }


    UnloadModel(cube);
    UnloadTexture(cube_texture);

    CloseWindow();

    return 0;
}
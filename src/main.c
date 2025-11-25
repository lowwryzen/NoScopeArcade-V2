#include "raylib.h"

#include "world.h"
#include "object.h"
#include "entity.h"
#include "moveset.h"

bool collision = 0;

Camera3D cam = {
    .fovy=45.0f,
    .position=   (Vector3){1.0f,10.0f,1.0f},
    .target=     (Vector3){0.0f,0.0f,0.0f},
    .up=         (Vector3){0.0f,1.0f,0.0f},
    .projection= CAMERA_PERSPECTIVE,
};

int main(){
    InitWindow(1280,720,"No Scope ArcadeV2");
    SetTargetFPS(60);

    Object player_body = {
        .model       =  LoadModel("./assets/models/cube.obj"),
        .texture     =  {0},
        .boundingbox =  GetModelBoundingBox(player_body.model),
        .position    =  cam.position,
        .scale       =  1.0f
    };
    
    Object cube = {
        .model    =    LoadModel("./assets/models/cube.obj"),
        .texture  =    LoadTexture("./assets/textures/texture.png"),
        .position =    (Vector3){2.0f, 0.0f, 0.0f},
        .boundingbox = GetModelBoundingBox(cube.model),
        .scale    =    1.0f
    };
    
    Object cube2 = {
        .model    =     cube.model,
        .texture  =     cube.texture,
        .position =     (Vector3){0.0f, -2.0f, 0.0f},
        .boundingbox =  GetModelBoundingBox(cube2.model),
        .scale    =     2.0f
    };

    Object ground = {
        .model    =     LoadModel("./assets/models/chao_xadrez.obj"),
        .texture  =     LoadTexture("./assets/textures/ground.jpg"),
        .position =     (Vector3){0.0f, -2.0f, 0.0f},
        .boundingbox =  GetModelBoundingBox(ground.model),
        .scale    =     1.0f
    };

    Entity player = {
        .body = player_body,
        .pos  = cam.position,
        .vel  = 0.1f,
        .HP   = 100
    };
    
    Object collidable_obj[] = {cube, cube2, ground};

    while(!WindowShouldClose()){
        BeginDrawing();
        
        ClearBackground(WHITE);
        
            BeginMode3D(cam);
                Vector3 lastpos = player.pos;
                
                movesetPlayer(&cam, &player);
                UpdatePos(&cam, &player, collidable_obj, sizeof(collidable_obj)/sizeof(Object));
                movesetMouse(&cam);
                
                InitObject(&cube);
                InitObject(&cube2);
                InitObject(&ground);

                DrawGrid(10, 1.0f);
        
            EndMode3D();
            
            DrawText(TextFormat("x pos: %0.2f", cam.position.x), 0,0,30,BLACK);
            DrawText(TextFormat("y pos: %0.2f", cam.position.y), 0,30,30,BLACK);
            DrawText(TextFormat("z pos: %0.2f", cam.position.z), 0,60,30,BLACK);
        
        EndDrawing();
    }
    
    DelObject(&cube);
    DelObject(&ground);

    CloseWindow();

    return 0;
}
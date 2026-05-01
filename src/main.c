#include "raylib.h"

#include "world.h"
#include "object.h"
#include "entity.h"
#include "moveset.h"

bool collision = 0;

Camera3D cam = {
    .fovy=45.0f,
    .position=   (Vector3){1.0f,10.0f,0.0f},
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
        .model    =    LoadModel("./assets/models/cube3.obj"),
        .texture  =    LoadTexture("./assets/textures/texture.png"),
        .position =    (Vector3){-15.0f, 1.0f, -27.0f},
        .boundingbox = GetModelBoundingBox(cube.model),
        .scale    =    1.0f
    };
    
    Object cube2 = {
        .model    =     LoadModel("./assets/models/cube.obj"),
        .texture  =     LoadTexture("./assets/textures/texture.png"),
        .position =     (Vector3){1.0f, 1.0f, 1.0f},
        .boundingbox =  GetModelBoundingBox(cube2.model),
        .scale    =     2.0f
    };


    Object ground = {
        .model    =     LoadModel("./assets/models/chao_xadrez.obj"),
        .texture  =     LoadTexture("./assets/textures/ground.jpg"),
        .position =     (Vector3){0.0f, 1.0f, 0.0f},
        .boundingbox =  GetModelBoundingBox(ground.model),
        .scale    =     1.0f
    };

    Entity player = CreateEntity(player_body, cam.position, 100, 0.1f, 1);

    Object collidable_obj[] = {cube2, cube , ground};

    while(!WindowShouldClose()){
        player.lastpos = player.pos;

        movesetPlayer(&cam, &player);
        
        player.onGround = 0;
        for (int i=0; i < sizeof(collidable_obj)/sizeof(Object); i++){
            UpdatePos(&cam, &player, &collidable_obj[i]);
        }

        movesetMouse(&cam);
        
        EnableGravity(&player, GRAVITY);
        

        BeginDrawing();
        
            ClearBackground(WHITE);
        
            BeginMode3D(cam);

                InitObject(&cube);
                InitObject(&cube2);
                InitObject(&ground);
                
            EndMode3D();

            DrawText(TextFormat("x pos: %0.2f", cam.position.x), 0,0,30,BLACK);
            DrawText(TextFormat("y pos: %0.2f", cam.position.y), 0,30,30,BLACK);
            DrawText(TextFormat("z pos: %0.2f", cam.position.z), 0,60,30,BLACK);

            DrawText(TextFormat("x pos p: %0.2f", player.pos.x), 200,0,30,BLACK);
            DrawText(TextFormat("y pos p: %0.2f", player.pos.y), 200,30,30,BLACK);
            DrawText(TextFormat("z pos p: %0.2f", player.pos.z), 200,60,30,BLACK);

            DrawText(TextFormat("x pos b: %0.2f", player.body.position.x), 400,0,30,BLACK);
            DrawText(TextFormat("y pos b: %0.2f", player.body.position.y), 400,30,30,BLACK);
            DrawText(TextFormat("z pos b: %0.2f", player.body.position.z), 440,60,30,BLACK);
        
        EndDrawing();
    }
    
    DelObject(&cube);
    DelObject(&cube2);
    DelObject(&ground);

    CloseWindow();

    return 0;
}
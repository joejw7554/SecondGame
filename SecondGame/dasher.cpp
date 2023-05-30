#include "raylib.h"

int main()
{
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    // rectangle dimensions
    const int width{50};
    const int height{80};

    // acceleartion due to gravity
    const int gravity{1};

    Texture2D scarfy=LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{};
    Vector2 scarfyPos{};

    int posY{windowHeight - height};
    int velocity{0};
    
    bool isInAir{};
    const int jumpVel{-22};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (posY >= (windowHeight - height))
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity;
            isInAir = true;
        }

        //Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        posY += velocity;
        DrawRectangle(windowWidth * 0.5, posY, width, height, BLUE);
        // stop drawing
        EndDrawing();
    }
    CloseWindow();
}
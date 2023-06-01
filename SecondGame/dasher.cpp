#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    int windowDimention[2]{512,380};
    InitWindow(windowDimention[0], windowDimention[1], "Dapper Dasher!");

    // acceleartion due to gravity
    const int gravity{1'000};

    // scarfy vars
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimention[0] * 0.5f - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimention[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // nubula vars
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Rectangle rec
        {windowDimention[0], windowDimention[1] - nebula.height / 8}, // Vector2 pos
        0,                                               // int frame
        1.0 / 12.0,                                      // float updateTime
        0};                                              // float runningTime

    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {windowDimention[0] + 300, windowDimention[1] - nebula.height / 8},
        0,
        1.0 / 16.0,
        0};

    int nebVel{-200};

    // animation frame
    int velocity{0};

    bool isInAir{};
    // jump vel pixel per sec
    const int jumpVel{-600};

    SetTargetFPS(60);
    int frame{};

    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyData.pos.y >= (windowDimention[1] - scarfyData.rec.height))
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebulas positions
        nebData.pos.x += nebVel * dT;
        neb2Data.pos.x += nebVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update running time
        scarfyData.runningTime += dT;

        if (!isInAir)
        {
            // update scarfy animation frame
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                scarfyData.rec.x = frame * scarfyData.rec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }

        // update neb anim
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }
        // update neb2 anim
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x =neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        // Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Neb
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // 2nd Neb
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        // stop drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

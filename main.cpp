#include "raylib.h"
#include "raymath.h"

int main() {

    const int windowWidth{1280};
    const int windowHeight{720};
    const char windowTitle[] = "Classy Clash";

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(60);

    struct {
        Texture2D texture;
        Vector2 position;
    } GameMap;

    GameMap.texture = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    GameMap.position = {0.0, 0.0};
    float speed = 4.0;

    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightRunning = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight{knightIdle};
    Vector2 knightPosition = {
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };

    // 1: facing right, -1: facing left
    float rightLeft{1.f};

    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.0/12.0};
    bool isKnightMoving{false};

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Texture2D activeSpritesheet{};
        isKnightMoving ? activeSpritesheet = knightRunning : activeSpritesheet = knight;

        // movement of the character is achieved by
        // moving the game map texture, so that the character
        // is always in the center of the screen
        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0) {
            isKnightMoving = true;
            GameMap.position = Vector2Subtract(GameMap.position, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        } else {
            isKnightMoving = false;
        }

        DrawTextureEx(GameMap.texture, GameMap.position, 0, 4, RAYWHITE);

        runningTime += deltaTime;
        if (runningTime >= updateTime) {
            frame++;
            runningTime = 0.0;
            if (frame > maxFrame) frame = 0;
        }

        Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle destination{knightPosition.x, knightPosition.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(activeSpritesheet, source, destination, Vector2{}, 0.0f, WHITE);

        EndDrawing();
    }
    CloseWindow();
}

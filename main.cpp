#include "raylib.h"
#include "raymath.h"

class Character {
public:
    Vector2 getWorldPosition();
    void setScreenPosition(int windowWidth, int windowHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D textureIdle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D textureRun{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPosition{0.0, 0.0};
    Vector2 worldPosition{0.0, 0.0};
    float rightLeft{1.0};
    float runningTime{0.0};
    int frame{0};
    const int maxFrame{6};
    const float updateTime{1.0 / 12.0};
    const float speed{4.0};
};

Vector2 Character::getWorldPosition() {
    return worldPosition;
}

void Character::setScreenPosition(int windowWidth, int windowHeight) {
    screenPosition.x = (float) windowWidth / 2.0f - 4.0f * (0.5f * (float) texture.width / 6.0f);
    screenPosition.y = (float) windowHeight / 2.0f - 4.0f * (0.5f * (float) texture.height);
}

void Character::tick(float deltaTime) {
    // handle movement
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    if (Vector2Length(direction) != 0.0) {
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = textureRun;
    } else {
        texture = textureIdle;
    }
    // handle animation changes
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.0;
        if (frame > maxFrame) frame = 0;
    }
    // draw the character
    Rectangle source{frame * (float) texture.width / 6.f, 0.f, rightLeft * (float) texture.width / 6.f, (float) texture.height};
    Rectangle destination{screenPosition.x, screenPosition.y, 4.0f * (float) texture.width / 6.0f, 4.0f * (float) texture.height};
    DrawTexturePro(texture, source, destination, Vector2{}, 0.0f, WHITE);
}

int main() {
    const int windowWidth{1280};
    const int windowHeight{720};
    const char windowTitle[] = "Classy Clash";

    InitWindow(windowWidth, windowHeight, windowTitle);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition = {0.0, 0.0};

    Character knight{};
    knight.setScreenPosition(windowWidth, windowHeight);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPosition = Vector2Scale(knight.getWorldPosition(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPosition, 0, 4, RAYWHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}

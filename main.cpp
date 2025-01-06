#include "raylib.h"

int main() {

    const int windowDimensions[]{1280, 720};
    const char windowTitle[] = "Classy Clash";

    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}

#include <iostream>
#include <raylib.h>


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    InitWindow(800, 600, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
      ClearBackground(RAYWHITE);


    }
    CloseWindow();

    return 0;
}


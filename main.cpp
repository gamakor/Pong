#include <iostream>
#include <raylib.h>

struct Ball {
    Vector2 position;
    float speed_x;
    float speed_y;
    float radius;

    void Draw()
    {
        DrawCircle(position.x, position.y, radius, WHITE);
    }
};

struct Paddle {
    Vector2 position;
    float speed;
    int width;
    int height;

    Rectangle GetRect()
    {
        return Rectangle{ position.x - width / 2, position.y - height / 2, 10, 100 };
    }
    void Draw() {
        DrawRectangleRec(GetRect(),WHITE);
    }
};


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    InitWindow(800, 600, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);
    //create ball
    Ball ball;
    ball.position.x = GetScreenWidth()/2;
    ball.position.y = GetScreenHeight()/2;
    ball.speed_x = 3.0f;
    ball.speed_y = 3.0f;
    ball.radius = 5.0f;

    //create left panel
    Paddle leftPaddle;
    leftPaddle.position.x = 50;
    leftPaddle.position.y =GetScreenHeight()/2;
    leftPaddle.width = 50;
    leftPaddle.height = 100;
    leftPaddle.speed = 300.f;

    Paddle rightPaddle;
    rightPaddle.height = 100;
    rightPaddle.width = 50;
    rightPaddle.position.x = GetScreenWidth() - rightPaddle.width;
    rightPaddle.position.y = GetScreenHeight()/2;
    rightPaddle.speed = 300.f;

    const char* winnerText = nullptr;




    while (!WindowShouldClose()) {

        ball.position.x += ball.speed_x;
        ball.position.y += ball.speed_y;

        if (ball.position.y < 0) {
            ball.position.y = 0;
            ball.speed_y *= -1;
        }
        if (ball.position.y > GetScreenHeight()) {
            ball.position.y = GetScreenHeight();
            ball.speed_y *= -1;
        }


        if (IsKeyDown(KEY_W)) {
            leftPaddle.position.y -= leftPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
            leftPaddle.position.y += leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_UP)) {
            rightPaddle.position.y -= rightPaddle.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN )) {
            rightPaddle.position.y += rightPaddle.speed * GetFrameTime();
        }


        if (CheckCollisionCircleRec(ball.position,ball.radius,leftPaddle.GetRect())) {
            if (ball.speed_x <0) {
                ball.speed_x *= -1.05;
                ball.speed_y *= (ball.position.y - leftPaddle.position.y) / (leftPaddle.height/2) * -ball.speed_x;
            }
        }
        if (CheckCollisionCircleRec(ball.position,ball.radius,rightPaddle.GetRect())) {
            if (ball.speed_x>0) {
                ball.speed_x *= -1.05;
                ball.speed_y *= (ball.position.y - rightPaddle.position.y) / (rightPaddle.height/2) * -ball.speed_x;
            }
        }

        if (ball.position.x > GetScreenWidth()) {
            winnerText = "Player 1 Wins!";
        }

        if (ball.position.x < 0) {
            winnerText = "Player 2 Wins!";
        }


        BeginDrawing();
      ClearBackground(BLACK);

        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();

        if (winnerText) {

            int textWidth = MeasureText(winnerText,60);
            DrawText(winnerText,GetScreenWidth()/2 - textWidth/2,GetScreenHeight()/2 - 30,60,YELLOW);
        }

        if (winnerText && IsKeyDown(KEY_SPACE)) {
            ball.position.x = GetScreenWidth()/2;
            ball.position.y = GetScreenHeight()/2;
            ball.speed_x = 3.0f;
            ball.speed_y = 3.0f;
            winnerText = nullptr;
        }

        //DrawRectangle(0,GetScreenHeight()/2,50,100,BLACK);
       // DrawRectangle(GetScreenWidth()-50,GetScreenHeight()/2,50,100,BLACK);

       DrawFPS(10,10);
        EndDrawing();


    }
    CloseWindow();

    return 0;
}

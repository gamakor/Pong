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
    void ChangeDir() {
         speed_x *= -1;
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
    leftPaddle.width = 50;
    leftPaddle.height = 100;
    leftPaddle.position.x = 25;;
    leftPaddle.position.y =GetScreenHeight()/2;
    leftPaddle.speed = 400.f;

    Paddle rightPaddle;
    rightPaddle.height = 100;
    rightPaddle.width = 50;
    rightPaddle.position.x = GetScreenWidth()+12 ;
    rightPaddle.position.y = GetScreenHeight()/2;
    rightPaddle.speed = 400.f;

    int rightPaddleScore = 0;
    int leftPaddleScore = 0;


    const char* winnerText = nullptr;
    char leftPaddleScoreText[10] = "0";
    char rightPaddleScoreText[10] = "0";





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
            if (leftPaddle.position.y > leftPaddle.height/2)
            {
                leftPaddle.position.y -= leftPaddle.speed * GetFrameTime();
            }
        }
        if (IsKeyDown(KEY_S)) {
            if (leftPaddle.position.y < GetScreenHeight() - leftPaddle.height/2) {
                leftPaddle.position.y += leftPaddle.speed * GetFrameTime();
            }
        }

        if (IsKeyDown(KEY_UP)) {
            if (rightPaddle.position.y > rightPaddle.height/2) {
                rightPaddle.position.y -= rightPaddle.speed * GetFrameTime();
            }
        }
        if (IsKeyDown(KEY_DOWN )) {
            if (rightPaddle.position.y < GetScreenHeight() - rightPaddle.height/2) {
                rightPaddle.position.y += rightPaddle.speed * GetFrameTime();
            }
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

        if (ball.position.x > GetScreenWidth() && winnerText == nullptr) {
            leftPaddleScore++;

            sprintf(leftPaddleScoreText, "%i", leftPaddleScore);

            if (leftPaddleScore == 3 ) {
                winnerText = "Player 1 Wins!";
            }
            if (!winnerText) {
                ball.position.x = GetScreenWidth()/2;
                ball.position.y = GetScreenHeight()/2;
                ball.speed_x = 3.0f;
                ball.speed_y = 3.0f;
           }

        }
        //score for right pannel
        if (ball.position.x < 0 && winnerText == nullptr) {
            rightPaddleScore++;
            sprintf(rightPaddleScoreText, "%i", rightPaddleScore);
            if (rightPaddleScore == 3) {
                winnerText = "Player 2 Wins!";
            }
            if (!winnerText) {
                ball.position.x = GetScreenWidth()/2;
                ball.position.y = GetScreenHeight()/2;
                ball.speed_x = 3.0f;
                ball.speed_y = 3.0f;
                ball.ChangeDir();
            }


        }


        BeginDrawing();
      ClearBackground(BLACK);

        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();
        DrawText(leftPaddleScoreText, 10, 10, 20, WHITE);
        DrawText(rightPaddleScoreText, GetScreenWidth() - 20, 10, 20, WHITE);

        if (winnerText) {

            int textWidth = MeasureText(winnerText,60);
            DrawText(winnerText,GetScreenWidth()/2 - textWidth/2,GetScreenHeight()/2 - 30,60,YELLOW);
        }

        if (winnerText && IsKeyDown(KEY_SPACE)) {
            ball.position.x = GetScreenWidth()/2;
            ball.position.y = GetScreenHeight()/2;
            ball.speed_x = 3.0f;
            if (winnerText == "Player 2 Wins!") {
                ball.ChangeDir();
            }
            ball.speed_y = 3.0f;
            leftPaddleScore = 0;
            rightPaddleScore = 0;
            sprintf(leftPaddleScoreText, "%i", leftPaddleScore);
            sprintf(rightPaddleScoreText, "%i", rightPaddleScore);
            winnerText = nullptr;
        }

        //DrawRectangle(0,GetScreenHeight()/2,50,100,BLACK);
       // DrawRectangle(GetScreenWidth()-50,GetScreenHeight()/2,50,100,BLACK);

     //  DrawFPS(10,10);
        EndDrawing();


    }
    CloseWindow();

    return 0;
}

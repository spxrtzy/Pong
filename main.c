#include "raylib.h"
#include "structs.h"
#include <stdio.h>


int main(void)
{
    // Init
    struct wininfo Win;
    struct ball Ball;
    struct paddle paddleRight;
    struct paddle paddleLeft;

    Win.width = 800;
    Win.height = 500;
    Win.title = "PONG!";
    Win.framesps = 61;
    
    

    // Actual Inits

    InitWindow(Win.width, Win.height, Win.title);

    // InitAudioDevice();

    SetTargetFPS(Win.framesps);

    Ball.x = GetScreenWidth() / 2; 
    Ball.y = 10;
    Ball.radius = 5;
    Ball.speedX = 200;
    Ball.speedY = 200;


    // Paddles

    paddleLeft.x = 30;
    paddleLeft.y =  GetScreenHeight() / 2 - 135;
    paddleLeft.width = 15;
    paddleLeft.height = 135;
    paddleLeft.speed = 400;

    paddleRight.x = GetScreenWidth() - 30;
    paddleRight.y =  GetScreenHeight() / 2 - 135;
    paddleRight.width = 15;
    paddleRight.height = 135;
    paddleRight.speed = 400;
    
    char *winnerTitle = NULL;

    // Loads

    // Main game loop
    while (!WindowShouldClose()) 
    {

        // Rects and vectors
        Vector2 BallPos = {Ball.x, Ball.y};

        Rectangle PaddleLeft1 = {paddleLeft.x, paddleLeft.y, paddleLeft.width, paddleLeft.height};
    
        Rectangle PaddleRight2 = { paddleRight.x, paddleRight.y, paddleRight.width, paddleRight.height };

        Ball.x += Ball.speedX * GetFrameTime(); 
        Ball.y += Ball.speedY * GetFrameTime();

        if (Ball.y < 0) {
            Ball.y = 0;
            Ball.speedY *= -1;
        }

        if (Ball.y > GetScreenHeight()) {
            Ball.y = GetScreenHeight();
            Ball.speedY *= -1;
        }

        // Bounce of the right wall

        //User Inputs
            if (IsKeyDown(KEY_W)) {
                paddleLeft.y -= paddleLeft.speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_S)) {
                paddleLeft.y += paddleLeft.speed * GetFrameTime();
            }

            if (IsKeyDown(KEY_UP)) {
                paddleRight.y -= paddleRight.speed * GetFrameTime();
            }

            if (IsKeyDown(KEY_DOWN)) {
                paddleRight.y += paddleRight.speed * GetFrameTime();
            }

        // Collisions

        if (CheckCollisionCircleRec((Vector2){ Ball.x, Ball.y }, Ball.radius, PaddleRight2))
		{
            printf("Ball colided with Right Paddle\n");
			if (Ball.speedX > 0)
			{
				Ball.speedX *= -1.1f;
                Ball.speedY += 15;
			}
		}

        if (CheckCollisionCircleRec((Vector2){ Ball.x, Ball.y }, Ball.radius, PaddleLeft1))
		{
			if (Ball.speedX < 0)
			{
				Ball.speedX *= -1.1f;
                Ball.speedY += 20;
			}
		}


        printf("BALL POS (%d, %d)\n", Ball.x, Ball.y);
        printf("BALL SPEED (%d, %d)\n", Ball.speedX, Ball.speedY);

        if (Ball.x < 0){
            winnerTitle = "RIGHT PLAYER VICTORY";
            printf("%s", winnerTitle);
            Ball.x = GetScreenWidth() / 2;
            Ball.y = 10;
            Ball.speedX = 0;
            Ball.speedY = 0;
            
        }

        if (Ball.x > GetScreenWidth()) {
            winnerTitle = "LEFT PLAYER VICTORY!";
            printf("%s", winnerTitle);
            Ball.x = GetScreenWidth() / 2;
            Ball.y = 10;
            Ball.speedX = 0;
            Ball.speedY = 0;
        }

        if (winnerTitle && IsKeyPressed(KEY_SPACE)) {
            // Ball Values
            Ball.x = GetScreenWidth() / 2;
            Ball.y = 10;
            Ball.speedX = 200;
            Ball.speedY = 200;

            // Paddle Values
            paddleLeft.x = 30;
            paddleLeft.y =  GetScreenHeight() / 2 - 135;
            paddleLeft.speed = 400;

            paddleRight.x = GetScreenWidth() - 30;
            paddleRight.y =  GetScreenHeight() / 2 - 135;
            paddleRight.speed = 400;


            winnerTitle = NULL;

        }

        BeginDrawing();



            ClearBackground(BLACK);
            DrawFPS(10, 10);
            // Ball

            DrawCircle(Ball.x, Ball.y, Ball.radius, GREEN);
            
            // Paddles
            DrawRectangleRec(PaddleLeft1, RED);
            DrawRectangleRec(PaddleRight2, RED);

            if(winnerTitle) {
                int winnerTitleWitdh = MeasureText(winnerTitle, 45);
                int infoTextWidth = MeasureText("PRESS SPACE TO RESTART", 20);
                DrawText(winnerTitle, GetScreenWidth()/2-winnerTitleWitdh/2, GetScreenHeight() / 2 - 30, 45, YELLOW);
                DrawText("PRESS SPACE TO RESTART", GetScreenWidth()/2-infoTextWidth/2, GetScreenHeight() / 2 + 30, 20, YELLOW);
            }

        EndDrawing();
       
    }

    CloseWindow();    

    return 0;
}

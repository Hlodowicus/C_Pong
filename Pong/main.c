#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

char title[4] = "PONG";
char fps[6];
char num1[6];
char num2[6];
int SPEED = 2;
int POWERSPEED;
int scorep1 = 0;
int scorep2 = 0;

int SizeWidth(int percentage) {
    return GetScreenWidth() / 100 * percentage;
}

int SizeHeight(int percentage) {
    return GetScreenHeight() / 100 * percentage;
}

struct Ball {
    int x;
    int y;
    int width;
    int height;
    int speedX;
    int speedY;
    
};

bool CheckCollisionBallRect(struct Ball b, struct Rectangle r) {
    if (b.x < r.x + r.width &&
        b.x + b.width > r.x &&
        b.y < r.y + r.height &&
        b.y + b.height > r.y) {
        return true;
    }
    return false;
}


int main(int argc, const char * argv[]) {
    InitWindow(GetScreenWidth(), GetScreenHeight(), title);
    SetTargetFPS(60);
    ToggleFullscreen();
    InitAudioDevice();
    
    Sound scoreMusic = LoadSound("Powerup3.wav");
    Sound rebound = LoadSound("Blip_Select4.wav");
    
    
    struct Rectangle player1;
    player1.x = SizeWidth(5);
    player1.y = SizeHeight(40);
    player1.width = SizeWidth(2);
    player1.height = SizeHeight(15);

    
    struct Rectangle player2;
    player2.x = SizeWidth(95);
    player2.y = SizeHeight(40);
    player2.width = SizeWidth(2);
    player2.height = SizeHeight(15);
    
    struct Ball ball;
    ball.x = SizeWidth(50);
    ball.y = SizeHeight(50);
    ball.width = 25;
    ball.height = 25;
    ball.speedX = 1;
    ball.speedY = 1;
    
    while(!WindowShouldClose()) {
        //UPDATE////////////////////////////////////////////////////////////////////////////////
        ball.x += 10 * ball.speedX;
        ball.y += 10 * ball.speedY;
        
        if(ball.y <= 0 || ((ball.y + ball.height) >= GetScreenHeight()) ){
            ball.speedY = -ball.speedY;
        }
        
        if(ball.x > GetScreenWidth()) {
            scorep1 += 1;
            PlaySound(scoreMusic);
            sprintf(num1, "%d", scorep1);
            ball.x = SizeWidth(50);
            ball.y = SizeHeight(50);
            ball.speedX = -ball.speedX;
            if (scorep2 % 2 == 0) {
                ball.speedY = -ball.speedY;
                ball.speedX = -ball.speedX;
            } else {
                ball.speedX = -ball.speedX;
            }
        }
        if(ball.x + ball.width < 0) {
            scorep2 += 1;
            PlaySound(scoreMusic);
            sprintf(num2, "%d", scorep2);
            ball.x = SizeWidth(50);
            ball.y = SizeHeight(50);
            if (scorep2 % 2 == 0) {
                ball.speedY = -ball.speedY;
                ball.speedX = -ball.speedX;
            } else {
                ball.speedX = -ball.speedX;
            }
        }
        
        if (CheckCollisionBallRect(ball, player1)) {
            ball.speedX = -ball.speedX;
            ball.x = player1.x + player1.width;
            PlaySound(rebound);
        }

        if (CheckCollisionBallRect(ball, player2)) {
            ball.speedX = -ball.speedX;
            ball.x = player2.x - ball.width;
            PlaySound(rebound);
        }

        //CHECK_EVENTS//////////////////////////////////////////////////////////////////////////
        if(IsKeyDown(KEY_ESCAPE)){
            CloseWindow();
            UnloadSound(scoreMusic);
            UnloadSound(rebound);
            CloseAudioDevice();
        }
        if(IsKeyDown(KEY_W) && (player1.y > 0) ) {
            player1.y -= SizeHeight(1) * SPEED;
        }
        if(IsKeyDown(KEY_S) && (player1.y + player1.height < GetScreenHeight())) {
            player1.y += SizeHeight(1) * SPEED;
        }
        if(IsKeyDown(KEY_UP) && (player2.y > 0)) {
            player2.y -= SizeHeight(1) * SPEED;
        }
        if(IsKeyDown(KEY_DOWN) && (player2.y + player2.height < GetScreenHeight())) {
            player2.y += SizeHeight(1) * SPEED;
        }
        
        
        //DRAW//////////////////////////////////////////////////////////////////////////////////
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(num1, SizeWidth(30), SizeHeight(20), 160, DARKGRAY);
        DrawText(num2, SizeWidth(70), SizeHeight(20), 160, DARKGRAY);
        DrawRectangle(GetScreenWidth() / 2, SizeHeight(0), SizeWidth(1), SizeHeight(100), DARKGRAY);
        DrawRectangle(player1.x, player1.y, player1.width, player1.height, RAYWHITE);
        DrawRectangle(player2.x, player2.y, player2.width, player2.height, RAYWHITE);
        DrawRectangle(ball.x, ball.y, ball.width, ball.height, RAYWHITE);
        EndDrawing();
    }
    
    CloseWindow();
    UnloadSound(scoreMusic);
    UnloadSound(rebound);
    CloseAudioDevice();


    return 0;
}

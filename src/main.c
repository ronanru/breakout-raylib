#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Obstacle {
  int x, y, width, height;
  bool isVisible;
  Color color;
} Obstacle;

int main(void) {
  const int screenWidth = 1200;
  const int screenHeight = 1000;

  const Color colorArray[8] = {RED,    GREEN,  BLUE, YELLOW,
                               PURPLE, ORANGE, GOLD, PINK};

  InitWindow(screenWidth, screenHeight, "My awesome game POGGIES");
  SetTargetFPS(144);

  Obstacle obstacles[14];

  bool isGameOver = true;
  int boardX, ballX, ballY;
  bool isBallXIncreasing, isBallYIncreasing;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (isGameOver) {
      DrawText("Press Space to start", 350, screenHeight / 2, 40, WHITE);
      if (IsKeyPressed(KEY_SPACE)) {
        int obstaclesCount = 0;
        for (int i = 0; i < 4; i++) {
          int x = i % 2 == 0 ? 200 : 300;
          for (int j = 0; j < (i % 2 == 0 ? 4 : 3); j++) {
            obstacles[obstaclesCount].x = x;
            x += 200;
            obstacles[obstaclesCount].y = 50 + i * 10;
            obstacles[obstaclesCount].width = 200;
            obstacles[obstaclesCount].height = 10;
            obstacles[obstaclesCount].isVisible = true;
            obstacles[obstaclesCount].color = colorArray[rand() % 8];
            obstaclesCount++;
          }
        }
        isBallXIncreasing = rand() % 2 == 0;
        isBallYIncreasing = false;
        ballX = rand() % screenWidth;
        ballY = rand() % (screenHeight / 2) + screenHeight / 4;
        boardX = screenWidth / 2 - 100;
        isGameOver = false;
      }
    } else {
      if (IsKeyDown(KEY_A)) {
        boardX -= 10;
        if (boardX < 0)
          boardX = 0;
      }
      if (IsKeyDown(KEY_D)) {
        boardX += 10;
        if (boardX > screenWidth - 200)
          boardX = screenWidth - 200;
      }
      ballX += (isBallXIncreasing ? 1 : -1) * 5;
      ballY += (isBallYIncreasing ? 1 : -1) * 5;
      if (ballX > screenWidth - 5) {
        isBallXIncreasing = !isBallXIncreasing;
        ballX = screenWidth - 5;
      }
      if (ballX < 5) {
        isBallXIncreasing = !isBallXIncreasing;
        ballX = 5;
      }
      if (ballY > screenHeight - 5) {
        isGameOver = true;
      }
      if (ballY > screenHeight - 25 && ballX > boardX && ballX < boardX + 200) {
        isBallYIncreasing = !isBallYIncreasing;
        ballY = screenHeight - 25;
      }
      if (ballY < 5) {
        isBallYIncreasing = !isBallYIncreasing;
        ballY = 5;
      }

      for (int i = 0; i < 14; i++) {
        if (obstacles[i].isVisible) {
          if (ballX >= obstacles[i].x &&
              ballX <= obstacles[i].x + obstacles[i].width) {
            if (ballY + 5 >= obstacles[i].y &&
                ballY + 5 <= obstacles[i].y + obstacles[i].height) {
              isBallYIncreasing = !isBallYIncreasing;
              obstacles[i].isVisible = false;
              ballY = obstacles[i].y - 5;
            }
            if (ballY - 5 <= obstacles[i].y + obstacles[i].height &&
                ballY - 5 >= obstacles[i].y) {
              isBallYIncreasing = !isBallYIncreasing;
              obstacles[i].isVisible = false;
              ballY = obstacles[i].y + obstacles[i].height + 5;
            }
          }
          if (ballY >= obstacles[i].y &&
              ballY <= obstacles[i].y + obstacles[i].height) {
            if (ballX + 5 >= obstacles[i].x &&
                ballX + 5 <= obstacles[i].x + obstacles[i].width) {
              isBallXIncreasing = !isBallXIncreasing;
              obstacles[i].isVisible = false;
              ballX = obstacles[i].x - 5;
            }
            if (ballX - 5 <= obstacles[i].x + obstacles[i].width &&
                ballX - 5 >= obstacles[i].x) {
              isBallXIncreasing = !isBallXIncreasing;
              obstacles[i].isVisible = false;
              ballX = obstacles[i].x + obstacles[i].width + 5;
            }
          }
        }
      }

      DrawRectangle(boardX, screenHeight - 20, 200, 10, MAROON);
      DrawCircle(ballX, ballY, 5, WHITE);
      bool continueGame = false;
      for (int i = 0; i < 14; i++) {
        if (obstacles[i].isVisible) {
          continueGame = true;
          DrawRectangle(obstacles[i].x, obstacles[i].y, obstacles[i].width,
                        obstacles[i].height, obstacles[i].color);
        }
      }
      if (!continueGame)
        isGameOver = true;
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
  int x, y, width, height;
  bool isVisible;
  Color color;
} Block;

int main(void) {
  const int screenWidth = 1200;
  const int screenHeight = 1000;
  const int blockLayout[] = {4, 3, 4, 3};
  const int blockWidth = 200;
  const int blockHeight = 20;
  const int ballRadius = 5;
  const int ballSpeed = 7;
  const int boardWidth = 200;
  const int boardSpeed = 10;
  const Color colorArray[8] = {RED,    GREEN,  BLUE, YELLOW,
                               PURPLE, ORANGE, GOLD, PINK};

  int blockLayoutLength = sizeof(blockLayout) / sizeof(blockLayout[0]);

  int blockCount = 0;
  for (int i = 0; i < blockLayoutLength; i++) {
    blockCount += blockLayout[i];
  }

  InitWindow(screenWidth, screenHeight, "My awesome game POGGIES");
  SetTargetFPS(144);

  Block blocks[blockCount];

  bool isGameOver = true;
  int boardX, ballX, ballY;
  bool isBallXIncreasing, isBallYIncreasing;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    if (isGameOver) {
      DrawText("Press Space to start", 350, screenHeight / 2, 40, WHITE);
      if (IsKeyPressed(KEY_SPACE)) {
        int currentBlock = 0;
        for (int i = 0; i < blockLayoutLength; i++) {
          int x = (screenWidth - blockWidth * blockLayout[i]) / 2;
          for (int j = 0; j < blockLayout[i]; j++) {
            blocks[currentBlock].x = x;
            x += blockWidth;
            blocks[currentBlock].y = 50 + i * blockHeight;
            blocks[currentBlock].width = blockWidth;
            blocks[currentBlock].height = blockHeight;
            blocks[currentBlock].isVisible = true;
            blocks[currentBlock].color = colorArray[rand() % 8];
            currentBlock++;
          }
        }
        isBallXIncreasing = rand() % 2 == 0;
        isBallYIncreasing = false;
        ballX = rand() % screenWidth;
        ballY = rand() % (screenHeight / 2) + screenHeight / 4;
        boardX = (screenWidth - boardWidth) / 2;
        isGameOver = false;
      }
    } else {
      if (IsKeyDown(KEY_A)) {
        boardX -= boardSpeed;
        if (boardX < 0)
          boardX = 0;
      }
      if (IsKeyDown(KEY_D)) {
        boardX += boardSpeed;
        if (boardX > screenWidth - boardWidth)
          boardX = screenWidth - boardWidth;
      }
      ballX += (isBallXIncreasing ? 1 : -1) * ballSpeed;
      ballY += (isBallYIncreasing ? 1 : -1) * ballSpeed;
      if (ballX > screenWidth - ballRadius) {
        isBallXIncreasing = !isBallXIncreasing;
        ballX = screenWidth - ballRadius;
      }
      if (ballX < ballRadius) {
        isBallXIncreasing = !isBallXIncreasing;
        ballX = ballRadius;
      }
      if (ballY > screenHeight - ballRadius) {
        isGameOver = true;
      }
      if (ballY > screenHeight - 20 - ballRadius && ballX > boardX &&
          ballX < boardX + boardWidth) {
        isBallYIncreasing = !isBallYIncreasing;
        ballY = screenHeight - 20 - ballRadius;
      }
      if (ballY < ballRadius) {
        isBallYIncreasing = !isBallYIncreasing;
        ballY = ballRadius;
      }

      for (int i = 0; i < blockCount; i++) {
        if (blocks[i].isVisible) {
          if (ballX >= blocks[i].x && ballX <= blocks[i].x + blocks[i].width) {
            if (ballY + ballRadius >= blocks[i].y &&
                ballY + ballRadius <= blocks[i].y + blocks[i].height) {
              isBallYIncreasing = !isBallYIncreasing;
              blocks[i].isVisible = false;
              ballY = blocks[i].y - ballRadius;
            }
            if (ballY - ballRadius <= blocks[i].y + blocks[i].height &&
                ballY - ballRadius >= blocks[i].y) {
              isBallYIncreasing = !isBallYIncreasing;
              blocks[i].isVisible = false;
              ballY = blocks[i].y + blocks[i].height + ballRadius;
            }
          }
          if (ballY >= blocks[i].y && ballY <= blocks[i].y + blocks[i].height) {
            if (ballX + ballRadius >= blocks[i].x &&
                ballX + ballRadius <= blocks[i].x + blocks[i].width) {
              isBallXIncreasing = !isBallXIncreasing;
              blocks[i].isVisible = false;
              ballX = blocks[i].x - ballRadius;
            }
            if (ballX - ballRadius <= blocks[i].x + blocks[i].width &&
                ballX - ballRadius >= blocks[i].x) {
              isBallXIncreasing = !isBallXIncreasing;
              blocks[i].isVisible = false;
              ballX = blocks[i].x + blocks[i].width + ballRadius;
            }
          }
        }
      }

      DrawRectangle(boardX, screenHeight - 20, boardWidth, 10, MAROON);
      DrawCircle(ballX, ballY, ballRadius, WHITE);
      bool continueGame = false;
      for (int i = 0; i < blockCount; i++) {
        if (blocks[i].isVisible) {
          continueGame = true;
          DrawRectangle(blocks[i].x, blocks[i].y, blocks[i].width,
                        blocks[i].height, blocks[i].color);
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
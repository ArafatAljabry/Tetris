#pragma once

#include "board.h"
#include "pieces.h"
#include "IO.h"
#include <time.h>

#define WAIT_TIME 700 //Number of ms that passes before a piece moves down 1 block
class Game
{
public:
    Game(board* board, pieces* pieces, IO* IO, int ScreenHeight);

    void DrawScene();
    void CreateNewPiece();

    int mPosX, mPosY;      // Position of the piece that is falling down
    int mPiece, mRotation; // Type and rotation of the piece that is falling down

    private:

    int mScreenHeight;             // Screen height in pixels
    int mNextPosX, mNextPosY;      // Position of the next piece
    int mNextPiece, mNextRotation; // Type and rotation of the next piece

    board* mBoard;
    pieces* mPieces;
    IO* mIO;

    int GetRand(int a, int b);
    void InitGame();
    void DrawPiece(int x, int y, int piece, int rotation);
    void DrawBoard();
    
};

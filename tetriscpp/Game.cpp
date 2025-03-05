#include "Game.h"

#include <cstdlib>

Game::Game(board* board, pieces* pieces, IO* IO, int ScreenHeight)
{
}

void Game::DrawScene()
{
}

/**
 * Sets the next piece as the current one and resets its position.
 * Then, selects a newe "next piece"
 */
void Game::CreateNewPiece()
{
    //The next piece
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH/2) + mPieces->GetXInitialPos(mPiece,mRotation);
    mPosY = mPieces->GetYInitialPos(mPiece,mRotation);

    //Random next piece
    mNextPiece = GetRand(0,6);
    mNextRotation = GetRand(0,3); 
}

/**
 * Gets a random integer between two numbers
 * @param a First number
 * @param b Second number
 * @return Random int
 */
int Game::GetRand(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

/**
 *Initial parameters of the game;
 * Initalizes the game by selecting the first and next piece, next piece is shown to the player.
 * Also sets the position in blocks the pieces
 */
void Game::InitGame()
{
    //Init random numbers
    srand((unsigned int) time(NULL));

    //First piece
    mPiece = GetRand(0,6);
    mRotation = GetRand(0,3);
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPos(mPiece,mRotation);
    mPosY = mPieces->GetYInitialPos(mPiece,mRotation);

    mNextPiece = GetRand(0,6);
    mNextRotation = GetRand(0,3);
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
}

/**
 * Iterates through the piece matrix and draws each block of the piece.
 * Green for normal blocks and blue for pivot blocks.For drawing the rectangles
 * it calls to DrawRectangle method of the class "IO"
 * @param x Horizontal position in blocks
 * @param y Vertical position in blocks
 * @param piece Piece to draw
 * @param rotation 1 of the 4 possible rotations
 */
void Game::DrawPiece(int x, int y, int piece, int rotation)
{
    color mColor; // Color of the block

    // Obtain the positino in pixel on the screen of the block we want to draw
    int mPixelsX = mBoard->GetXPosInPixels(x);
    int mPixelsY = mBoard->GetYPosInPixels(y);

    // Travel the matrix of blocks of the piece and draw the blocks that are filled
    for (int i = 0; i < PIECE_BLOCKS; i++)
    {
        for (int j = 0; j <PIECE_BLOCKS; j++)
        {
            //Get the type of block and draw it with the correct color
            switch (mPieces->GetBlockType(piece,rotation,j,i))
            {
            case 1: mColor = GREEN;break; // For each block of the piece exept the pivot
            case 2: mColor = BLUE;break; // For the pivot   
                
            }
            if (mPieces->GetBlockType(piece,rotation,j,i) !=0)
            {
                mIO->DrawRectangle( mPixelsX + i * BLOCK_SIZE,
                                    mPixelsY + j * BLOCK_SIZE,
                                    (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
                                    mColor);
            }
        }
    }
}

void Game::DrawBoard()
{
    //Calculate the limits of the board in pixels
    int x1 = BOARD_POSITION - (BLOCK_SIZE *(BOARD_WIDTH/2)) - 1;
    int x2 = BOARD_POSITION + (BLOCK_SIZE *(BOARD_WIDTH/2));
    int y = mScreenHeight - (BLOCK_SIZE *(BOARD_HEIGHT));

    //Rectangles that delimits the board
    mIO->DrawRectangle(x1- BOARD_LINE_WIDTH, y, x2, mScreenHeight - 1, BLUE);
    mIO->DrawRectangle(x2,y,x2)
    
}

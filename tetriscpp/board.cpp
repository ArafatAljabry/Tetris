#include "board.h"

board::board(pieces* pieces, int ScreeHeight)
{
}

/**
 * Obtains the horizontal position in pixel given a position of a block
 * @param Pos Horizontal position of the block on the board
 * @return Horizontal position in pixel given parameter
 */
int board::GetXPosInPixels(int Pos)
{
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (Pos * BLOCK_SIZE) );
}

/**
 * Obtains the vertical position in pixel given a position of a block
 * @param Pos Vertical position of the block on the board
 * @return Vertical position on board in pixels
 */
int board::GetYPosInPixels(int Pos)
{
    return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (Pos * BLOCK_SIZE) );
}

/**
 * Checks out if a board block is filled or not
 * @param x Horizontal position in blocks
 * @param y Vertical position in blocks
 * @return True if the block of the board is empty, false if filled
 */
bool board::IsFreeBlock(int x, int y)
{
    if (mBoard[x][y] == POS_FREE) return true;

    return false;
}

/**
 * Checks if the pice can be stored at this position without any collision
 * @param x Horizontal position in blocks
 * @param y Vertical position in blocks
 * @param piece Piece to draw
 * @param rotation 1 of the 4 possible rotations
 * @return true if movement is possible, false otherwise
 */
bool board::IsPossibleMovement(int x, int y, int piece, int rotation)
{
    //Checks if collision with pieces already stored on the board or the board limits
    //This is to check a 5x5 block of a piece with the appropriate are on the board
    for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; i1++,i2++)
    {
       for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; j1++,j2++)
       {
           // Checks if the piece is outside the limits of the board
           if (i1 < 0 || i1> BOARD_WIDTH-1 || j1 > BOARD_HEIGHT-1)
           {
               if (mPiece->GetBlockType(piece,rotation,j2,i2) != 0)
               {
                   return 0;
               }
           }
               //Check if the piece have collisioned with a block already stored on the board
               if (j1 >= 0)
               {
                   if ((mPiece->GetBlockType(piece,rotation,j2,i2) != 0) &&( !IsFreeBlock(i1,j1)))
                       return false;
               }
       }
        
    }
    //No collision
    return true;
}

/**
 * Store a piece in the board by filling the blocks. Nested loop that iterates through the piece matrix
 * and store the block in the board, by setting the appropriate block as POS_FILLED
 * @param x Horizontal position in blocks
 * @param y Vertical position in blocks
 * @param piece Piece to draw
 * @param rotation 1 of the 4 possible rotations
 */
void board::StorePiece(int x, int y, int piece, int rotation)
{
    //Store each block of the piece into the board
    for (int i1 = x,i2 = 0; i1 < x + PIECE_BLOCKS; i1++,i2++)
    {
        for ( int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; j1++,j2++)
        {
            // Store only the blocks of the pice that are not holes ( not 0)
            if (mPiece->GetBlockType(piece, rotation,j2,i2) != 0)
            {
                mBoard[i1][j1] = POS_FILLED;
            }
        }
    }
}

/**
 * Delete all lines that should be removed. Checks a horizontal line block for block to see if the whole line is filled
 */
void board::DeletePossibleLines()
{
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int i = 0;
        while (i < BOARD_WIDTH)
        {
            if (mBoard[i][j] != POS_FILLED) break;
            i++;
        }

        if (i == BOARD_WIDTH) DeleteLine(j);
    }
}

/**
 * Check if the game is over because a piece have achieved the upper position
 * @return True or False
 */
bool board::IsGameOver()
{
    //If the first line has blocks, then game over
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (mBoard[i][0] == POS_FILLED) return true;
    }
    return false;
}

/**
 *Initalize the board blocks with free positions
 */
void board::InitBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i ++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j ++)
        {
            mBoard[i][j] = POS_FREE;
        }
    }
}

/**
 * Delete a line of the board by moving all above lines down.
 * Starts from the line that is being removed. 
 * @param y Vertical position in blocks of the line to delete
 */
void board::DeleteLine(int y)
{
    //Moves all upper lines one row down
    for (int j = y; j > 0; j--)
    {
        for (int i = 0; i < BOARD_WIDTH; i ++)
        {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
}

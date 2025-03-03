#include "pieces.h"

/**
 *  Returns the type of block to draw (0 = no-block, 1 = normal block, 2 = pivot block)
 * @param piece Piece to draw
 * @param rotation 1 of the 4 possible rotations
 * @param x Horizontal position in blocks
 * @param y Vertical position in blocks
 * @return The type of block(int)
 */
int pieces::GetBlockType(int piece, int rotation, int x, int y)
{
    return mPieces[piece][rotation][x][y]; 
}

/**
 * Returns the horizontal displacement of the piece that has to be applied
 * in order to create it in the coorect position
 * @param piece Piece to draw
 * @param rotation 1 of the 4 possible rotations
 * @return Horizontal displacement(int)
 */
int pieces::GetXInitialPos(int piece, int rotation)
{
    return mPiecesInitialPos[piece][rotation][0];
}

/**
 * Returns the vertical displacement of the piece that has to be applied
 * in order to create it in the correct position.
 * @param piece Piece to draw
 * @param rotation 1 of the 4 possible rotations
 * @return Vertical displacement(int)
 */
int pieces::GetYInitialPos(int piece, int rotation)
{
    return mPiecesInitialPos[piece][rotation][1];
}

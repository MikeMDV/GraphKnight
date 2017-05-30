/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 5/26/17
 *
 */

#include <vector>
#include <iostream>

#include "CommonDefs.h"
#include "MoveValidator.h"

int main(int argc, char *argv[])
{
    // Program to test MoveValidator class

    // Create an 8x8 board filled with '.' chars
    std::vector<std::vector<char> > board = 
        { {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'},
          {'.', '.', '.', '.', '.', '.', '.', '.'} };

    MoveValidator validator(board);

    // Comment 2nd and 3rd to test list of one Vertex
    Vertex vertOne(1, 2, std::numeric_limits<int>::max());
    Vertex vertTwo(3, 3, std::numeric_limits<int>::max());
    Vertex vertThree(5, 4, std::numeric_limits<int>::max());
    // Comment above and uncomment below to test an invalid move
    // Vertex vertThree(7, 4, std::numeric_limits<int>::max());

    std::vector<Vertex> moves;
    moves.push_back(vertOne);
    moves.push_back(vertTwo);
    moves.push_back(vertThree);

    bool printBoard = true;
    // Comment above and uncomment below to test no board printing
    // bool printBoard = false;

    bool areValidMoves = validator.validateMoves(moves, printBoard);

    return 0;
}
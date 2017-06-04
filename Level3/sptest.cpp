/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 06/03/17
 *
 */

#include <vector>
#include <iostream>

#include "CommonDefs.h"
#include "MoveValidator.h"
#include "KnightGraph.h"

int main(int argc, char *argv[])
{
    // Program to test KnightGraph class

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

    MoveValidator *validator = new MoveValidator(board);
    KnightGraph   *graph     = new KnightGraph(board);

    // int start_x = -1;
    // int start_y = 88;
    int start_x = 2;
    int start_y = 2;
    int end_x   = 3;
    int end_y   = 0;

    graph->bfsShortestPath(start_x, start_y, end_x, end_y);
    
    std::vector<Vertex> moves = graph->getPathToEnd();
    
    bool printBoard = true;
    // Comment above and uncomment below to test no board printing
    // bool printBoard = false;
    validator->validateMoves(moves, printBoard);

    return 0;
}

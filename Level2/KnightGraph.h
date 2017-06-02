#ifndef KNIGHT_GRAPH_H
#define KNIGHT_GRAPH_H

/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 05/30/17
 *
 */

#include <vector>
#include <iostream>

#include "CommonDefs.h"
#include "MoveValidator.h"

class KnightGraph
{
public:

    // Constructor
    KnightGraph(std::vector<std::vector<char> > board);

    // Destructor
    ~KnightGraph();

    /* Brief desc.       - A method to find a path to the end using depth-first 
     *                     search
     * param[in] x_start - X coordinate of the starting node
     * param[in] y_start - Y coordinate of the starting node
     * param[in] x_end   - X coordinate of the ending node
     * param[in] y_end   - Y coordinate of the ending node
     *
     */
    void dfsPathFind(int start_x, int start_y, int end_x, int end_y);

    /* Brief desc.       - A method to retrieve the path of moves to the end node 
     *
     */
    std::vector<Vertex> getPathToEnd();


private:

    /* Brief desc.       - A recursive method to visit nodes and return a vector
     *                     of Vertex structs to build the path to the end node
     * param[in] start_x - X coordinate of the starting node
     * param[in] start_y - Y coordinate of the starting node
     * param[in] end_x   - X coordinate of the ending node
     * param[in] end_y   - Y coordinate of the ending node
     *
     * param[out]        - A path to the end in reverse order; The function can
     *                     return an empty path if the end node was not found
     *
     */
    std::vector<Vertex> visitNext(int start_x, int start_y, int end_x, int end_y);

    /* Brief desc.     - A method to retrieve the next legal move
     * param[in] start - Starting node
     *
     * param[out]      - Vertex representing the next legal move
     *
     */
    Vertex getNextLegalMove(Vertex start);

    /* Brief desc.     - A method to check if a move is legal
     * param[in] start - Starting node
     * param[in] end   - Ending node
     *
     * param[out]      - True if the move was legal
     *
     */
    bool isLegalMove(Vertex start, Vertex end);

    // Attributes
    MoveValidator *m_validator;
    
    std::vector<std::vector<char> > m_board;

    std::vector<Vertex> m_nodes;

    std::vector<Vertex> m_path;

};

#endif // KNIGHT_GRAPH_H

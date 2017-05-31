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

    /* Brief desc.       - A method to build a graph of knight moves and a path 
     *                     to the end using depth-first search
     * param[in] x_start - X coordinate of the starting node
     * param[in] y_start - Y coordinate of the starting node
     * param[in] x_end   - X coordinate of the ending node
     * param[in] y_end   - Y coordinate of the ending node
     *
     */
    void dfsGraphBuild(int start_x, int start_y, int end_x, int end_y);

    /* Brief desc.       - A method to retrieve the adjacency matrix showing the 
     *                     connections between nodes in the graph
     *
     */
    std::vector<std::vector<bool> > getAdjMatrix();

    /* Brief desc.       - A method to retrieve the path of move to the end node 
     *
     */
    std::vector<Vertex> getPathToEnd();


private:



    // Attributes
    std::vector<std::vector<char> > m_board;

    std::vector<Vertex> m_nodes;

    std::vector<Vertex> m_path;

    std::vector<std::vector<bool> > m_adj_matrix;

};

#endif // KNIGHT_GRAPH_H
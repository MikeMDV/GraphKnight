#ifndef KNIGHT_GRAPH_H
#define KNIGHT_GRAPH_H

/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 06/25/17
 *
 */

#include <deque>
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

    /* Brief desc.       - A method to find a path to the end using a modified 
     *                     depth-first search
     * Note              - dfsGraphBuild() assumes the graph is unweighted
     * param[in] x_start - X coordinate of the starting node
     * param[in] y_start - Y coordinate of the starting node
     *
     */
    void dfsGraphBuild(int start_x, int start_y);

    /* Brief desc.       - A method to find a shortest path to the end using 
     *                     breadth-first search
     * Note              - bfsShortestPath() assumes the graph is unweighted
     * param[in] x_start - X coordinate of the starting node
     * param[in] y_start - Y coordinate of the starting node
     * param[in] x_end   - X coordinate of the ending node
     * param[in] y_end   - Y coordinate of the ending node
     *
     */
    void bfsShortestPath(int start_x, int start_y, int end_x, int end_y);

    /* Brief desc.       - A method to find a shortest path to the end using 
     *                     Dijkstra's algorithm
     * param[in] x_start - X coordinate of the starting node
     * param[in] y_start - Y coordinate of the starting node
     * param[in] x_end   - X coordinate of the ending node
     * param[in] y_end   - Y coordinate of the ending node
     *
     */
    void daShortestPath(int start_x, int start_y, int end_x, int end_y);

    /* Brief desc. - A method to retrieve the path of moves to the end node 
     *
     */
    std::vector<Vertex> getPathToEnd();


private:

    /* Brief desc.       - A recursive method to visit nodes and build the
     *                     adjacency matrix
     * param[in] start_x - X coordinate of the starting node
     * param[in] start_y - Y coordinate of the starting node
     *
     */
    void dfsVisitNext(int start_x, int start_y);

    // Attributes
    MoveValidator *m_validator;
    
    std::vector<std::vector<char> > m_board;

    std::vector<Vertex> m_nodes;

    std::vector<Vertex> m_path;

    std::deque<Vertex> m_node_queue;

    int m_board_row_size;

    int m_node_count;

    std::vector<std::vector<int> > m_adj_matrix;

};

#endif // KNIGHT_GRAPH_H

#ifndef KNIGHT_GRAPH_H
#define KNIGHT_GRAPH_H

/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 07/02/17
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

    /* Brief desc.        - A method to find the approximate longest path to the 
     *                      end node
     * param[in] x_start  - X coordinate of the starting node
     * param[in] y_start  - Y coordinate of the starting node
     * param[in] x_end    - X coordinate of the ending node
     * param[in] y_end    - Y coordinate of the ending node
     * param[in] searches - The number of searches that should be performed
     *
     */
    void apprLongestPath(int start_x, int start_y, int end_x, int end_y, 
        int searches);

    /* Brief desc. - A method to retrieve the path of moves to the end node 
     *
     */
    std::vector<Vertex> getPathToEnd();

    /* Brief desc. - A method to print the length of m_path, calculating extra 
     *               moves for water and lava nodes
     *
     */
    void printCalculatedPathLengthAndPercent();

private:

    /* Brief desc.       - A recursive method to visit nodes and build the
     *                     adjacency matrix
     * param[in] start_x - X coordinate of the starting node
     * param[in] start_y - Y coordinate of the starting node
     *
     */
    void dfsVisitNext(int start_x, int start_y);

    /* Brief desc.        - A method to retrieve the neighbor(s) with the least
     *                      degree (number of nodes connected)
     * param[in] position - Vertex representing the start position
     *
     * param[out]         - Returns vector of Vertex of neighbors with the least
     *                      degree
     *
     */
    std::vector<Vertex> getLeastDegreeNeighbors(Vertex start);

    /* Brief desc.        - A method to retrieve the sum of the degrees of the 
     *                      neighbor(s) of the node
     * param[in] position - Vertex representing the start position
     *
     * param[out]         - Returns an int for the sum of the degrees
     *
     */
    int getSumOfDegreesOfNeighbors(Vertex start);

    /* Brief desc. - For all m_nodes, set distance, parent node, and visited to 
     *               default values
     *
     */
    void setM_nodeValsToDefaults();

    /* Brief desc.   - Returns the longest path from the m_path_store
     * param[in] end - Vertex representing the end position
     *
     * param[out]    - Returns an vector of Vertex
     *
     */
    std::vector<Vertex> getLongestPathFromPathStore(Vertex end);

    /* Brief desc.     - Build the path in reverse order from the path end node 
     *                   and store in m_path
     * param[in] start - Vertex representing the start position
     * param[in] end   - Vertex representing the end position
     *
     */
    void buildPathInReverse(Vertex start, Vertex end);

    // Attributes
    MoveValidator *m_validator;
    
    std::vector<std::vector<char> > m_board;

    std::vector<Vertex> m_nodes;

    std::vector<Vertex> m_path;

    std::deque<Vertex> m_node_queue;

    int m_board_row_size;

    int m_node_count;

    std::vector<std::vector<int> > m_adj_matrix;

    std::vector<std::vector<Vertex> > m_path_store;
};

#endif // KNIGHT_GRAPH_H

/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 06/03/17
 *
 */

#include <iostream>

#include "KnightGraph.h"


KnightGraph::KnightGraph(std::vector<std::vector<char> > board)
    : m_board(board)
{
    // Construct vector of Vertex structs
    for (int i = 0; i < m_board.size(); i++)
    {
        for (int j = 0; j < m_board[0].size(); j++)
        {
            Vertex vert(j, i);
            m_nodes.push_back(vert);
        }
    }

    // Initialize adjacency matrix with 0 for all nodes
    int node_count = m_board.size() * m_board[0].size();
    std::vector<std::vector<int> > m_adj_matrix(node_count, 
        std::vector<int>(node_count));

    // Initialize MoveValidator object
    m_validator = new MoveValidator(board);
}

KnightGraph::~KnightGraph()
{
    if (m_validator)
    {
        delete m_validator;
    }

    if (m_adj_matrix)
    {
        delete m_adj_matrix;
    }
}

/* Algorithm - Confirm that the start node is on the board
 *           - Call dfsVisitNext() to use DFS to build the adjacency matrix until
 *             a point is reached where a move to an unvisited node is not 
 *             possible
 *           - Check m_nodes for the first unvisited node and begin DFS again 
 *             from that node
 * 
 */
void KnightGraph::dfsGraphBuild(int start_x, int start_y)
{
    // Verify start node is on board
    Vertex start(start_x, start_y);
    bool start_is_on_board = m_validator->onBoard(start);

    if (start_is_on_board)
    {
        // Call visitNext() to use DFS to build adjacency matrix
        dfsVisitNext(start_x, start_y);
    }
    else
    {
        std::cout << "Start node is invalid.\n";
    }
}

/* Algorithm - Call dfsGraphBuild() to build the adjacency matrix
 *           - Call      to use BFS to retrieve a shortest path to the end node
 * 
 */
void KnightGraph::bfsShortestPath(int start_x, int start_y, 
    int end_x, int end_y)
{


}

/* Algorithm - Mark current node visited
 *           - Get the legal moves available from the current node
 *           - Add node connections to adjancency matrix
 *           - Check for the first node of the returned list of moves that has 
 *             not been visited
 *           - If no unvisited legal moves exist, return (base case)
 *           - Otherwise, set next_x and next_y to the next unvisited legal move
 *           - Visit next_x and next_y (recursive call)
 * 
 */
void KnightGraph::dfsVisitNext(int start_x, int start_y)
{
    // Create Vertex for current node
    Vertex current_node(start_x, start_y);

    // Mark current node visited
    auto result = std::find_if(
        std::begin(m_nodes), std::end(m_nodes), match_num(current_node.number));
    if (result != std::end(m_nodes))
    {
        result->visited = true;
    }

    // Get available legal moves
    std::vector<Vertex> legal_moves = m_validator->getLegalMoves(current_node);

    // Add node connections to adjancency matrix

    // Check for first unvisited legal move
    int position = -1;
    for (int i = 0; i < legal_moves.size(); i++)
    {
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(legal_moves[i].number));
        if ((result != std::end(m_nodes)) && !result->visited)
        {
            position = i;
            i = legal_moves.size();
        }
    }

    // Determine next node
    int next_x = -1;
    int next_y = -1;

    if (position != -1)
    {
        next_x = legal_moves[position].x;
        next_y = legal_moves[position].y;
    }
    else
    {
        // No unvisited legal moves exist; Return

        return;
    }

    // Visit next node
    dfsVisitNext(next_x, next_y);
}

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}


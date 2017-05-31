/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 05/30/17
 *
 */

#include "KnightGraph.h"
// #include "MoveValidator.h"


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

    // Initialize MoveValidator object
    MoveValidator m_validator(board);
}

KnightGraph::~KnightGraph()
{
    // Empty
}

/* Algorithm - 
 * 
 */
void KnightGraph::dfsPathFind(int start_x, int start_y, int end_x, int end_y)
{
    // Call visitNext() to begin DFS search for path to end
    std::vector<Vertex> reverse_path = visitNext(start_x, start_y, end_x, end_y);
    
    // Assign each Vertex to m_path in reverse order
    for (int i = 0; i < reverse_path.size(); i++)
    {
        m_path.push_back(reverse_path.back());
        reverse_path.pop_back();
    }
}

std::vector<Vertex> KnightGraph::visitNext(int start_x, int start_y, int end_x, int end_y)
{
    // Mark current node visited
    int number = (start_y * 8) + start_x;
    auto result = std::find_if(std::begin(m_nodes), std::end(m_nodes), match_num(number));
    if (result != std::end(m_nodes))
    {
        result->visited = true;
    }
    
    // Create Vertex for current node and vector for path
    Vertex current_node(start_x, start_y);
    std::vector<Vertex> path;
    
    // Check if current node equals end and if so, push_back current Vertex and 
    // return
    if (start_x == end_x && start_y == end_y)
    {
        path.push_back(current_node);
        return path;
    }
    
    // Check if move to 1 o'clock position is legal
    bool print_board = false;
    std::vector<Vertex> move;
    
    move.push_back(current_node);
    Vertex position_one(start_x + 1, start_y + 2);
    move.push_back(position_one);
    if (m_validator->validateMoves(move, print_board))
    {
        // Check if node is visited
    }

    return path;
}

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}


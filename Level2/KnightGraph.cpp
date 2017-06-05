/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 06/03/17
 *
 */

#include <iostream>
#include <algorithm>

#include "KnightGraph.h"


KnightGraph::KnightGraph(std::vector<std::vector<char> > board)
    : m_board(board)
{
    // Construct vector of Vertex structs
    for (unsigned int i = 0; i < m_board.size(); i++)
    {
        for (unsigned int j = 0; j < m_board[0].size(); j++)
        {
            Vertex vert(j, i);
            m_nodes.push_back(vert);
        }
    }

    // Initialize MoveValidator object
    m_validator = new MoveValidator(board);
}

KnightGraph::~KnightGraph()
{
    if (m_validator)
    {
        delete m_validator;
    }
}

/* Algorithm - Confirm that the start and end nodes are on the board
 *           - Call visitNext() to use DFS to retrieve a path to the end node
 * 
 */
void KnightGraph::dfsPathFind(int start_x, int start_y, int end_x, int end_y)
{
    // Verify start and end nodes are on board
    Vertex start(start_x, start_y);
    Vertex end(end_x, end_y);
    bool start_is_on_board = m_validator->onBoard(start);
    bool end_is_on_board   = m_validator->onBoard(end);

    if (start_is_on_board && end_is_on_board)
    {
        // Call visitNext() to begin DFS search for reverse path to end
        visitNext(start_x, start_y, end_x, end_y);
    }
    else
    {
        std::cout << "Start or end node is invalid.\n";
    }
}

/* Algorithm - Mark current node visited
 *           - Add current node to m_path
 *           - Check if current node is the end node; If so, return (base case)
 *           - Get the legal moves available from the current node
 *           - Check for the first node of the returned list of moves that has 
 *             not been visited
 *           - If no unvisited legal moves exist, set next_x and next_y to 
 *             previous node visited
 *           - Otherwise, set next_x and next_y to the next unvisited legal move
 *           - Visit next_x and next_y (recursive call)
 * 
 */
void KnightGraph::visitNext(int start_x, int start_y, int end_x, int end_y)
{
    // Create Vertex for current node
    Vertex current_node(start_x, start_y);

    // Mark current node visited and add to m_path
    auto result = std::find_if(
        std::begin(m_nodes), std::end(m_nodes), match_num(current_node.number));
    if (result != std::end(m_nodes))
    {
        result->visited = true;
        m_path.push_back(current_node);
    }
    
    // Check if current node position equals end node and if so, return
    if (start_x == end_x && start_y == end_y)
    {
        return;
    }

    // Get available legal moves
    std::vector<Vertex> legal_moves = m_validator->getLegalMoves(current_node);

    // Check for first unvisited legal move
    int position = -1;
    for (unsigned int i = 0; i < legal_moves.size(); i++)
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
    int next_x;
    int next_y;

    if (position != -1)
    {
        next_x = legal_moves[position].x;
        next_y = legal_moves[position].y;
    }
    else
    {
        // No unvisited legal moves exist; Move back one node and check for move

        // Pop current node off path
        m_path.pop_back();

        if (!m_path.empty())
        {
            // Retrieves coordinates of previous node
            next_x = m_path.back().x;
            next_y = m_path.back().y;
        }

        // Pop previous node off path so it is not added twice
        m_path.pop_back();
    }

    // Visit next node
    visitNext(next_x, next_y, end_x, end_y);
}

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}


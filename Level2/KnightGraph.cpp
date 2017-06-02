/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 05/30/17
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

/* Algorithm - Call visitNext() to use DFS to retrieve a path to the end node
 *           - Assign the Vertex structs from the returned path to m_path in 
 *             reverse order
 * 
 */
void KnightGraph::dfsPathFind(int start_x, int start_y, int end_x, int end_y)
{
    // Call visitNext() to begin DFS search for reverse path to end
    visitNext(start_x, start_y, end_x, end_y);
    
    // Reverse path and assign to m_path
    // std::reverse(std::begin(path), std::end(path));
    // m_path = path;
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
    // Create Vertex for current node and vector for path
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
    std::vector<Vertex> legal_moves = getLegalMoves(current_node);

    // Check if legal moves have been visited

    // If no unvisited legal move, 
    
/*    // Check if move to 1 o'clock position is legal
    Vertex position_one(start_x + 1, start_y - 2);
    if (isLegalMove(current_node, position_one))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_one.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 2 o'clock position is legal
    Vertex position_two(start_x + 2, start_y - 1);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_two.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 4 o'clock position is legal
    Vertex position_three(start_x + 2, start_y + 1);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_three.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 5 o'clock position is legal
    Vertex position_four(start_x + 1, start_y + 2);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_four.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 7 o'clock position is legal
    Vertex position_five(start_x - 1, start_y + 2);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_five.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 8 o'clock position is legal
    Vertex position_six(start_x - 2, start_y + 1);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_six.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 10 o'clock position is legal
    Vertex position_seven(start_x - 2, start_y - 1);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_seven.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }

    // Check if move to 11 o'clock position is legal
    Vertex position_eight(start_x - 1, start_y - 2);
    if (isLegalMove(current_node, position_two))
    {
        // Check if node has been visited
        auto result = std::find_if(
            std::begin(m_nodes), std::end(m_nodes), 
            match_num(position_eight.number));
        if (!result->visited)
        {
            // Visit the node
            path = visitNext(result->x, result->y, end_x, end_y);
        }

        // Check if returned path has the end node at front 
        if ((path.size() >= 1) 
            && (path.front().x == end_x && path.front().y == end_y))
        {
            // Add current node to path and return
            path.push_back(current_node);
            return path;
        }
    }*/

    std::cout << "Control reached end of visitNext\n";
}

/* Algorithm - Check for next legal move starting with 1 o'clock position, 
 *             followed by 2:00, 4:00, 5:00, 7:00, 8:00, 10:00, 11:00
 * 
 */
 std::vector<Vertex> KnightGraph::getLegalMoves(Vertex start)
 {
    std::vector<Vertex> legal_moves;

    // Check if move to 1 o'clock position is legal
    Vertex move(start.x + 1, start.y - 2);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 2 o'clock position is legal
    move = Vertex(start.x + 2, start.y - 1);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 4 o'clock position is legal
    move = Vertex(start.x + 2, start.y + 1);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 5 o'clock position is legal
    move = Vertex(start.x + 1, start.y + 2);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 7 o'clock position is legal
    move = Vertex(start.x - 1, start.y + 2);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 8 o'clock position is legal
    move = Vertex(start.x - 2, start.y + 1);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 10 o'clock position is legal
    move = Vertex(start.x - 2, start.y - 1);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 10 o'clock position is legal
    move = Vertex(start.x - 1, start.y - 2);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    return legal_moves;

 }

/* Algorithm - 
 * 
 */
bool KnightGraph::isLegalMove(Vertex start, Vertex end)
{
    // Check legality of move
    bool print_board = false;
    std::vector<Vertex> move;
    
    move.push_back(start);
    move.push_back(end);
    
    return (m_validator->validateMoves(move, print_board));
}

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}


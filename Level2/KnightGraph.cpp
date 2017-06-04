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
    std::cout << "Entered visitNext()\n";
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
        m_path.pop_back();
        next_x = m_path.back().x;
        next_y = m_path.back().y;
    }

    // Visit next node
    visitNext(next_x, next_y, end_x, end_y);
}

/* Algorithm - Check for next legal move starting with 1 o'clock position, 
 *             followed by 2:00, 4:00, 5:00, 7:00, 8:00, 10:00, 11:00
 * 
 */
 std::vector<Vertex> KnightGraph::getLegalMoves(Vertex start)
 {
    std::cout << "Entered getLegalMoves()\n";
    std::vector<Vertex> legal_moves;

    // Check if move to 1 o'clock position is legal
    Vertex move(start.x + 1, start.y - 2);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 1\n";
        legal_moves.push_back(move);
    }

    // Check if move to 2 o'clock position is legal
    move = Vertex(start.x + 2, start.y - 1);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 2\n";
        legal_moves.push_back(move);
    }

    // Check if move to 4 o'clock position is legal
    move = Vertex(start.x + 2, start.y + 1);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 3\n";
        legal_moves.push_back(move);
    }

    // Check if move to 5 o'clock position is legal
    move = Vertex(start.x + 1, start.y + 2);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 4\n";
        legal_moves.push_back(move);
    }

    // Check if move to 7 o'clock position is legal
    move = Vertex(start.x - 1, start.y + 2);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 5\n";
        legal_moves.push_back(move);
    }

    // Check if move to 8 o'clock position is legal
    move = Vertex(start.x - 2, start.y + 1);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 6\n";
        legal_moves.push_back(move);
    }

    // Check if move to 10 o'clock position is legal
    move = Vertex(start.x - 2, start.y - 1);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 7\n";
        legal_moves.push_back(move);
    }

    // Check if move to 10 o'clock position is legal
    move = Vertex(start.x - 1, start.y - 2);
    if (isLegalMove(start, move))
    {
        std::cout << "About to push back pos 8\n";
        legal_moves.push_back(move);
    }

    std::cout << "getLegalMoves(): About to return vector: legal_moves\n";
    return legal_moves;

 }

/* Algorithm - 
 * 
 */
bool KnightGraph::isLegalMove(Vertex start, Vertex end)
{
    std::cout << "Entered isLegalMove()\n";
    // Check legality of move
    bool print_board = false;
    std::vector<Vertex> move;
    
    move.push_back(start);
    move.push_back(end);
    std::cout << "isLegalMove(): About to call validateMoves()\n";
    bool output = m_validator->validateMoves(move, print_board);
    std::cout << "isLegalMove(): About to return output\n";
    return (output);
    // return (m_validator->validateMoves(move, print_board));
}

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}


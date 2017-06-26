/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 06/24/17
 *
 */

#include <iostream>
#include <vector>

#include "MoveValidator.h"

MoveValidator::MoveValidator(std::vector<std::vector<char> > board)
    : m_board(board),
    m_board_row_size(m_board[0].size())
{
    // Find first teleport node
    for (unsigned int i = 0; i < m_board.size(); i++)
    {
        for (unsigned int j = 0; j < m_board[0].size(); j++)
        {
            if (m_board[i][j] == 'T')
            {
                m_teleport_node_one = new Vertex(j, i, m_board_row_size);
            }
        }
    }

    // Find second teleport node
    for (unsigned int i = 0; i < m_board.size(); i++)
    {
        for (unsigned int j = 0; j < m_board[0].size(); j++)
        {
            if (m_board[i][j] == 'T' 
                && (i != m_teleport_node_one->y || j != m_teleport_node_one->x))
            {
                m_teleport_node_two = new Vertex(j, i, m_board_row_size);
            }
        }
    }
}

MoveValidator::~MoveValidator()
{
    // Empty
}

/* Algorithm - Check the starting and ending points of the move set and set them
 *             to S and E on the board
 *           - Print the board if necessary
 *           - Loop through moves: 
 *               - Set current knight position to K on board
 *               - Print board if necessary
 *               - Check if move is valid
 *           - If all moves are valid, return true, otherwise return false
 * 
 */
bool MoveValidator::validateMoves(std::vector<Vertex> moves, bool print_moves)
{
    // Retrieve starting and ending points and set them to 'S' and 'E'
    if (!moves.empty())
    {
        if (print_moves && isOnBoard(moves.front()))
        {
            m_board[moves.front().y][moves.front().x] = 'S';
        }
        if (print_moves && isOnBoard(moves.back()))
        {
            m_board[moves.back().y][moves.back().x]   = 'E';
        }
        
    }
    else
    {
        // Empty moves path provided; Return false
        return false;
    }
    
    if (print_moves)
    {
        printBoard(m_board);
    }

    bool all_moves_are_valid = true;
    bool is_valid_move       = true;

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        // Set current knight position to 'K' on board
        if (print_moves && isOnBoard(moves[i]))
        {
            m_board[moves[i].y][moves[i].x] = 'K';
        }

        // Print board if necessary
        if (print_moves)
        {
            printBoard(m_board);
        }

        // If a move is present, check if it is valid 
        if (i < (moves.size() - 1))
        {
            is_valid_move = checkMove(moves[i], moves[i + 1]);

            if (!is_valid_move)
            {
                if (print_moves)
                {
                    std::cout << "Current position: (" << moves[i].x << ", "
                          << moves[i].y << ")\n";
                    std::cout << "The next move to (" << moves[i + 1].x << ", "
                          << moves[i + 1].y << ") is invalid.\n";
                }
                
                i = moves.size();
                all_moves_are_valid = false;
            }
        }

    }

    if (all_moves_are_valid && print_moves)
    {
        std::cout << "All the moves were valid.\n";
    }
    // std::cout << "MoveValidator::validateMoves - About to return all_moves_are_valid\n";
    return all_moves_are_valid;
}

/* Algorithm - Create a set of legal moves starting with 1 o'clock position, 
 *             followed by 2:00, 4:00, 5:00, 7:00, 8:00, 10:00, 11:00
 * 
 */
 std::vector<Vertex> MoveValidator::getLegalMoves(Vertex start)
 {
    // std::cout << "MoveValidator::getLegalMoves - Entered\n";
    std::vector<Vertex> legal_moves;

    // Check if move to 1 o'clock position is legal
    Vertex move(start.x + 1, start.y - 2, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 2 o'clock position is legal
    move = Vertex(start.x + 2, start.y - 1, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 4 o'clock position is legal
    move = Vertex(start.x + 2, start.y + 1, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 5 o'clock position is legal
    move = Vertex(start.x + 1, start.y + 2, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 7 o'clock position is legal
    move = Vertex(start.x - 1, start.y + 2, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 8 o'clock position is legal
    move = Vertex(start.x - 2, start.y + 1, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 10 o'clock position is legal
    move = Vertex(start.x - 2, start.y - 1, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    // Check if move to 10 o'clock position is legal
    move = Vertex(start.x - 1, start.y - 2, m_board_row_size);
    if (isLegalMove(start, move))
    {
        legal_moves.push_back(move);
    }

    return legal_moves;
 }

/* Algorithm - Check if position is valid; Position is valid if it is located 
 *             on the board
 * 
 */
bool MoveValidator::isOnBoard(Vertex position)
{
    // std::cout << "MoveValidator::isOnBoard - Entered\n";
    bool position_is_on_board  = true;

    if ((position.x < 0 || position.x >= static_cast<int>(m_board[0].size()))
        || (position.y < 0 || position.y >= static_cast<int>(m_board.size())))
    {
        position_is_on_board = false;
    }

    return position_is_on_board;
}

/* Algorithm - Check if position is a rock
 * 
 */
bool MoveValidator::isRock(Vertex position)
{
    bool position_is_rock = false;

    // Check if position is a rock
    if (isOnBoard(position) && m_board[position.y][position.x] == 'R')
    {
        position_is_rock = true;
    }

    return position_is_rock;
}

/* Algorithm - Check if position is a barrier
 * 
 */
bool MoveValidator::isBarrier(Vertex position)
{
    bool position_is_barrier = false;

    // Check if position is a barrier
    if (isOnBoard(position) && m_board[position.y][position.x] == 'B')
    {
        position_is_barrier = true;
    }

    return position_is_barrier;
}

/* Algorithm - Return the teleport node that is connected to position
 * 
 */
Vertex MoveValidator::getTeleportNode(Vertex position)
{
    if (isOnBoard(position))
    {
        if (isOnBoard(position) && position.number == m_teleport_node_one->number)
        {
            return *m_teleport_node_two;
        }
        else
        {
            return *m_teleport_node_one;
        }
    }
    else
    {
        // This shouldn't happen
        std::cout << "Unexpected error in getTeleportNode\n";
        Vertex error(-1, -1, -1);
        return error;
    }
}

/* Algorithm - Loop through each row and print each character
 * 
 */
void MoveValidator::printBoard(std::vector<std::vector<char> > board)
{
    // Loop through board and print each character
    for (unsigned int i = 0; i < board.size(); i++)
    {
        for (unsigned int j = 0; j < board[i].size(); j++)
        {
            std::cout << board[i][j] << " ";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

/* Algorithm - Check if move is valid; Move is valid if the knight moves in an
 *             L shape - horizontal 2 spaces, then vertical 1 space, or vertical 
 *             2 spaces, then horizontal 1 space; The destination must not be 
 *             located beyond the edge of the board; The destination must not be
 *             a rock; The destination must not be a barrier and a barrier must
 *             not lie within the path of the move
 *
 * Note      - If the destination is a teleport node, the origin must be a
 *             teleport node; If both are teleport nodes, the move is valid
 * 
 */
bool MoveValidator::checkMove(Vertex origin, Vertex destination)
{
    // std::cout << "MoveValidator::checkMove - Entered\n";
    // Check if move is valid
    bool is_valid_shape  = false;
    bool dest_on_board   = false;
    bool dest_is_rock    = false;
    bool dest_is_barrier = false;
    bool dest_is_blocked = false;
    bool tests_passed    = false;

    // Check if move is proper L shape
    if ((destination.x == (origin.x + 2)) && 
       ((destination.y == (origin.y + 1)) || (destination.y == (origin.y - 1))))
    {
        is_valid_shape = true;
    }
    else if ((destination.x == (origin.x - 2)) && 
       ((destination.y == (origin.y + 1)) || (destination.y == (origin.y - 1))))
    {
        is_valid_shape = true;
    }
    else if ((destination.y == (origin.y + 2)) && 
       ((destination.x == (origin.x + 1)) || (destination.x == (origin.x - 1))))
    {
        is_valid_shape = true;
    }
    else if ((destination.y == (origin.y - 2)) && 
       ((destination.x == (origin.x + 1)) || (destination.x == (origin.x - 1))))
    {
        is_valid_shape = true;
    }

    // Check if destination is beyond the edge of the board
    if (isOnBoard(destination))
    {
        dest_on_board = true;
    }

    // Check if destination is a rock
    if (dest_on_board && isRock(destination))
    {
        dest_is_rock = true;
    }

    // Check if destination is a barrier
    if (dest_on_board && isBarrier(destination))
    {
        dest_is_barrier = true;
    }

    // Check if destination is blocked by barrier
    if (dest_on_board && moveIsBlocked(origin, destination))
    {
        dest_is_blocked = true;
    }

    if (is_valid_shape && dest_on_board && !dest_is_rock && !dest_is_barrier
        && !dest_is_blocked)
    {
        tests_passed = true;
    }
    else if (dest_on_board 
            && ((origin.number == m_teleport_node_one->number 
            && destination.number == m_teleport_node_two->number)
            || (origin.number == m_teleport_node_two->number 
            && destination.number == m_teleport_node_one->number)))
    {
        // Both nodes are teleport nodes, the move is valid
        tests_passed = true;
    }

    return tests_passed;
}

/* Algorithm - Call validateMoves() to verify legality of move
 * 
 */
bool MoveValidator::isLegalMove(Vertex start, Vertex end)
{
    // std::cout << "MoveValidator::isLegalMove - Entered\n";
    // Check legality of move
    bool print_board = false;
    std::vector<Vertex> move;
    
    move.push_back(start);
    move.push_back(end);
    // std::cout << "MoveValidator::isLegalMove - About to call validateMoves()\n";
    return (validateMoves(move, print_board));
}

/* Algorithm - Check if the move is blocked; The move is blocked if one of the
 *             two nodes comprising the horizontal or vertical run of the move
 *             are a barrier (B). This function will not check if the
 *             destination is a barrier
 * 
 */
bool MoveValidator::moveIsBlocked(Vertex start, Vertex end)
{
    // std::cout << "MoveValidator::moveIsOpen - Entered\n";
    bool move_is_blocked = false;
    int  horizontal_diff = 0;
    int  vertical_diff   = 0;

    horizontal_diff = end.x - start.x;
    vertical_diff   = end.y - start.y;

    // Check two nodes in path for barrier
    if (abs(horizontal_diff) > abs(vertical_diff))
    {
        // Move is 2 nodes horizontal first
        if (m_board[start.y][end.x] == 'B')
        {
            // Second horizontal node is a barrier
            move_is_blocked = true;
        }
        else
        {
            // Check first horizontal node in path
            if (horizontal_diff < 0)
            {
                // Move horizontal to left
                if (m_board[start.y][start.x - 1] == 'B')
                {
                    // First horizontal node is a barrier
                    move_is_blocked = true;
                }
            }
            else
            {
                // Move is horizontal to right
                if (m_board[start.y][start.x + 1] == 'B')
                {
                    // First horizontal node is a barrier
                    move_is_blocked = true;
                }
            }
        }
    }
    else
    {
        // Move is 2 nodes vertical first
        if (m_board[end.y][start.x] == 'B')
        {
            // Second vertical node is a barrier
            move_is_blocked = true;
        }
        else
        {
            // Check first vertical node in path
            if (vertical_diff < 0)
            {
                // Move vertical up
                if (m_board[start.y - 1][start.x] == 'B')
                {
                    // First vertical node is a barrier
                    move_is_blocked = true;
                }
            }
            else
            {
                // Move is vertical down
                if (m_board[start.y + 1][start.x] == 'B')
                {
                    // First vertical node is a barrier
                    move_is_blocked = true;
                }
            }
        }
    }

    return move_is_blocked;
}



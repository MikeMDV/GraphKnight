/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 06/05/17
 *
 */

#include <vector>

#include "MoveValidator.h"

MoveValidator::MoveValidator(std::vector<std::vector<char> > board)
    : m_board(board)
{
    // Empty
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
bool MoveValidator::validateMoves(
        std::vector<Vertex> moves,
        bool print_moves)
{
    // Retrieve starting and ending points and set them to 'S' and 'E'
    if (!moves.empty())
    {
        if (onBoard(moves.front()))
        {
            m_board[moves.front().y][moves.front().x] = 'S';
        }
        if (onBoard(moves.back()))
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
        if (onBoard(moves[i]))
        {
            m_board[moves[i].y][moves[i].x] = 'K';
        }

        // Print board if necessary
        if (print_moves)
        {
            printBoard(m_board);
        }

        // If another move is present, check if it is valid 
        if (i < (moves.size() - 1))
        {
            is_valid_move = checkMove(moves[i], moves[i + 1]);

            if (!is_valid_move)
            {
                std::cout << "Current position: (" << moves[i].x << ", "
                          << moves[i].y << ")\n";
                std::cout << "The next move to (" << moves[i + 1].x << ", "
                          << moves[i + 1].y << ") is invalid.\n";
                i = moves.size();
                all_moves_are_valid = false;
            }
        }

    }

    if (all_moves_are_valid)
    {
        std::cout << "All the moves were valid.\n";
    }

    return all_moves_are_valid;
}

/* Algorithm - Check if position is valid; Position is valid if it is located 
 *             on the board
 * 
 */
bool MoveValidator::onBoard(Vertex position)
{
    bool position_is_on_board = true;

    if ((position.x < 0 || position.x >= static_cast<int>(m_board[0].size()))
        || (position.y < 0 || position.y >= static_cast<int>(m_board.size())))
    {
        position_is_on_board = false;
    }

    return position_is_on_board;
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
 *             2 spaces, then horizontal 1 space; also the destination must not 
 *             be located beyond the edge of the board
 * 
 */
bool MoveValidator::checkMove(
        Vertex origin, 
        Vertex destination)
{
    // Check if move is valid
    bool is_valid_shape   = false;
    bool dest_beyond_edge = false;
    bool tests_passed     = false;

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
    if ((destination.x < 0 
        || destination.x > static_cast<int>(m_board[0].size() - 1))
        || (destination.y < 0 
        || destination.y > static_cast<int>(m_board.size() - 1)))
    {
        dest_beyond_edge = true;
    }

    if (is_valid_shape && !dest_beyond_edge)
    {
        tests_passed = true;
    }

    return tests_passed;
}

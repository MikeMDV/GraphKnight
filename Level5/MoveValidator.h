#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 06/24/17
 *
 */

#include <vector>
#include <iostream>

#include "CommonDefs.h"

class MoveValidator
{
public:

    // Constructor
    MoveValidator(std::vector<std::vector<char> > board);

    // Destructor
    ~MoveValidator();

    /* Brief desc.           - A method to validate a set of moves and print 
     *                         the board for each move if requested
     * param[in] moves       - Vector of Vertex structs representing each move
     * param[in] print_moves - A flag to indicate whether board should be 
     *                         printed after each move
     *
     * param[out]            - Returns true if all moves are valid
     *
     */
    bool validateMoves(std::vector<Vertex> moves, bool print_moves);

    /* Brief desc.     - A method to return a set of legal moves from a position
     * param[in] start - Starting node
     *
     * param[out]      - Vector of Vertex structs representing the available 
     *                   legal moves
     *
     */
    std::vector<Vertex> getLegalMoves(Vertex start);

    /* Brief desc.        - A method to verify a position is on the board
     * param[in] position - Vertex representing the position needing checked
     *
     * param[out]         - Returns true if the position is on the board
     *
     */
    bool isOnBoard(Vertex position);

    /* Brief desc.        - A method to verify a position is a rock
     * param[in] position - Vertex representing the position needing checked
     *
     * param[out]         - Returns true if the position is a rock
     *
     */
    bool isRock(Vertex position);

    /* Brief desc.        - A method to verify a position is a barrier
     * param[in] position - Vertex representing the position needing checked
     *
     * param[out]         - Returns true if the position is a barrier
     *
     */
    bool isBarrier(Vertex position);

    // TODO: Write getTeleportNode() method to retrieve other T node when 1 is
    // given as a parameter
    /* Brief desc.        - A method to retrieve the other teleport node
     * param[in] position - Vertex representing the first teleport node
     *
     * param[out]         - Returns Vertex of the other connected teleport node
     *
     */
    Vertex getTeleportNode(Vertex position);

private:

    /* Brief desc.     - A method to print the board to stdout
     * param[in] board - A 2D Vector of chars to represent the board
     *
     */
    void printBoard(std::vector<std::vector<char> > board);

    /* Brief desc.           - A method to validate one move
     * param[in] origin      - Vertex representing the starting position
     * param[in] destination - Vertex representing the end position of the move
     *
     * param[out]            - Returns true if the move is valid
     *
     */
    bool checkMove(Vertex origin, Vertex destination);

    /* Brief desc.     - A method to check if a move is legal
     * param[in] start - Starting node
     * param[in] end   - Ending node
     *
     * param[out]      - True if the move was legal
     *
     */
    bool isLegalMove(Vertex start, Vertex end);

    /* Brief desc.     - A method to check if a move is blocked by a barrier
     * param[in] start - Starting node
     * param[in] end   - Ending node
     *
     * param[out]      - True if the move was blocked by a barrier
     *
     * Note            - This method will not check if the destination node is a
     *                   barrier
     *
     */
    bool moveIsBlocked(Vertex start, Vertex end);

    // Attributes
    std::vector<std::vector<char> > m_board;

    int m_board_row_size;

    Vertex *m_teleport_node_one;
    Vertex *m_teleport_node_two;

};

#endif // MOVE_VALIDATOR_H
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
    if (m_validator)
    {
        delete m_validator;
        m_validator = NULL;
    }
}

/* Algorithm - Call visitNext() to use DFS to retrieve a path to the end node
 *           - Assign the Vertex structs from the returned path to m_path in 
 *             reverse order
 * 
 */
void KnightGraph::dfsPathFind(const int &start_x, const int &start_y, 
    const int &end_x, const int &end_y)
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

/* Algorithm - Mark current node visited
 *           - Check if current node is the end node; If so, add the current 
 *             node to the path and return it (base case)
 *           - Check if 1 o'clock position is a legal move
 *           - If legal, check if the node has been visited
 *           - If not, recursively call visitNext() 
 *           - Check if the front node of the returned path is the end node
 *           - If so, add the cuurent node to the back of the path and return
 *           - Check the other possible moves
 *           - If no paths contained the end node, return an empty path (base
 *             case)
 * 
 */
std::vector<Vertex> KnightGraph::visitNext(const int &start_x, const int &start_y,
    const int &end_x, const int &end_y)
{
    // Create Vertex for current node and vector for path
    Vertex current_node(start_x, start_y);
    std::vector<Vertex> path;

    // Mark current node visited
    auto result = std::find_if(
        std::begin(m_nodes), std::end(m_nodes), match_num(current_node.number));
    if (result != std::end(m_nodes))
    {
        result->visited = true;
    }
    
    // Check if current node position equals end node and if so, push_back 
    // current Vertex and return
    if (start_x == end_x && start_y == end_y)
    {
        path.push_back(current_node);
        return path;
    }
    
    // Check if move to 1 o'clock position is legal
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

    // // Check if move to 2 o'clock position is legal
    // Vertex position_two(start_x + 2, start_y - 1);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_two.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }

    // // Check if move to 4 o'clock position is legal
    // Vertex position_three(start_x + 2, start_y + 1);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_three.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }

    // // Check if move to 5 o'clock position is legal
    // Vertex position_four(start_x + 1, start_y + 2);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_four.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }

    // // Check if move to 7 o'clock position is legal
    // Vertex position_five(start_x - 1, start_y + 2);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_five.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }

    // // Check if move to 8 o'clock position is legal
    // Vertex position_six(start_x - 2, start_y + 1);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_six.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }

    // // Check if move to 10 o'clock position is legal
    // Vertex position_seven(start_x - 2, start_y - 1);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_seven.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }

    // // Check if move to 11 o'clock position is legal
    // Vertex position_eight(start_x - 1, start_y - 2);
    // if (isLegalMove(current_node, position_two))
    // {
    //     // Check if node has been visited
    //     auto result = std::find_if(
    //         std::begin(m_nodes), std::end(m_nodes), 
    //         match_num(position_eight.number));
    //     if (!result->visited)
    //     {
    //         // Visit the node
    //         path = visitNext(result->x, result->y, end_x, end_y);
    //     }

    //     // Check if returned path has the end node at front 
    //     if ((path.size() >= 1) 
    //         && (path.front().x == end_x && path.front().y == end_y))
    //     {
    //         // Add current node to path and return
    //         path.push_back(current_node);
    //         return path;
    //     }
    // }
    
    // If control reaches this point, the end node was not in any of the 
    // returned paths; Return an empty path

    return path;
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


/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 06/04/17
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

#include "KnightGraph.h"


KnightGraph::KnightGraph(std::vector<std::vector<char> > board)
    : m_board(board),
    m_node_count(m_board.size() * m_board[0].size()),
    m_adj_matrix(m_node_count, std::vector<int>(m_node_count, 0))
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

/* Algorithm - Confirm that the start node is on the board
 *           - Call dfsVisitNext() to use a modified DFS to build the adjacency 
 *             matrix until a point is reached where a move to an unvisited node
 *             is not possible
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
        return;
    }

    // Get number of unvisited nodes remaining
    auto unvisited_nodes = std::count_if(m_nodes.begin(), m_nodes.end(), 
            match_visited(false));

    // Visit remaining unvisited nodes
    while (unvisited_nodes != 0)
    {
        // Find first unvisited node
        auto result = std::find_if(
        m_nodes.begin(), m_nodes.end(), match_visited(false));

        // Start DFS from the first unvisited node
        dfsVisitNext(result->x, result->y);

        // Get number of unvisited nodes remaining
        unvisited_nodes = std::count_if(m_nodes.begin(), m_nodes.end(), 
            match_visited(false));
    }

    // Reset visited status for all nodes
    for (unsigned int i = 0; i < m_nodes.size(); i++)
    {
        m_nodes[i].visited = false;
    }
}

/* Algorithm - Call dfsGraphBuild() to build the adjacency matrix
 *           - Confirm the start and end points are on the board
 *           - Use BFS to retrieve a shortest path to the end node
 *             - Enqueue the first node in a FIFO queue
 *             - While the node queue contains nodes, check the adjacency matrix
 *               for the neighbors of the front node; distance of the neighbors
 *               becomes distance of the current node + 1; the parent of the 
 *               neighbors is changed to the current vertex; Enqueue the current
 *               node
 * 
 */
void KnightGraph::bfsShortestPath(int start_x, int start_y, 
    int end_x, int end_y)
{
    // Build the adjacency matrix
    dfsGraphBuild(start_x, start_y);

    // Verify start and end Vertex structs are on board
    Vertex start(start_x, start_y);
    Vertex end(end_x, end_y);

    bool start_is_on_board = m_validator->onBoard(start);
    bool end_is_on_board   = m_validator->onBoard(end);

    if (!start_is_on_board || !end_is_on_board)
    {
        std::cout << "Start or end node is invalid.\n";
        return;
    }

    // Enqueue the start node
    std::queue<Vertex> node_queue(m_node_queue);
    node_queue.push(m_nodes[start.number]);

    // Conduct BFS search in loop 
    while (!node_queue.empty())
    {
        // Get a copy of the front node
        Vertex current = node_queue.front();

        // Check the adjacency matrix for connected nodes
        for (unsigned int i = 0; i < m_adj_matrix[current.number].size(); i++)
        {
            if (m_adj_matrix[current.number][i] == 1)
            {
                auto result = std::find_if(
                    m_nodes.begin(), m_nodes.end(), match_num(i));

                // Update node if it has not been visited
                if (result != m_nodes.end() && !result->visited)
                {
                    result->distance   = current.distance + 1;
                    result->parent_num = current.number;

                    // Enqueue the node
                    node_queue.push(m_nodes[i]);
                }
            }
        }

        // Mark current node visited
        auto result = std::find_if(
            m_nodes.begin(), m_nodes.end(), match_num(current.number));
        if (result != m_nodes.end())
        {
            result->visited = true;
        }

        // Dequeue current node
        node_queue.pop();
    }

    // Build path in reverse order
    int node_number = end.number;
    while (node_number != -1)
    {
        m_path.push_back(m_nodes[node_number]);

        // Set next node number to parent number of the current node
        if (node_number == start.number)
        {
            node_number = -1;
        }
        else
        {
            int next_node_number = m_nodes[node_number].parent_num;
            node_number = next_node_number;
        }
    }

    // Reverse order of path
    std::reverse(m_path.begin(), m_path.end());
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
        m_nodes.begin(), m_nodes.end(), match_num(current_node.number));
    if (result != m_nodes.end())
    {
        result->visited = true;
    }

    // Get available legal moves
    std::vector<Vertex> legal_moves = m_validator->getLegalMoves(current_node);

    // Add node connections to adjancency matrix
    for (unsigned int i = 0; i < legal_moves.size(); i++)
    {
        m_adj_matrix[current_node.number][legal_moves[i].number] = 1;
    }

    // Check for first unvisited legal move
    int position = -1;
    for (unsigned int i = 0; i < legal_moves.size(); i++)
    {
        auto result = std::find_if(m_nodes.begin(), m_nodes.end(), 
            match_num(legal_moves[i].number));
        if ((result != m_nodes.end()) && !result->visited)
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


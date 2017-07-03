/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 07/02/17
 *
 */

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <deque>
#include <queue>
#include <random>

#include "KnightGraph.h"

KnightGraph::KnightGraph(std::vector<std::vector<char> > board)
    : m_board(board),
    m_board_row_size(m_board[0].size()),
    m_node_count(m_board.size() * m_board[0].size()),
    m_adj_matrix(m_node_count, std::vector<int>(m_node_count, 0))
{
    // Construct vector of Vertex structs
    for (unsigned int i = 0; i < m_board.size(); i++)
    {
        for (unsigned int j = 0; j < m_board[0].size(); j++)
        {
            Vertex vert(j, i, m_board_row_size);
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
 *           - Call dfsVisitNext() to use a DFS to build the adjacency matrix 
 *           - Reset the visited status for all nodes in m_nodes
 * 
 */
void KnightGraph::dfsGraphBuild(int start_x, int start_y)
{
    // Verify start node is on board
    Vertex start(start_x, start_y, m_board_row_size);
    bool start_is_on_board = m_validator->isOnBoard(start);

    if (!start_is_on_board)
    {
        std::cout << "Start node is invalid.\n";
        return;
    }

    // Call visitNext() to use DFS to build adjacency matrix
    dfsVisitNext(start_x, start_y);

    // Reset visited status for all nodes
    for (unsigned int i = 0; i < m_nodes.size(); i++)
    {
        m_nodes[i].visited = false;
    }
}

/* Algorithm - Confirm the start and end points are on the board
 *           - Call dfsGraphBuild() to build the adjacency matrix
 *           - Use BFS to retrieve a shortest path to the end node
 *             - Enqueue the first node in a FIFO queue
 *             - While the node queue contains nodes, check the adjacency matrix
 *               for the neighbors of the front node; distance of the neighbors
 *               becomes distance of the current node + 1; the parent of the 
 *               neighbors is changed to the current vertex; Enqueue the current
 *               node
 *             - Once the FIFO queue is empty build the path in reverse order
 *               from the destination to the source
 * 
 */
void KnightGraph::bfsShortestPath(int start_x, int start_y, 
    int end_x, int end_y)
{
    // Verify start and end Vertex structs are on board    
    Vertex start(start_x, start_y, m_board_row_size);
    Vertex end(end_x, end_y, m_board_row_size);
    
    bool start_is_on_board = m_validator->isOnBoard(start);
    bool end_is_on_board   = m_validator->isOnBoard(end);
    if (!start_is_on_board || !end_is_on_board)
    {
        std::cout << "Start or end node is invalid.\n";
        return;
    }
    
    // Build the adjacency matrix
    dfsGraphBuild(start_x, start_y);

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

/* Algorithm - Call dfsGraphBuild() to build the adjacency matrix
 *           - Confirm the start and end points are on the board
 *           - Use Dijkstra's algo to retrieve a shortest path to the end node
 *             - Set the start Vertex distance to 0
 *             - Copy m_nodes to m_nodes_queue and set up a min heap
 *             - While the node queue contains nodes, extract the node with the
 *               min distance; mark the node visited; relax the edges of the 
 *               connected nodes by making their distance the current node's 
 *               distance + the value from the adj matrix, then changing the 
 *               parent to the current vertex, as long as the current node 
 *               distance + the adj matrix value is less than the node's 
 *               distance
 *             - Once the min-priority queue is empty build the path in reverse 
 *               order from the destination to the source
 *
 * Note      - The STL make_heap places the largest element at the top by 
 *             default, using comparison function that returns the smaller of 
 *             two types. A comparison returning the larger type will result in 
 *             a min heap.
 *           - m_node_queue will be the min-priority queue and m_nodes will be 
 *             the set of visited nodes
 *           - When building the path, if a teleport node is encountered, the 
 *             parent of the teleport node must be the other teleport node, so 
 *             it will need to be inserted in the path.
 * 
 */
void KnightGraph::daShortestPath(int start_x, int start_y, int end_x, int end_y)
{
    // Build the adjacency matrix
    dfsGraphBuild(start_x, start_y);

    // Verify start and end Vertex structs are on board and legal
    Vertex start(start_x, start_y, m_board_row_size);
    Vertex end(end_x, end_y, m_board_row_size);

    bool start_is_on_board = m_validator->isOnBoard(start);
    bool end_is_on_board   = m_validator->isOnBoard(end);
    bool start_is_rock     = m_validator->isRock(start);
    bool end_is_rock       = m_validator->isRock(end);
    bool start_is_barrier  = m_validator->isBarrier(start);
    bool end_is_barrier    = m_validator->isBarrier(end);

    if (!start_is_on_board || !end_is_on_board || start_is_rock || end_is_rock 
        || start_is_barrier || end_is_barrier)
    {
        std::cout << "Start or end node is invalid.\n";
        return;
    }

    // Set the distance for the start node to 0
    auto result = std::find_if(
        m_nodes.begin(), m_nodes.end(), match_num(start.number));
    if (result != m_nodes.end())
    {
        result->distance = 0;
    }
    
    // Copy all nodes in m_nodes to queue and create a min heap
    for (unsigned int i = 0; i < m_nodes.size(); i++)
    {
        m_node_queue.push_back(m_nodes[i]);
    }
    std::make_heap(m_node_queue.begin(), m_node_queue.end(), greater_dist());

    // Use Dijkstra's algorithm to find the shortest path
    while (!m_node_queue.empty())
    {
        // Get a copy of the front node
        Vertex current = m_node_queue.front();

        // Mark current node visited
        auto result = std::find_if(
            m_nodes.begin(), m_nodes.end(), match_num(current.number));
        if (result != m_nodes.end())
        {
            result->visited = true;
        }

        // Check the adjacency matrix for connected nodes and relax edges
        for (unsigned int i = 0; i < m_adj_matrix[current.number].size(); i++)
        {
            if (m_adj_matrix[current.number][i] > 0)
            {
                // Update node if the current node distance + adj matrix value
                // is less than the connected node's distance
                auto result = std::find_if(
                    m_node_queue.begin(), m_node_queue.end(), match_num(i));

                if (result != m_node_queue.end() 
                    && (current.distance + m_adj_matrix[current.number][i])
                        < result->distance)
                {
                    // Update distance in m_node_queue
                    result->distance = current.distance 
                        + m_adj_matrix[current.number][i];

                    // Update parent node in m_nodes
                    auto m_node_result = std::find_if(
                        m_nodes.begin(), m_nodes.end(), match_num(i));
                    if (m_node_result != m_nodes.end())
                    {
                        m_node_result->parent_num = current.number;
                    }
                }
            }
        }

        // Make heap again since changing distance values may have affected heap
        std::make_heap(m_node_queue.begin(), m_node_queue.end(), greater_dist());

        // Pop the current node off the top of the heap
        std::pop_heap(m_node_queue.begin(), m_node_queue.end(), greater_dist());
        m_node_queue.pop_back();
    }

    // Build path in reverse order
    buildPathInReverse(start, end);
}

/* Algorithm - Call dfsGraphBuild() to build the adjacency matrix
 *           - Confirm the start and end points are on the board
 *           - Call daShortestPath() and place the path in m_path_store
 *           - Loop through longest path algorithm searches times
 *             - While the end node has not been reached and there are unvisited
 *               nodes to explore
 *               - Build path using heuristic of choosing next node having least 
 *               degree
 *               - Tiebreak 1: Get sum of degrees of neighbor nodes of least
 *               degree neighbors and choose least
 *               - Tiebreak 2: If current node and the next node is on the 
 *               previous longest path, choose another node
 *               - Tiebreak 3: Choose a node at random
 *               - Set the next node parent_num as the current node
 *               - Set the current_node to next_node
 *             - Build path in reverse order from end node
 *             - Add path to m_path_store then clear m_path
 *             - Reset m_nodes values to defaults
 *             - Copy longest path from m_node_store to m_path
 * 
 */
void KnightGraph::apprLongestPath(int start_x, int start_y, int end_x, int end_y, 
        int searches)
{
    // Build the adjacency matrix
    dfsGraphBuild(start_x, start_y);

    // Verify start and end Vertex structs are on board and legal
    Vertex start(start_x, start_y, m_board_row_size);
    Vertex end(end_x, end_y, m_board_row_size);

    bool start_is_on_board = m_validator->isOnBoard(start);
    bool end_is_on_board   = m_validator->isOnBoard(end);
    bool start_is_rock     = m_validator->isRock(start);
    bool end_is_rock       = m_validator->isRock(end);
    bool start_is_barrier  = m_validator->isBarrier(start);
    bool end_is_barrier    = m_validator->isBarrier(end);

    if (!start_is_on_board || !end_is_on_board || start_is_rock || end_is_rock 
        || start_is_barrier || end_is_barrier)
    {
        std::cout << "Start or end node is invalid.\n";
        return;
    }

    // Call daShortestPath() and place the path in m_path_store
    daShortestPath(start_x, start_y, end_x, end_y);
    m_path_store.push_back(m_path);
    m_path.clear();

    // Reset visited, parent, and distance status for all nodes
    setM_nodeValsToDefaults();

    // Loop through longest path algorithm searches times
    for (unsigned int i = 0; i < searches; i++)
    {
        // Build path using heuristic of choosing next node having least degree
        Vertex current_node = start;
        bool are_unvisited_nodes = true;
        while (current_node.number != end.number && are_unvisited_nodes)
        {
            // Mark current node visited
            auto result = std::find_if(
                m_nodes.begin(), m_nodes.end(), match_num(current_node.number));
            if (result != m_nodes.end())
            {
                result->visited = true;
            }

            // Choose move to unvisited node with least degree
            std::vector<Vertex> next_move_set = 
                getLeastDegreeNeighbors(current_node);

            if (next_move_set.size() == 0)
            {
                // No unvisited nodes available for move from this position
                are_unvisited_nodes = false;
            }
            else
            {
                // Check if tiebreakers are needed
                // Tiebreak 1 - Get sum of degrees of neighbor nodes of least 
                //              degree neighbors and choose least
                if (next_move_set.size() > 1)
                {
                    std::vector<int> degree_sums;
                    int least_degree_sum = std::numeric_limits<int>::max();
                    for (unsigned int j = 0; j < next_move_set.size(); j++)
                    {
                        int sum = 
                            getSumOfDegreesOfNeighbors(next_move_set[j]);

                        degree_sums.push_back(sum);

                        // Set least degree sum if necessary
                        if (sum < least_degree_sum)
                        {
                            least_degree_sum = sum;
                        }
                    }

                    // Create a vector of neighbor nodes with neighbors with  
                    // least degree and copy to next move set
                    std::vector<Vertex> least_degree_sum_neighbors;
                    for (unsigned int j = 0; j < next_move_set.size(); j++)
                    {
                        if (degree_sums[j] == least_degree_sum)
                        {
                            least_degree_sum_neighbors.push_back(
                                next_move_set[j]);
                        }
                    }
                    next_move_set = least_degree_sum_neighbors;
                }

                // Tiebreak 2 if current node and the next node is on the 
                // previous longest path, choose another node
                std::vector<Vertex> longest_path = 
                    getLongestPathFromPathStore(end);
                result = std::find_if(longest_path.begin(), longest_path.end(), 
                    match_num(current_node.number));
                if (result != longest_path.end())
                {
                    // Advance result to next node and check if it matches any  
                    // in the move set
                    std::vector<Vertex> nodes_not_on_earlier_path;
                    ++result;
                    for (unsigned int j = 0; j < next_move_set.size(); j++)
                    {
                        if (result->number != next_move_set[j].number)
                        {
                            nodes_not_on_earlier_path.push_back(
                                next_move_set[j]);
                        }
                    }
                    
                    if (nodes_not_on_earlier_path.size() > 0)
                    {
                        next_move_set = nodes_not_on_earlier_path;
                    }
                }

                // Tiebreaker 3 choose a node at random
                if (next_move_set.size() > 1)
                {
                    std::vector<Vertex> random_node;
                    std::random_device rd;
                    std::mt19937 engine(rd());
                    std::uniform_int_distribution<unsigned int> 
                        dis(0, next_move_set.size() - 1);
                    unsigned int index = dis(engine);
                    random_node.push_back(next_move_set[index]);
                    next_move_set = random_node;
                }

                // Set the next node parent_num as the current node
                Vertex next_node = next_move_set[0];
                m_nodes[next_node.number].parent_num = current_node.number;

                // Set the current_node to next_node
                current_node = next_node;
            }
        }

        // Build path in reverse order from end node
        buildPathInReverse(start, current_node);

        // Add path to m_path_store then clear m_path
        m_path_store.push_back(m_path);
        m_path.clear();

        // Reset m_nodes values to defaults
        setM_nodeValsToDefaults();
    }

    // Copy longest path from m_node_store to m_path
    std::vector<Vertex> longest_path = getLongestPathFromPathStore(end);
    m_path = longest_path;
}

/* Algorithm - Mark current node visited and add to m_path
 *           - Get the legal moves available from the current node
 *           - Add node connections to adjancency matrix
 *           - Check for the first node of the returned list of moves that has 
 *             not been visited
 *           - If no unvisited legal moves exist, move back one node and check 
 *             for unvisited nodes
 *           - If beginning of path has been reached and no unvisited nodes 
 *             exist, return (base case)
 *           - Otherwise, set next_x and next_y to the next unvisited legal move
 *           - Visit next_x and next_y (recursive call)
 * 
 */
void KnightGraph::dfsVisitNext(int start_x, int start_y)
{
    // Create Vertex for current node
    Vertex current_node(start_x, start_y, m_board_row_size);

    // Mark current node visited and add to m_path
    auto result = std::find_if(
        m_nodes.begin(), m_nodes.end(), match_num(current_node.number));
    if (result != m_nodes.end())
    {
        result->visited = true;
        m_path.push_back(current_node);
    }

    // Get available legal moves
    std::vector<Vertex> legal_moves = m_validator->getLegalMoves(current_node);

    // Add node connections to adjancency matrix
    for (unsigned int i = 0; i < legal_moves.size(); i++)
    {
        // Get the node tyoe of the legal move node
        char node_type = m_board[legal_moves[i].y][legal_moves[i].x];

        // Determine what the edge weight will be for the adj matrix connection
        switch(node_type)
        {
            case 'W':
            {
                m_adj_matrix[current_node.number][legal_moves[i].number] 
                    = WATER_NODE_WEIGHT;
                break;
            }
            case 'L':
            {
                m_adj_matrix[current_node.number][legal_moves[i].number] 
                    = LAVA_NODE_WEIGHT;
                break;
            }
            case 'T': // Teleport node - connect to other teleport node
            {
                // Retrieve other T node number
                Vertex teleport_node = 
                    m_validator->getTeleportNode(legal_moves[i]);
                // Add connection to retrieved node in matrix rather than 
                // current T node from legal_moves
                m_adj_matrix[current_node.number][teleport_node.number] = 1;
                break;
            }
            default: // '.' character - normal node
            {
                m_adj_matrix[current_node.number][legal_moves[i].number] = 1;
            }
        }

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
        // No unvisited legal moves exist; Move back one node and check for move

        // Pop current node off path
        m_path.pop_back();

        if (!m_path.empty())
        {
            // Retrieves coordinates of previous node
            next_x = m_path.back().x;
            next_y = m_path.back().y;
        }
        else
        {
            // The path is empty after popping the current node off; The graph
            // has been fully explored

            return;
        }

        // Pop previous node off path so it is not added twice
        m_path.pop_back();
    }

    // Visit next node
    dfsVisitNext(next_x, next_y);
}

/* Algorithm - Retrieve the legal moves for the start position
 *           - Instantiate an unsigned int with the max value for least degree
 *           - Loop through the vector of legal moves, retrieve the legal moves 
 *             for each of thoses moves, storing value in degree vector
 *             - If the degree of the move being checked is less than the least 
 *               degree, set least degree to that value
 *           - Return a vector of Vertex with the unvisited least degree 
 *             legal moves
 * 
 */
std::vector<Vertex> KnightGraph::getLeastDegreeNeighbors(Vertex start)
{
    // Retrieve the legal moves for the start position
    std::vector<Vertex> legal_moves = m_validator->getLegalMoves(start);

    // Create a vector of unvisited legal move nodes
    std::vector<Vertex> uv_legal_moves;
    for (unsigned int i = 0; i < legal_moves.size(); i++)
    {
        if (!(m_nodes[legal_moves[i].number].visited))
        {
            uv_legal_moves.push_back(legal_moves[i]);
        }
    }

    // Retrieve the number of legal moves for each of the legal moves
    unsigned int least_degree = std::numeric_limits<int>::max();
    std::vector<unsigned int> uv_legal_moves_degrees;
    for (unsigned int i = 0; i < uv_legal_moves.size(); i++)
    {
        std::vector<Vertex> conn_uv_legal_moves = 
            m_validator->getLegalMoves(uv_legal_moves[i]);

        // Create a vector of unvisited connections to unvisited legal moves
        std::vector<Vertex> uv_conn_uv_legal_moves;
        for (unsigned int j = 0; j < conn_uv_legal_moves.size(); j++)
        {
            if (!m_nodes[conn_uv_legal_moves[j].number].visited)
            {
                uv_conn_uv_legal_moves.push_back(conn_uv_legal_moves[j]);
            }
        }

        // Store the degree of the node in the vector of degrees
        unsigned int degree = uv_conn_uv_legal_moves.size();
        uv_legal_moves_degrees.push_back(degree);

        // Set least degree if necessary
        if (degree < least_degree)
        {
            least_degree = degree;
        }
    }

    // Retrieve unvisited nodes with the least degree and return them
    std::vector<Vertex> least_degree_neighbors;
    for (unsigned int i = 0; i < uv_legal_moves.size(); i++)
    {
        if (uv_legal_moves_degrees[i] == least_degree)
        {
            least_degree_neighbors.push_back(uv_legal_moves[i]);
        }
    }

    return least_degree_neighbors;
}

/* Algorithm - Retrieve the unvisited legal moves for the start position
 *           - Instantiate an unsigned int for the sum of degrees
 *           - Loop through the vector of legal moves, retrieve the legal moves 
 *             for each of thoses moves, storing value in degree vector
 *           - Return a sum of the vector degrees
 * 
 */
int KnightGraph::getSumOfDegreesOfNeighbors(Vertex start)
{
    // Retrieve the legal moves for the start position
    std::vector<Vertex> legal_moves = m_validator->getLegalMoves(start);

    // Create a vector of unvisited legal move nodes
    std::vector<Vertex> uv_legal_moves;
    for (unsigned int i = 0; i < legal_moves.size(); i++)
    {
        if (!m_nodes[legal_moves[i].number].visited)
        {
            uv_legal_moves.push_back(legal_moves[i]);
        }
    }

    // Retrieve the number of legal moves for each of the legal moves
    std::vector<unsigned int> uv_legal_moves_degrees;
    for (unsigned int i = 0; i < uv_legal_moves.size(); i++)
    {
        std::vector<Vertex> conn_uv_legal_moves = 
            m_validator->getLegalMoves(uv_legal_moves[i]);

        // Create a vector of unvisited connections to unvisited legal moves
        std::vector<Vertex> uv_conn_uv_legal_moves;
        for (unsigned int j = 0; j < conn_uv_legal_moves.size(); j++)
        {
            if (!m_nodes[conn_uv_legal_moves[j].number].visited)
            {
                uv_conn_uv_legal_moves.push_back(conn_uv_legal_moves[j]);
            }
        }

        // Store the degree of the node in the vector of degrees
        unsigned int degree = uv_conn_uv_legal_moves.size();
        uv_legal_moves_degrees.push_back(degree);
    }

    // Sum vector of degrees and return it
    int sum = static_cast<int>(std::accumulate(uv_legal_moves_degrees.begin(),
        uv_legal_moves_degrees.end(), 0));

    return sum;
}

/* Algorithm - Set values for visited, distance, and parent node to defaults
 * 
 */
void KnightGraph::setM_nodeValsToDefaults()
{
    for (unsigned int i = 0; i < m_nodes.size(); i++)
    {
        m_nodes[i].visited    = false;
        m_nodes[i].distance   = std::numeric_limits<int>::max();
        m_nodes[i].parent_num = -1;
    }
}

/* Algorithm - Find the size of the longest path in m_path_store with end as the
 *             last node
 *           - Return the last path equal to the longest path
 * 
 */
std::vector<Vertex> KnightGraph::getLongestPathFromPathStore(Vertex end)
{
    // Find the size of the longest path in m_path_store
    unsigned int longest_path_size  = 0;
    unsigned int longest_path_index = 0;
    for (unsigned int i = 0; i < m_path_store.size(); i++)
    {
        if (m_path_store[i].size() > longest_path_size 
            && m_path_store[i].back().number == end.number)
        {
            longest_path_size  = m_path_store[i].size();
            longest_path_index = i;
        }
    }

    // Return the path with the largest index equal to the longest path size
    std::vector<Vertex> longest_path = m_path_store[longest_path_index];

    return longest_path;
}

/* Algorithm - Build the path in reverse from the end node and store in m_path
 * 
 */
void KnightGraph::buildPathInReverse(Vertex start, Vertex end)
{
    // Build path in reverse order from end node
    int node_number = end.number;
    while (node_number != -1)
    {
        m_path.push_back(m_nodes[node_number]);

        // Set next node number to parent number of the current node
        if (node_number == start.number)
        {
            node_number = -1;
        }
        else if (m_board[m_nodes[node_number].y][m_nodes[node_number].x] == 'T')
        {
            // Other teleport node must be inserted in path
            Vertex other_teleport_node = 
                m_validator->getTeleportNode(m_nodes[node_number]);
            int node_after_teleport_number = m_nodes[node_number].parent_num;
            m_path.push_back(m_nodes[other_teleport_node.number]);
            node_number = node_after_teleport_number;
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

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}

/* Algorithm - Calculate the number of total moves possible if a path traversed
 *             every possible node
 *             - '.' = 1; 'W' = 2; 'L' = 5; Both 'T' = 1; 'R' & 'B' = 0
 *           - Create an int vector with a value for each move
 *           - Sum the vector
 *           - Print the total possible path length and the percentage of the 
 *             total length for m_path
 * 
 */
void KnightGraph::printCalculatedPathLengthAndPercent()
{
    std::vector<int> move_lengths;
    bool teleport_was_on_board = false;
    for (unsigned int i = 0; i < m_board.size(); i++)
    {
        for (unsigned int j = 0; j < m_board_row_size; j++)
        {
            char node_type = m_board[i][j];

            // Determine what the move value will be
            switch(node_type)
            {
                case '.':
                {
                    move_lengths.push_back(1);
                    break;
                }
                case 'W':
                {
                    move_lengths.push_back(WATER_NODE_WEIGHT);
                    break;
                }
                case 'L':
                {
                    move_lengths.push_back(LAVA_NODE_WEIGHT);
                    break;
                }
                case 'T':
                {
                    teleport_was_on_board = true;
                    break;
                }
                default: // 'B', 'R'
                {
                    // Do nothing
                }
            }
        }
    }

    // Add 1 for the teleport nodes
    if (teleport_was_on_board)
    {
        move_lengths.push_back(1);
    }

    // Sum the moves
    int total_possible_moves = std::accumulate(move_lengths.begin(), 
        move_lengths.end(), 0);
    std::cout << "Total possible moves on board = " << total_possible_moves 
        << "\n";

    // Calculate the length of m_path
    std::vector<int> path_lengths;
    bool teleport_was_in_path = false;
    for (unsigned int i = 0; i < m_path.size(); i++)
    {
        // Get the node tyoe of the legal move node
        char node_type = m_board[m_path[i].y][m_path[i].x];

        // Determine what the edge weight will be for the adj matrix connection
        switch(node_type)
        {
            case '.':
            {
                path_lengths.push_back(1);
                break;
            }
            case 'W':
            {
                path_lengths.push_back(WATER_NODE_WEIGHT);
                break;
            }
            case 'L':
            {
                path_lengths.push_back(LAVA_NODE_WEIGHT);
                break;
            }
            default: // 'T'
            {
                teleport_was_in_path = false;
            }
        }
    }

    if (teleport_was_in_path)
    {
        // Add 1 for teleport nodes
        path_lengths.push_back(1);
    }

    // Sum the moves
    int total_path_length = std::accumulate(path_lengths.begin(), 
        path_lengths.end(), 0);
    std::cout << "Total path length = " << total_path_length 
        << "\n";

    // Calculate the percentage
    double percentage = static_cast<double>(total_path_length)
        / static_cast<double>(total_possible_moves);

    std::cout << "Total path length is " << percentage << " percent of max " 
        << "possible path length\n";
}

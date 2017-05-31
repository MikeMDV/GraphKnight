/*              Author: Michael Marven
 *        Date Created: 05/30/17
 *  Date Last Modified: 05/30/17
 *
 */

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
}

KnightGraph::~KnightGraph()
{
    // Not implemented yet
}

/* Algorithm - 
 * 
 */
void KnightGraph::dfsGraphBuild(int start_x, int start_y, int end_x, int end_y)
{
    // Not implemented yet
}

/* Algorithm - Return m_adj_matrix
 * 
 */
std::vector<std::vector<bool> > KnightGraph::getAdjMatrix()
{
    return m_adj_matrix;
}

/* Algorithm - Return m_path
 * 
 */
std::vector<Vertex> KnightGraph::getPathToEnd()
{
    return m_path;
}


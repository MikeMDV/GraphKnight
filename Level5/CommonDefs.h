#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 07/02/17
 *
 */

#include <limits>

const int WATER_NODE_WEIGHT = 2;
const int LAVA_NODE_WEIGHT  = 5;


/* Brief desc.          - A struct to hold information for nodes in the Knight  
 *                        Board graphs
 * param[in] x          - X coordinate of the vertex
 * param[in] y          - Y coordinate of the vertex
 * param[in] row_size   - Row size of board for number calculation
 * param     distance   - Distance of the vertex from the source vertex 
 * param     number     - Number of the vertex
 * param     parent_num - Number of the parent/predecessor vertex
 * param     visited    - True if vertex was previously visited
 *
 */
struct Vertex
{
    int  x; // X coordinate
    int  y; // Y coordinate
    int  distance; // Distance
    int  number; // Vertex number
    int  parent_num; // Parent vertex number
    bool visited; // Indicates whether vertex was previously visited 

    // Constructor
    Vertex(int x_in, int y_in, int row_size) 
    : x(x_in), 
      y(y_in), 
      distance(std::numeric_limits<int>::max()),
      parent_num(-1),
      visited(false)
    {
        // Calculate vertex number from x and y coordinates
        number = (y_in * row_size) + x_in;
    }
};


/* Brief desc. - A struct for a comparison function for Vertex structs based on
 *               distance 
 * Details     - For use with STL algorithms; Will return true when Vertex 1 has
 *               a greater distance than Vertex 2; If the distances are equal,
 *               it returns true if Vertex 1 number is greater than Vertex 2
 *
 */
struct greater_dist 
{
    inline bool operator() (const Vertex& struct_1, const Vertex& struct_2)
    {
        return (struct_1.distance > struct_2.distance) 
                || (struct_1.distance == struct_2.distance
                    && struct_1.number > struct_2.number);
    }
};

/* Brief desc. - A function object for matching Vertex structs based on struct
 *               number
 * Details     - For use with STL algorithms requiring a unary predicate; Will
 *               return true if struct number equals number passed as param
 *
 */
struct match_num : std::unary_function<Vertex, bool>
{
    int num;
    match_num(int num):num(num){}
    inline bool operator() (const Vertex& v)
    {
        return (v.number == num);
    }
};

/* Brief desc. - A function object for matching Vertex structs based on visited
 *               status
 * Details     - For use with STL algorithms requiring a unary predicate; Will
 *               return true if visited equals boolean value passed as param
 *
 */
struct match_visited : std::unary_function<Vertex, bool>
{
    bool is_vis;
    match_visited(bool is_vis):is_vis(is_vis){}
    inline bool operator() (const Vertex& v)
    {
        return (v.visited == is_vis);
    }
};

#endif // COMMON_DEFS_H

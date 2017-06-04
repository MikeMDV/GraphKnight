#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 06/03/17
 *
 */


/* Brief desc.          - A struct to hold information for nodes in the Knight  
 *                        Board graphs
 * param[in] x          - X coordinate of the vertex
 * param[in] y          - Y coordinate of the vertex
 * param[in] distance   - Distance of the vertex from the source vertex 
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
    Vertex(int x_in, int y_in) 
    : x(x_in), 
      y(y_in), 
      distance(std::numeric_limits<int>::max()),
      visited(false)
    {
        // Calculate vertex number from x and y coordinates
        number = (y_in * 8) + x_in;
    }
};


/* Brief desc. - A struct for a comparison function for Vertex structs based on
 *               distance 
 * Details     - For use with STL algorithms; Will return true or false when
 *               comparing the distance of 2 Vertex structs
 *
 */
struct GreaterDist 
{
    inline bool operator() (const Vertex& struct_1, const Vertex& struct_2)
    {
        return (struct_1.distance > struct_2.distance);
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

#endif // COMMON_DEFS_H

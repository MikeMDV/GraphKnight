#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/*              Author: Michael Marven
 *        Date Created: 05/26/17
 *  Date Last Modified: 5/26/17
 *
 */


/* Brief desc.        - A struct to hold information for nodes in the Knight  
 *                      Board graphs
 * param[in] x        - X coordinate of the vertex
 * param[in] y        - Y coordinate of the vertex
 * param[in] distance - Distance of the vertex from the source vertex 
 * param     parent_x - X coordiante of the parent/predecessor vertex
 * param     parent_y - Y coordiante of the parent/predecessor vertex
 *
 */
struct Vertex
{
    int x; // X coordinate
    int y; // Y coordinate
    int distance; // Distance
    int parent_x; // Parent x coordinate
    int parent_y; // Parent y coordinate

    // Constructor
    Vertex(int x_in, int y_in, int d_in) : x(x_in), y(y_in), distance(d_in) {}
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

#endif // COMMON_DEFS_H
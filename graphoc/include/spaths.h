/**
 *  This program is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see https://www.gnu.org/licenses/.
 *  
 *  \brief  Declaration of shortest path functions
 *  \author Marco M. Mosca, email: marcomichele.mosca@gmail.com
 *
*/

#ifndef __SPATHS_H
#define __SPATHS_H
#include <stdio.h>
#include "graph.h"
/** Infinity -- Infinite value for Dijkstra algorithm*/
#define INFINITY (-1.0)
#define UNDEF ((unsigned int) -1)

/** Find the shortest paths in a graph with Dijkstra
    \param g Weighted graph
    \param source Starting node
    \param predecessors Pointer to the predecessor array. It is updated 
        during the traversal.

    \retval d -- Pointer to distance vector
    \retval NULL -- if errot (sets errno)
*/
double* dijkstra (graph_t* g, unsigned int source, unsigned int** predecessors);

/** Create the string with the predecessors generated by dijkstra function from n1 to n2
    \param g Graph
    \param n1 Source node
    \param n2 Destination node
    \param predecessors Pointer to the predecessor array.

    \retval s -- String with the path from n1 to n2. Each label separated by $: CAMBRIDGE$LONDON$...
    \retval NULL -- if the path does not exist sets errno == 0 and
    if error sets errno != 0
 */
char * spath_to_string(graph_t * g, unsigned int n1, unsigned int n2,  unsigned int * predecessors);

#endif //__SPATHS_H_END

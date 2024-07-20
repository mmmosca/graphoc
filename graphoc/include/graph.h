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
 *  \brief  Declaration of Graph functions and definition of Graph structures
 *  \author Marco M. Mosca, email: marcomichele.mosca@gmail.com
 *
*/

#ifndef __GRAPH_H
#define __GRAPH_H
#include <stdio.h>

/** Enum of TRUE and FALSE values */
typedef enum bool {
    TRUE=1,
    FALSE=0
} bool_t;


/**
 * Adjacency list of edges
 * - label -- Edge label
 * - weight -- Edge weight
 * - next -- Pointer to next edge
 */
typedef struct edge {
  unsigned int label;     
  double weight;
  struct edge * next;    
} edge_t;

/** Max length of a node label */
#define MAXLABEL 128

/**
 * Graph node
 * - char -- Pointer to edge label
 * - edge_t -- Pointer to adjacency list 
 */
typedef struct node {
    char* label;      
    edge_t * adj;          
} node_t;

/**
 * Graph node
 * - node_t -- Pointer to edge label
 * - size -- Node count
 */
typedef struct graph {
  node_t * node;  
  unsigned int size;      
} graph_t;


char* new_buff();

void copyword(char** s1, char * s2, int d);


/** Add an edge to the graph. Each edge should be unique.
    \param g Pointer to the Graph
    \param e edge: formatted string
       SORCE:DESTINATION:WEIGHT                                                                           
       e.g: CAMBRIDGE:LONDON:30.0 

    \retval 0 -- Insertion succeeded
    \retval -1 -- if error (sets errno)
            errno == ENOMEM failure during allocation
	        errno == EINVAL Invalid edge (e.g. not existing) */
int add_edge (graph_t * g, char* e);

/** Check if a node exists
    \param g Pointer to the graph
    \param label Node label


    \retval i -- Index of the node if exists
    \retval -1 -- otherwise
*/
int is_node(graph_t* g, char* label);

/** Check if an edge exists
    \param g Pointer to the graph
    \param n1 Label of source node
    \param n2 Label of destination node

    \retval TRUE -- if exists
    \retval FALSE -- otherwise
*/
bool_t is_edge(graph_t* g, unsigned int n1, unsigned int n2);

/** Get the node's get_degree
    \param g Pointer to the graph
    \param label Node label

    \retval n -- The number of edges in the node 
    \retval -1 -- if error (sets errno)*/
int get_degree(graph_t * g, char* label);  

/** Get the total number of nodes in a graph
    \param g Pointer to the graph

    \retval n -- Number of nodes 
    \retval -1 -- if error (sets errno)
*/
int get_node_count(graph_t* g); 


/** Get the number of edges in a graph
    \param g Pointer to the graph

    \retval n -- Number of edges
    \retval -1 -- if error (sets errno)
*/
int get_edge_count(graph_t* g);

char* get_input();

/** Load a graph from two files with Labels and Edges respectively:
    File 1: Labels separated by newline
    File 2 :Edges seaparated by newline with the following format: SOURCE:DESTINATION:WEIGHT 
    
    \param nodefile File with labels
    \param edgefile File with edges

    \retval g -- Pointer to the new graph
    \retval NULL -- if error (sets errno), es
            errno == ENOMEM Failure during allocation
	        errno == EINVAL Invalid parameters*/
graph_t* load_graph (FILE * nodefile, FILE * edgefile);

/** Check the label string
    \param label Label string
*/
int check_str(char* label);

/** Check the edge format
 * \param sedge Edge string
*/
int check_weight(char* sedge);

/** Save the graph to two files.
    File 1: Labels separated by newline
    File 2: Edges seaparated by newline with the following format: SOURCE:DESTINATION:WEIGHT
    
    \param nodefile File with labels
    \param edgefile File with edges

    \param g Graph to save

    \retval 0 -- Save completed
    \retval -1 -- if error (sets errno), es. errno == EIO failure during writing to file
*/
int save_graph (FILE * nodefile, FILE * edgefile, graph_t* g);

/** Create a graph 
    \param n Number of Nodes
    \param labels Pointer to array of labels:
    static const char* labels[] = {
        "CAMBRIDGE",
        "LONDON",
        "MACHESTER",
        "LIVERPOOL",
        NULL,
       };

    \retval p -- Pointer to the new graph
    \retval NULL -- if error (errno set)
    (errno == EINVAL invalid parameters)
    (errno == ENOMEM failure during memory allocation)
*/
graph_t * create_graph (unsigned int n, char **labels);

/** Destroy a graph and free all allocated memory
    \param g Address of pointer to the graph. Set to NULL at the end. 
*/
void free_graph (graph_t** g);

/** Print a graph to STDOUT
    \param g Pointer to the graph
*/
void print_graph (graph_t* g);

/** Create a copy of a graph
    \param g Pointer to the graph

    \retval p -- Pointer to the new copied graph
    \retval NULL -- if error (set errno)
    errno == ENOMEM Failure during allocation
    errno == EINVAL Invalid parameters */
graph_t* copy_graph (graph_t* g);

#endif //__GRAPH_C_END

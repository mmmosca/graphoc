/*
This program is free software: you can redistribute it and/or 
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see https://www.gnu.org/licenses/.
 
Author Marco M. Mosca, email: marcomichele.mosca@gmail.com
*/
#include "graph.h"
#include "string.h"
#include "assert.h"
#include "tests.h"

void test_get_edge_count()
{
    graph_t* graph;
    if ( ( graph = create_graph(5, labels) ) == NULL )  {
		exit(EXIT_FAILURE);
    }
    for(char** e=edges; *e!=NULL; e++){
		if (  add_edge(graph,*e) == -1 ) {
			fprintf(stderr, "Adding edge failed: %s", *e);
			perror("");
			exit(EXIT_FAILURE);
		}
    }
	assert(get_edge_count(graph) == 6);
    free_graph(&graph);
}

int main()
{
  test_get_edge_count();
  return 0;
}

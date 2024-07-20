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

void test_save_graph()
{
    graph_t* graph;
    FILE* nodefile, *edgefile;
    if ( ( graph = create_graph(5, labels) ) == NULL )  {
      exit(EXIT_FAILURE);
    }
    for(char** e=edges; *e!=NULL; e++){
		if (  add_edge(graph,*e) == -1 ) {
			exit(EXIT_FAILURE);
		}
    }
	if ( (nodefile = fopen("./labels.txt","w") ) == NULL ) {
		perror("fopen");
		exit(EXIT_FAILURE);
    }
    if ( (edgefile = fopen("./edges.txt","w") ) == NULL ) {
		perror("fopen");
		exit(EXIT_FAILURE);
    }
	assert(save_graph(nodefile, edgefile, graph) == 0);
    free_graph(&graph);
	fclose(nodefile);
    fclose(edgefile);
}

int main()
{
	test_save_graph();
	return 0;
}

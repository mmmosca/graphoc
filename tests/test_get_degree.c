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

void test_get_degree()
{
    graph_t* graph;
    if ( ( graph = create_graph(5, labels) ) == NULL )  {
      exit(EXIT_FAILURE);
    }
	for(char** p=edges; *p!=NULL; p++){
		if (  add_edge(graph,*p) == -1 ) {
			exit(EXIT_FAILURE);
		}
    }
    for(char** p=labels,i=0; *p!=NULL; p++,i++){
		assert(get_degree(graph,*p) == degrees[i]);
    }
    free_graph(&graph);
	
	assert( get_degree(NULL,NULL) == -1 );
}

int main()
{
  test_get_degree();
  return 0;
}

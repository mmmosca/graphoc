#include "graph.h"
#include "string.h"
#include "assert.h"
#include "tests.h"

void test_copy_graph()
{
	graph_t *graph, *cpy_graph;
	unsigned int edge_count, exp_node_count = 5, exp_edge_count = 6;
	if ( ( graph = create_graph(5, labels) ) == NULL )  {
		perror("test_copy_graph - create graph nodes");
		exit(EXIT_FAILURE);
	}
	for(char** e=edges; *e!=NULL; e++){
		if ( add_edge(graph,*e) == -1 ) {
			perror("test_copy_graph - add edges");
			exit(EXIT_FAILURE);
		}
	}

	if ( ( cpy_graph = copy_graph(graph) ) == NULL )  {
		perror("test_copy_graph - copy graph");
		exit(EXIT_FAILURE);
	}
	if ( ( edge_count = get_edge_count(cpy_graph) ) == -1 )  {
		perror("test_copy_graph - edge count");
		exit(EXIT_FAILURE);
	}
	assert(cpy_graph->size == exp_node_count);
	assert(edge_count == exp_edge_count);
	free_graph(&graph);
	free_graph(&cpy_graph);
	assert(graph == NULL);
	assert(cpy_graph == NULL);
}

int main()
{
  test_copy_graph();
  return 0;
}

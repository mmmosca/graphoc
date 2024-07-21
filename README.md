# graphoc
C API for Unix and Windows to create `graphs` and compute the shortest paths with `Dijkstra` 

## Prerequisites
### Windows
1. Install Visual Studio (e.g. Community) choosing the following `single components`:
    - `MSVC v142+ - C++ Build tools`
    - `C++/CLI for Build Tools v142+`
    - `Windows 11 SDK`
    - `CMake C++ Tools for Windows`

2. Add the following environmental variable as User:
    - `VS_DIR`: Path to Visual Studio with all folders (e.g. `Microsoft Visual Studio\2022\Community`)

3. Start a `Command Prompt` (no PowerShell) and type the following to setup the env:
    ```
    "%VS_DIR%\VC\Auxiliary\Build\vcvarsall.bat" x64
	```

### Unix
No prerequisites

## Installation
1. Download the repository

2. Run the following in a terminal (or Command Prompt) to install the library:
    ```
    cd graphoc
    cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=<install_folder>
    cmake --build build --target install --config Release
    ```
    Note: Generate shared libraries (`.so` or `.lib` + `.dll`) instead as follows:
    ```
    cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=<install_folder> -DSHARED=ON
    ```
3. When using the library in your project make sure to:
    - Include `<install_folder>/include`
    - Link the library `<install_folder>/lib/graphoc.a` or `<install_folder>/lib/graphoc.lib`

## Load `graphoc` as dependency in your cmake file
In your `CMakeLists.txt` file
```
...
find_package(graphoc PATHS "<install_folder>" REQUIRED)
include_directories(${graphoc_INCLUDE_DIR})
add_executable(${PROJECT_NAME} yourmain.cpp)
target_link_libraries(${PROJECT_NAME} "${graphoc_LIBRARIES}")
install(FILES ${graphoc_RUNTIME} DESTINATION bin)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
...
```

## Usage example
```
#include "graph.h"
#include "spaths.h"
...
int main(int argc, char* argv[]) {
	graph_t* graph;
	double *dist = NULL;
	unsigned int * predecessors=NULL;
	char * labels[] = {
		"node1",
		"node2",
		"node3",
		...,
		NULL,
	}
	char* edges[] = {
		"node1:node2:20.0",
		"node2:node3:40.0",
		...,
		NULL,
	};

	if ( ( graph = create_graph(<number_of_nodes>, labels) ) == NULL )  {
		exit(EXIT_FAILURE);
	}
	for(char** e=edges; *e!=NULL; e++){
		if (  add_edge(graph,*e) == -1 ) {
			perror("Adding edge error");
			exit(EXIT_FAILURE);
		}
	}
	if ( ( dist = dijkstra(graph, 0, &predecessors) ) == NULL ) {
		perror("Dijkstra error");
		exit(EXIT_FAILURE);
	}
	/* Use vector of distances 'dist' and 'predecessors' from 'node1' */
	free_graph(&graph);
	...
}
```

## Tests (only on static build)
```
cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=<install_folder>
cmake --build .\build --target install --config Release
cd build
ctest --build-config Release --build-target install
```

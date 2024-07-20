# graphoc
C API for Unix to create `graphs` and compute the shortest paths with `Dijkstra` 

## Installation (Unix)
1. Download the repository

2. Run the following in a terminal to install it:
    ```
    cd graphoc
    cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=<install_folder>
    cmake --build build --target install --config Release
    ```
    Note: Generate shared libraries (`.so`) instead as follows:
    ```
    cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=<install_folder> -DSHARED=ON
    ```
3. When using the library in your project make sure to:
    - Include `<install_folder>/include`
    - Link the library `<install_folder>/lib/graphoc.a`


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
int main(int argc, char* argv[]) {
    
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

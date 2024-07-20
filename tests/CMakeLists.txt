#[[
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
]]

project(graphoc_test LANGUAGES C)

add_executable (test_create_graph ${CMAKE_CURRENT_SOURCE_DIR}/test_create_graph.c)
add_executable (test_get_node_count ${CMAKE_CURRENT_SOURCE_DIR}/test_get_node_count.c)
add_executable (test_get_edge_count ${CMAKE_CURRENT_SOURCE_DIR}/test_get_edge_count.c)
add_executable (test_add_edge ${CMAKE_CURRENT_SOURCE_DIR}/test_add_edge.c)
add_executable (test_get_degree ${CMAKE_CURRENT_SOURCE_DIR}/test_get_degree.c)
add_executable (test_check_node_edge ${CMAKE_CURRENT_SOURCE_DIR}/test_check_node_edge.c)
add_executable (test_save_graph ${CMAKE_CURRENT_SOURCE_DIR}/test_save_graph.c)
add_executable (test_dijkstra ${CMAKE_CURRENT_SOURCE_DIR}/test_dijkstra.c)
target_link_libraries (test_create_graph PRIVATE graphoc)
target_link_libraries (test_get_node_count PRIVATE graphoc)
target_link_libraries (test_get_edge_count PRIVATE graphoc)
target_link_libraries (test_add_edge PRIVATE graphoc)
target_link_libraries (test_get_degree PRIVATE graphoc)
target_link_libraries (test_check_node_edge PRIVATE graphoc)
target_link_libraries (test_save_graph PRIVATE graphoc)
target_link_libraries (test_dijkstra PRIVATE graphoc)
add_test (NAME test_create_graph COMMAND test_create_graph)
add_test (NAME test_get_node_count COMMAND test_get_node_count)
add_test (NAME test_get_edge_count COMMAND test_get_edge_count)
add_test (NAME test_add_edge COMMAND test_add_edge)
add_test (NAME test_get_degree COMMAND test_get_degree)
add_test (NAME test_check_node_edge COMMAND test_check_node_edge)
add_test (NAME test_save_graph COMMAND test_save_graph)
add_test (NAME test_dijkstra COMMAND test_dijkstra)

add_executable (test_create_graph_nolabels ${CMAKE_CURRENT_SOURCE_DIR}/test_create_graph_nolabels.c)
add_executable (test_create_graph_zerosize ${CMAKE_CURRENT_SOURCE_DIR}/test_create_graph_zerosize.c)
add_executable (test_get_node_count_ofnull ${CMAKE_CURRENT_SOURCE_DIR}/test_get_node_count_ofnull.c)
target_link_libraries (test_create_graph_nolabels PRIVATE graphoc)
target_link_libraries (test_create_graph_zerosize PRIVATE graphoc)
target_link_libraries (test_get_node_count_ofnull PRIVATE graphoc)
add_test (NAME test_create_graph_nolabels COMMAND test_create_graph_nolabels)
add_test (NAME test_create_graph_zerosize COMMAND test_create_graph_zerosize)
add_test (NAME test_get_node_count_ofnull COMMAND test_get_node_count_ofnull)

set_tests_properties(
    test_create_graph_zerosize
    test_create_graph_nolabels
    test_get_node_count_ofnull
    PROPERTIES WILL_FAIL TRUE
)

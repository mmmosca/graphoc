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
include(CMakePackageConfigHelpers)

set ( INSTALL_LIB lib )
set ( INSTALL_BIN bin )
set(INSTALL_INCLUDE_DIR include)
set(INSTALL_CONFIG_FILE cmake)
IF(WIN32)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set ( INSTALL_LIBRARIES ${INSTALL_LIB}/${PROJECT_NAME}.lib )
    IF(SHARED)
        set ( INSTALL_RUNTIME ${INSTALL_BIN}/${PROJECT_NAME}.dll )
        set( EXPORT_OBJECTS INSTALL_INCLUDE_DIR INSTALL_LIBRARIES INSTALL_RUNTIME )
    ELSE()
        set( EXPORT_OBJECTS INSTALL_INCLUDE_DIR INSTALL_LIBRARIES )
    ENDIF()
ELSE()
    IF(SHARED)
        set ( INSTALL_LIBRARIES ${INSTALL_LIB}/lib${PROJECT_NAME}.so )
    ELSE()
        set ( INSTALL_LIBRARIES ${INSTALL_LIB}/lib${PROJECT_NAME}.a )
    ENDIF()
    set( EXPORT_OBJECTS INSTALL_INCLUDE_DIR INSTALL_LIBRARIES )
ENDIF()

set( INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" )
set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" )

set( HEADER_FILES ${INCLUDE_DIR}/graph.h ${INCLUDE_DIR}/spaths.h)
set( SRC_FILES ${SRC_DIR}/graph.c ${SRC_DIR}/spaths.c)

if (SHARED)
    set (CMAKE_IN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/graphocConfigShared.cmake.in)
    add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
ELSE()
    set (CMAKE_IN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/graphocConfig.cmake.in)
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
ENDIF()

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

configure_package_config_file(
    ${CMAKE_IN_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/graphocConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIG_FILE}
    PATH_VARS ${EXPORT_OBJECTS}
)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${INSTALL_BIN})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${INSTALL_LIB})
install(FILES
    ${HEADER_FILES}
    DESTINATION ${INSTALL_INCLUDE_DIR}
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/graphocConfig.cmake
    DESTINATION ${INSTALL_CONFIG_FILE}
)

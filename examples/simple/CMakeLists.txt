# This file builds example

cmake_minimum_required (VERSION 2.6)
project (simple)

set(SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	)
set(HEADERS
	${CMAKE_CURRENT_LIST_DIR}/../../include/plain_fsm.h
	)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../include)
	
add_executable(test ${SOURCES} ${HEADERS})


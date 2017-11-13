cmake_minimum_required (VERSION 3.2)
project (plainfsm-tree)

set(SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/parent.cpp
	${CMAKE_CURRENT_LIST_DIR}/base_state.cpp
	${CMAKE_CURRENT_LIST_DIR}/parent_states.cpp
	${CMAKE_CURRENT_LIST_DIR}/parent_state2_states.cpp
	)

set(HEADERS
	${CMAKE_CURRENT_LIST_DIR}/../../include/plain_fsm.h
	${CMAKE_CURRENT_LIST_DIR}/parent.h
	${CMAKE_CURRENT_LIST_DIR}/base_state.h
	${CMAKE_CURRENT_LIST_DIR}/events.h
	${CMAKE_CURRENT_LIST_DIR}/parent_states.h
	${CMAKE_CURRENT_LIST_DIR}/parent_state2_states.h
	)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../include)
	
add_executable(plainfsm-tree ${SOURCES} ${HEADERS})

set_target_properties(plainfsm-tree PROPERTIES 
	CXX_STANDARD 11
	)

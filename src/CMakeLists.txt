set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib)

set(SOURCES
	main.cpp
	${LIBRARY_DIR}/Base.h
	${LIBRARY_DIR}/Dictionary.h
	${LIBRARY_DIR}/Dictionary.cpp
	${LIBRARY_DIR}/Hash.h
	${LIBRARY_DIR}/Hash.cpp)

add_executable(${CMAKE_PROJECT_NAME}
			   ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
						   ${LIBRARY_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
					  fmt::fmt
					  OpenSSL::SSL
					  RNG)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h)

add_executable(
		${CMAKE_PROJECT_NAME}
		${SOURCE_FILES}
)

target_link_libraries(
		${CMAKE_PROJECT_NAME} PRIVATE
		OpenSSL::SSL
)

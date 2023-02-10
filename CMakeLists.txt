cmake_minimum_required(VERSION 3.25)
project(mnemonic_generator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(ENABLED_FLAGS -Wall -Wextra -Werror)
set(DISABLED_FLAGS -Wno-unused -Wno-unused-parameter)

add_compile_options(${ENABLED_FLAGS} ${DISABLED_FLAGS})
add_compile_options(-fsanitize=address,leak)
add_link_options(-fsanitize=address,leak)

find_package(fmt REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/RNG)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

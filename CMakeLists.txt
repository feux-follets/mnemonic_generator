cmake_minimum_required(VERSION 3.25)
project(mnemonic_generator LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "BIP39 Mnemonic Generator")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Diagnostic flags
set(WARNINGS
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
		-Wnon-virtual-dtor
		-Wshadow
		)
add_compile_options(${WARNINGS})

# Sanitizers
set(SANITIZERS -fsanitize=address,undefined)
add_compile_options("$<$<CONFIG:Debug>:${SANITIZERS}>")
add_link_options("$<$<CONFIG:Debug>:${SANITIZERS}>")

# Random flags
set(RANDOM_FLAGS -mrdseed)
add_compile_options(${RANDOM_FLAGS})

# Dependencies
find_package(fmt REQUIRED)
find_package(OpenSSL REQUIRED)

# Source
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

cmake_minimum_required(VERSION 3.29)
project(mnemonic_generator LANGUAGES CXX VERSION 1.0.1 DESCRIPTION "BIP39 Mnemonic Generator")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LINKER_TYPE MOLD)

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

# Random flags
set(RANDOM_FLAGS -mrdseed)
add_compile_options(${RANDOM_FLAGS})

# Dependencies
find_package(OpenSSL REQUIRED)

# Source
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

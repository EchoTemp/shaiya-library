# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.1)

# Set the project details
project(shaiya          VERSION 1.0
        DESCRIPTION     "Shaiya library"
        LANGUAGES       CXX)

# Set language standard
set(CMAKE_CXX_STANDARD 20)

# Include the source code
add_subdirectory(shaiya)
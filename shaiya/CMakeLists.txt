# Collect the source files
file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)

# Add the library build target
add_library(shaiya SHARED ${SRC})

# Define the include directories
target_include_directories(shaiya
        PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>
        PRIVATE
                src)

# Define the linking language
set_target_properties(shaiya PROPERTIES LINKER_LANGUAGE CXX)

# Define the MSVC library runtime to use
set_property(TARGET shaiya PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")

# Add custom definitions
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)
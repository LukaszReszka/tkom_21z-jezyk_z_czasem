project(Jezyk_z_czasem)

# All sources that also need to be tested in unit tests go into a static library
add_library(interpreter STATIC
        interpreter.h
        interpreter.cpp
        context.h
        context.cpp
        funcallcontext.cpp funcallcontext.h scope.cpp scope.h)

target_include_directories(interpreter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
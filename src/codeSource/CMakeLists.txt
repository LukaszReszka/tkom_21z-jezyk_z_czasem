project(Jezyk_z_czasem)

# All sources that also need to be tested in unit tests go into a static library
add_library(codeSource STATIC
        codeSource.h
        codeSource.cpp
        charAndPosition.h
        )

target_include_directories(codeSource PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
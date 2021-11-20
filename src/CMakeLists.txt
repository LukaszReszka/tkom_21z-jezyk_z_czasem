project(Jezyk_z_czasem)

# All sources that also need to be tested in unit tests go into a static library
add_library(exec_and_test STATIC CodeSource.h CodeSource.cpp CharAndPosition.h)
target_include_directories(exec_and_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# The main program
add_executable(tln
        main.cpp)

target_link_libraries(tln PRIVATE exec_and_test)
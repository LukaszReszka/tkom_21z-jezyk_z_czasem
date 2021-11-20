project(Jezyk_z_czasem)

add_executable(tests
        doctest.cpp
        testCharAndPosition.cpp
        testCodeSource.cpp)

target_link_libraries(tests PRIVATE exec_and_test doctest)
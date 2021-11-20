project(Jezyk_z_czasem)

add_executable(tests
        testmain.cpp
        TestCharAndPosition.cpp
        )

target_link_libraries(tests PRIVATE exec_and_test doctest)
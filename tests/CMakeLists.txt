project(Jezyk_z_czasem)

add_executable(tests
        doctest.cpp
        testCharAndPosition.cpp
        testCodeSource.cpp
        testLexer.cpp)

target_link_libraries(tests PRIVATE codeSource lexer doctest)
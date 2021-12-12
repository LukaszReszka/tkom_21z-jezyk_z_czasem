project(Jezyk_z_czasem)

add_executable(tests
        doctest.cpp
        testCharAndPosition.cpp
        testCodeSource.cpp
        testLexer.cpp testParser.cpp)

target_link_libraries(tests PRIVATE codeSource lexer parser doctest)
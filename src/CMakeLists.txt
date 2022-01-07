project(Jezyk_z_czasem)

add_subdirectory(codeSource/)
add_subdirectory(lexer/)
add_subdirectory(parser/)

# The main program
add_executable(tln
        main.cpp)

target_link_libraries(tln PRIVATE parser lexer codeSource)
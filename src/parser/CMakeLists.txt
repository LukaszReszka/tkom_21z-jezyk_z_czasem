project(Jezyk_z_czasem)

# All sources that also need to be tested in unit tests go into a static library
add_library(parser STATIC
        astNode.h
        programNode.h
        returnNode.h
        errorNode.h
        parser.h
        parser.cpp
        whileLoopNode.h blockNode.h ifNode.h elifNode.h elseNode.h funcDefNode.h identifierNode.h funcArgsNode.h)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
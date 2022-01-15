project(Jezyk_z_czasem)

# All sources that also need to be tested in unit tests go into a static library
add_library(parser STATIC
        phrase.h
        value.h
        expression.h
        literal.cpp
        literal.h
        operatoroperation.cpp
        operatoroperation.h
        funcdef.cpp
        funcdef.h
        funccall.cpp
        funccall.h
        returninstr.cpp
        returninstr.h
        showfunc.cpp
        showfunc.h
        whileloop.cpp
        whileloop.h
        ifstatement.cpp
        ifstatement.h
        elifstat.cpp
        elifstat.h
        instruction.cpp
        instruction.h
        command.cpp
        command.h
        programtree.cpp
        programtree.h
        parser.h
        parser.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
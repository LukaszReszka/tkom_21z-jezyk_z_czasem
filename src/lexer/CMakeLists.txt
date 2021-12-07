project(Jezyk_z_czasem)

# All sources that also need to be tested in unit tests go into a static library
add_library(lexer STATIC
        token.h
        timeMoment.h
        timePeriod.h
        lexer.cpp
        lexer.h
        )

target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
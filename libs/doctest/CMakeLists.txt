project(Doctest)

#INTERFACE, because header only library
add_library(doctest INTERFACE)

#INTERFACE targets only have INTERFACE properties
target_include_directories(doctest INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
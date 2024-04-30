cmake_minimum_required(VERSION 3.25)
project(thermostat)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target( docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

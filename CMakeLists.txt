cmake_minimum_required(VERSION 3.10.1)

project(cmaketutorial VERSION 1.0)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)

find_library(myglewlib glew NAMES glew2 GLEW GLEW2 DOC 'glew library')

#if(${myglewlib}) # or : if(${myglewlib} STREQUAL myglewlib-NOTFOUND)
#    message(FATAL_ERROR 'no glew')
#else()
#    message(STATUS "glew found! as ${myglewlib}")
#endif()


configure_file(cmaketutorial_config.h.in cmaketutorial_config.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#           CHECK ALL THE SUBMODULES
###############################################################################
#if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
#    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
#endif()
###############################################################################
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/gtests/CMakeLists.txt")
    message(FATAL_ERROR "The googletest submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#ifdef (USE_ADDER)
    add_subdirectory(Adder)
    target_include_directories(${PROJECT_NAME} 
                            PUBLIC Adder)
    target_link_libraries(${PROJECT_NAME} adder)
#endif


#add_subdirectory(external/glfw)
add_subdirectory(Example)

############ For google tests ######
enable_testing()
add_subdirectory(external/gtests)
add_subdirectory(test)

#target_link_libraries(${PROJECT_NAME} ${myglewlib})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${PROJECT_BINARY_DIR}/cmaketutorial_config.h DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)
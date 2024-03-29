#[
#[[cmake_minimum_required(VERSION 3.24)
project(final_project LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 23)


add_executable(final_project main.cpp)

set(SFML_DIR "E:\\Lib_SFML\\sfml\\SFML-2.5.1\\lib\\cmake\\SFML")


target_link_libraries(cpp_part sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

set(SOURCE_FILES main.cpp)]]



#cmake_minimum_required(VERSION 3.24)
cmake_minimum_required(VERSION 3.23.2)

project(final_project LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
#add modules

add_executable(
        final_project
        main.cpp
        map.h
        global_const.h
        Player.h
        objects/Objects.h
        objects/LineObject.h
        objects/Wall.h
        objects/Point.h)
# add_subdirectory(objects)
target_include_directories(final_project PRIVATE objects)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/kotokrolik.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/Marble.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets)

target_link_libraries(final_project PRIVATE sfml-graphics)
target_compile_features(final_project PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET final_project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:final_project> $<TARGET_FILE_DIR:final_project> COMMAND_EXPAND_LISTS)
endif ()

install(TARGETS final_project)

#target_link_libraries(cpp_part PUBLIC Object_lib)
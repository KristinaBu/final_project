#[[
cmake_minimum_required(VERSION 3.24)
project(cpp_part LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 23)


add_executable(cpp_part main.cpp)

set(SFML_DIR "E:\\Lib_SFML\\sfml\\SFML-2.5.1\\lib\\cmake\\SFML")


target_link_libraries(cpp_part sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

set(SOURCE_FILES main.cpp)
]]





#cmake_minimum_required(VERSION 3.24)
cmake_minimum_required(VERSION 3.23.2)

project(cpp_part LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
#add modules

add_executable(cpp_part main.cpp ray_casting.cpp map.cpp map.h global_const.h Objects.h Objects.cpp Player.cpp Player.h LineObject.h LineObject.h Wall.h Wall.h Point.h Point.h)
#add_subdirectory(Object_lib)

target_link_libraries(cpp_part PRIVATE sfml-graphics)
target_compile_features(cpp_part PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET cpp_part POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:cpp_part> $<TARGET_FILE_DIR:cpp_part> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS cpp_part)

#target_link_libraries(cpp_part PUBLIC Object_lib)
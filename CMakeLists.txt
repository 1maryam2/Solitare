cmake_minimum_required(VERSION 3.16)
project(Sea_Battle_new LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

include_directories(include)

add_executable(Sea_Battle_new ${SOURCES} ${HEADERS})

target_link_libraries(Sea_Battle_new PRIVATE sfml-graphics)
target_compile_features(Sea_Battle_new PRIVATE cxx_std_17)
 

if(WIN32)
    add_custom_command(
        TARGET Sea_Battle_new
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Sea_Battle_new>
        VERBATIM)
endif()

install(TARGETS Sea_Battle_new)

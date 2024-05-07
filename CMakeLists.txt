cmake_minimum_required(VERSION 3.22)
project(SocialMedia)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_STATIC_LIBRARIES FALSE)
    set(BUILD_SHARED_LIBS TRUE)
    message(STATUS "Debug build")
else()
    set(SFML_STATIC_LIBRARIES TRUE)
    set(BUILD_SHARED_LIBS FALSE)
    message(STATUS "Release build")
endif()

set(SFML_DIR "C:/msys64/ucrt64/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS audio graphics main network window system REQUIRED)
find_package(CryptoPP REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src/headers)
target_include_directories(${PROJECT_NAME} PRIVATE C:/msys64/ucrt64/include/SFML)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-audio sfml-graphics sfml-main sfml-network sfml-window sfml-system CryptoPP)

# if (BUILD_SHARED_LIBS)
#     file (GLOB SFML_DLLS "C:/msys64/ucrt64/bin/libsfml-*.dll")
#     foreach(DLL ${SFML_DLLS})
#         add_custom_command(
#             TARGET ${PROJECT_NAME}
#             COMMAND ${CMAKE_COMMAND} -E copy_if_different
#             ${DLL}
#             $<TARGET_FILE_DIR:${PROJECT_NAME}>
#         )
#     endforeach()
# endif()
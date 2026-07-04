cmake_minimum_required(VERSION 3.23)

project(TicTacToe)

add_executable(run)
target_sources(run
    PRIVATE
        src/main.cpp
        src/board.cpp

    PUBLIC
        FILE_SET HEADERS
        FILES
            include/board.h
)

if(
  (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR
  (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
)

  target_compile_options(run PRIVATE /W3)

elseif(
  (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
)

  target_compile_options(run PRIVATE -Wall)
  target_compile_options(run PRIVATE -Wextra)
  target_compile_options(run PRIVATE -Werror)
  target_compile_options(run PRIVATE -Wfatal-errors)

endif()

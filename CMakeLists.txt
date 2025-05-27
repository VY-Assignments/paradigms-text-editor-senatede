cmake_minimum_required(VERSION 3.31)
project(paradigms_text_editor_senatede)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(paradigms_text_editor_senatede
        main.cpp
        TextEditor.cpp)

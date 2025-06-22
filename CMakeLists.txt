cmake_minimum_required(VERSION 3.31)
project(paradigms_text_editor_senatede)

set(CMAKE_CXX_STANDARD 14)

include_directories(LineTypes History)

add_executable(main
        Program/main.cpp
        Program/TextEditor.cpp
        Program/LineTypes/Line.h
        Program/LineTypes/String.cpp
        Program/History/Text.cpp
        Program/History/TextStateStack.cpp
)
cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        main_parser.cpp
        tokens_define.cpp
        process_ahead.cpp
        file_writer.cpp
        structure_define.cpp
        Test/MacroRight
        Test/StringRight
        Test/MacroWrong)

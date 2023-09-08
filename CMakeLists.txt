cmake_minimum_required(VERSION 3.26)
project(GrammarParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(GrammarParser main.cpp
        file_writer.cpp
        main_parser.cpp
        process_ahead.cpp
        structure_define.cpp
        tokens_define.cpp
        Test/MacroRight
        Test/MacroWrong)

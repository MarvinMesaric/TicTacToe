cmake_minimum_required(VERSION 3.29)
project(TicTacToeUni C)

set(CMAKE_C_STANDARD 23)

add_executable(TicTacToeUni main.c
        gui.c
        highscoreList.c
        winCheck.c
        gui.h
        highscoreList.h
        winCheck.h
)

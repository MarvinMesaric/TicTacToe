cmake_minimum_required(VERSION 3.29)
project(TicTacToeUni C)

set(CMAKE_C_STANDARD 23)

add_executable(TicTacToeUni main.c
        gui.c
        fileIO.c
        winCheck.c
        gui.h
        fileIO.h
        winCheck.h
        tttGame.c
        tttGame.h
)

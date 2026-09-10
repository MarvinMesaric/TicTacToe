//
// Created by Marvin on 15.01.2025.
//
#define SIZE 3
#ifndef TTTGAME_H
#define TTTGAME_H
bool isValidMove(char *board[SIZE][SIZE], int move);
char flipPlayer(char currentPlayer);
void clearBoard(char *board[SIZE][SIZE]);
int computerMove(void);
void inputMove(char *board[SIZE][SIZE], int move, char currentPlayer);
void playerGame(char *board[SIZE][SIZE], char currentPlayer);
void computerGame(char *board[SIZE][SIZE], char currentPlayer);

#endif //TTTGAME_H

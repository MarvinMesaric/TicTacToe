//
// Created by Marvin on 21.12.2024.
//

#ifndef FILEIO_H
#define FILEIO_H
void readMessage(char *fileName, char *search);
void saveMessage(char *filename, char *entry);
void saveGame(char *board[SIZE][SIZE], char currentPlayer, char *filename);
char loadGame(char *board[SIZE][SIZE], char *filename, int saveNumber);
void updateScore(const char *filename, const char *name);
#endif //FILEIO_H

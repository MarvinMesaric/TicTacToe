//
// Created by Marvin on 15.01.2025.
//
#include "winCheck.h"
#include "tttGame.h"
#include "fileIO.h"
#include "gui.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

bool isValidMove(char *board[SIZE][SIZE], int move) {
    int row = (move - 1 ) / SIZE;
    int col = (move - 1) % SIZE;
    if (move >= 1 && move <= 9 && (board[row][col] != 'O' && board[row][col] != 'X')) {
        return true;
    }else {
        printf("Invalider Zug\n");
        return false;
    }
}
int computerMove(void) {
    return rand() % 9;
}
void inputMove(char *board[SIZE][SIZE], int move, char currentPlayer) {
    int row = (move - 1 ) / SIZE;
    int col = (move - 1) % SIZE;
    board[row][col] = currentPlayer;
}

char flipPlayer(char currentPlayer) {
    if (currentPlayer == 'X') {
        return 'O';
    }else {
        return 'X';
    }
}
void clearBoard(char *board[SIZE][SIZE]) {
    int counter = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '0' + counter;
            counter++;
        }
    }
}

void playerGame(char *board[SIZE][SIZE], char currentPlayer) {
    int turns = 0;
    char name[10];
    int move;
    while(!checkForWin(board) && turns < 9) {
        readMessage("messages.txt", "#Message 5");
        scanf("%d", &move);
        if (move == 10) {
            saveGame(board, currentPlayer, "scorelist.txt");
            printf("Waehle nun deinen Zug aus! ");
            scanf("%d", &move);
        }
        while(!isValidMove(board, move)) {
            scanf("%d", &move);
        }
        inputMove(board, move, currentPlayer);
        turns++;
        currentPlayer = flipPlayer(currentPlayer);
        printBoard(board);
    }
    if (checkForWin(board) && turns < 9) {
        printf("Spieler %c Gewinnt!\n", currentPlayer);
        clearBoard(board);
        printf("Gebe deinen fuer die Highscore liste ein.");
        scanf("%s", name);
        updateScore("scorelist.txt", name);
    }else {
        printf("Unentschieden!");
    }
}

void computerGame(char *board[SIZE][SIZE], char currentPlayer) {
    int turns = 0;
    int move;
    while (!checkForWin(board) && turns < 9) {
        readMessage("messages.txt", "#Message 5");

        // Spielerzug
        scanf("%d", &move);
        while (!isValidMove(board, move)) {
            printf("Ungültiger Zug. Versuchen Sie es erneut: ");
            scanf("%d", &move);
        }

        inputMove(board, move, currentPlayer);

        if (!checkForWin(board) && turns < 9) {
            turns++;
            currentPlayer = flipPlayer(currentPlayer);
        }else {
            break;
        }

        // Computerzug
        move = computerMove();
        while (!isValidMove(board, move)) {
            move = computerMove();  // Generiere einen neuen Zug, falls der aktuelle ungültig ist
        }

        inputMove(board, move, currentPlayer);

        if (!checkForWin(board) && turns < 9) {
            currentPlayer = flipPlayer(currentPlayer);
            turns++;
        }else {
            break;
        }
        printBoard(board);
    }

    if (checkForWin(board)) {
        printf("Spieler %c gewinnt!\n", currentPlayer);
        clearBoard(board);
    } else {
        printf("Unentschieden!\n");
    }
}





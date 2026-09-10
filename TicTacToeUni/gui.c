#include <stdio.h>
#include "gui.h"
#include <string.h>
#include "fileIO.h"

#define SIZE 3


void printMainGUI(void) {
    readMessage("messages.txt", "#Message 1");
}
void printInstructions(void) {
    readMessage("messages.txt", "#Message 2");
}

void printBoard(char *board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if(i < SIZE - 1) {
            printf("---|---|---\n");
        }
    }
}

void printHighscoreList(void) {
    readMessage("scorelist.txt", "#highscorelist");
}


/*void clearScreen(void){
    printf("\033[2J\033[H"); // \033 leitet die Steuersequenz ein, [2J löscht den bildschirm und [H setzt den cursor wieder nach oben links \033[H
}
*/
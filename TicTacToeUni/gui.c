#include <stdio.h>
#define SIZE 3

void printMainGUI(void) {
    printf("Spielen\n\nSteuerung\n\nHighscore\n\nSpiel beenden");
}
void printInstructions(void) {

}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", board[i][j]);
            if (j < SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if(i < SIZE - 1) {
            printf("---|---|---\n");
        }
        printf("\n");
    }
}

void clearScreen(void){
    printf("\033[2J\033[H");
}
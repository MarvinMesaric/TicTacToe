#include <stdio.h>
#include <stdlib.h>
#include "tttGame.h"
#include "gui.h"
#include "fileIO.h"
#include "winCheck.h"
#include "time.h"

#define SIZE 3


int main (void) {
    srand(time(NULL));
    char *board[SIZE][SIZE] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char *filename, *suche, currentPlayer = 'O';
    int choice, settings, load, save;

    //clearScreen();

    while (choice != 5) {
        printMainGUI();
        if (scanf("%d", &choice) != 1) {
            // Ungültige Eingabe, Eingabepuffer bereinigen
            printf("Ungueltige Eingabe! Versuchen Sie es erneut!\n");
            while(getchar() != '\n');  // Eingabepuffer leeren
            continue;  // Schleife fortsetzen
        }
        switch (choice) {
            case 1:
                printf("Welchen Modus wollen sie Spielen?\n1 Mehrspieler\t| 2 Computermodus\n");
                readMessage("messages.txt", "#Message 3");
                readMessage("messages.txt", "#Message 4");

                scanf("%d", &settings);
                if (settings == 1) {
                    printBoard(board);
                    playerGame(board, currentPlayer);
                }
                else if (settings == 2) {
                    printBoard(board);
                    computerGame(board, currentPlayer);
                }else {
                    printf("Ungueltige Eingabe! Versuchen Sie es erneut!\n");
                }
            break;

            case 2:
                printInstructions();
            break;

            case 3:
                printHighscoreList();
            break;

            case 4:
                printf("Welchen Spielstand wollen Sie laden? (1-3)");
                scanf("%d", &load);
                loadGame(board, "scorelist.txt", load);
            break;
            
            case 5:
                printf("Das Programm wird beendet!");
            break;

            default:
                printf("ngueltige Eingabe! Versuchen Sie es erneut!\n");
            break;
        }
    }
    return 0;
}

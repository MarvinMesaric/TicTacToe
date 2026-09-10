#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MESSAGE_LENGTH_MAX 256
#define SIZE 3

void readMessage(char *fileName, char *search) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error beim Oeffnen der Datei %s\n", fileName);
        return;
    }
    char col[MESSAGE_LENGTH_MAX];
    bool found = false;

    while (fgets(col, MESSAGE_LENGTH_MAX, file)) {
        // Teilstring wird gesucht
        if (strstr(col, search)) {
            found = true;
            continue; // Überspringe die Zeile mit der Kennung
        }

        // Wenn Nachricht gefunden, Zeilen ausgeben, bis eine neue Nachricht beginnt
        if (found) {
            if (col[0] == '#') {
                break;
            }
            printf("%s\n", col);
        }
    }
    fclose(file);
}
// Speichert eine Nachricht im Datei mit einer fortlaufenden Nummer
void saveMessage(char *filename, char *entry) {
    FILE *file = fopen(filename, "a+"); // Datei im Anhaengemodus oeffnen
    if (file == NULL) {
        printf("Fehler beim Oeffnen der Datei\n");
        return;
    }
    char col[MESSAGE_LENGTH_MAX];
    int lastNumber = 0;

    // Bestehende Nachrichten durchsuchen, um die letzte Nummer zu finden
    while (fgets(col, MESSAGE_LENGTH_MAX, file)) {
        if (strncmp(col, "#Message", 11) == 0) {
            int number;
            if (sscanf(col, "#Message %d", &number) == 1) {
                if (number > lastNumber) {
                    lastNumber = number;
                }
            }
        }
    }
    // Neue Nachricht nummerieren und speichern
    int newNumber = lastNumber + 1;
    fprintf(file, "\n#Message %d\n%s\n", newNumber, entry);

    printf("Nachricht erfolgreich gespeichert als '#Message %d'.\n", newNumber);
    fclose(file);
}

// Speichert das Spiel in einer Datei mit einer fortlaufenden Nummer
void saveGame(char *board[SIZE][SIZE], char currentPlayer, char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Fehler beim oeffnen der Datei zum Speichern.\n");
        return;
    }

    // Bestehende Spielstaende durchsuchen, um die letzte Nummer zu finden
    int lastNumber = 0;
    char col[MESSAGE_LENGTH_MAX];
    while (fgets(col, MESSAGE_LENGTH_MAX, file)) {
        if (strncmp(col, "#savescore", 10) == 0) {
            int number;
            if (sscanf(col, "#savescore %d", &number) == 1) {
                if (number > lastNumber) {
                    lastNumber = number;
                }
            }
        }
    }

    // Neuer Spielstand
    int newNumber = lastNumber + 1;
    fprintf(file, "\n#savescore %d\n", newNumber);

    // Speichern des Spielfeldes
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(file, "%c", board[i][j]);
            if (j < SIZE - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    // Speichern des aktuellen Spielers
    fprintf(file, "%c\n", currentPlayer);

    printf("Spiel erfolgreich gespeichert als 'savescore %d'.\n", newNumber);
    fclose(file);
}

// Laedt einen Spielstand aus der Datei basierend auf der gesuchten Nummer
char loadGame(char *board[SIZE][SIZE], char *filename, int saveNumber) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei zum Laden.\n");
        return '\0';  // Fehler beim Laden, Rückgabe eines ungültigen Spielers
    }

    char col[MESSAGE_LENGTH_MAX];
    int currentSave = 0;

    while (fgets(col, MESSAGE_LENGTH_MAX, file)) {
        if (strncmp(col, "#savescore", 10) == 0) {
            // Wenn wir die gesuchte Nummer finden, laden wir den Spielstand
            int number;
            if (sscanf(col, "#savescore %d", &number) == 1) {
                currentSave = number;
                if (currentSave == saveNumber) {
                    // Spielfeld laden
                    for (int i = 0; i < SIZE; i++) {
                        for (int j = 0; j < SIZE; j++) {
                            if (fscanf(file, " %c", &board[i][j]) != 1) {
                                printf("Fehler beim Laden des Spielfeldes.\n");
                                fclose(file);
                                return '\0';  // Fehler beim Laden
                            }
                        }
                    }

                    // Aktuellen Spieler laden
                    char currentPlayer;
                    if (fscanf(file, " %c", &currentPlayer) != 1) {
                        printf("Fehler beim Laden des aktuellen Spielers.\n");
                        fclose(file);
                        return '\0';  // Fehler beim Laden
                    }

                    fclose(file);
                    printf("Spiel erfolgreich geladen! Aktueller Spieler: %c\n", currentPlayer);
                    return currentPlayer;  // Erfolgreiches Laden
                }
            }
        }
    }

    printf("Spielstand mit der Nummer %d nicht gefunden.\n", saveNumber);
    fclose(file);
    return '\0';  // Spielstand nicht gefunden
}

void updateScore(const char *filename, const char *name) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        printf("Fehler: Datei konnte nicht geöffnet werden.\n");
        return;
    }

    char line[256];
    long highscorePos = -1;
    int found = 0;

    // Suchen nach #highscore und speichern der Position
    while (fgets(line, MESSAGE_LENGTH_MAX, file)) {
        if (strncmp(line, "#highscore", 10) == 0) {
            highscorePos = ftell(file); // Position nach der #highscore-Zeile merken
            break;
        }
    }

    if (highscorePos == -1) {
        printf("Fehler: #highscore nicht gefunden.\n");
        fclose(file);
        return;
    }

    // Datei-Pointer zur #highscore-Position setzen
    fseek(file, highscorePos, SEEK_SET);

    // Namen und Punktzahlen nach #highscore durchsuchen
    while (fgets(line, MESSAGE_LENGTH_MAX, file)) {
        char existingName[100];
        int score;

        if (sscanf(line, "%99s %d", existingName, &score) == 2) {
            if (strcmp(existingName, name) == 0) {
                // Name gefunden, Punktzahl erhöhen
                found = 1;
                fseek(file, -(long)strlen(line), SEEK_CUR); // Datei-Pointer auf Zeilenanfang setzen
                fprintf(file, "%-99s %d\n", existingName, score + 1); // Punktzahl aktualisieren
                break;
            }
        }
    }

    // Wenn Name nicht gefunden wurde, neuen Eintrag hinzufügen
    if (!found) {
        fseek(file, 0, SEEK_END); // Datei-Pointer ans Ende setzen
        fprintf(file, "%s %d\n", name, 1); // Neuen Namen mit Punktzahl 1 hinzufügen
    }

    fclose(file);
}
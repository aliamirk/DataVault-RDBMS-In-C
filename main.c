#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu_operations.h"

void displayMenu() {
    printf("\n");
    printf(" ---------------------------------------------------\n");
    printf(" |            Database Management System           |\n");
    printf(" |-------------------------------------------------|\n");
    printf(" | 1. Create Database                              |\n");
    printf(" | 2. View Databases                               |\n");
    printf(" | 3. Delete Database                              |\n");
    printf(" | 4. Tables Menu                                  |\n");
    printf(" ---------------------------------------------------\n");
    printf("\nEnter your choice: ");
}

int main() {
    int choice;

    do {
        system("clear || cls");

        // Display the menu
        displayMenu();

        // Read user input
        scanf("%d", &choice);

        // Handle the user's choice
        switch (choice) {
            case 1:
                printf("\nYou selected: Create Database\n");
                createDatabase();
                break;
            case 2:
                printf("\nYou selected: View Databases\n");
                break;
            case 3:
                printf("\nYou selected: Delete Database\n");
                break;
            case 4:
                printf("\nYou selected: Tables Menu\n");
                break;
            case 0:
                return 0;
                break;    
            default:
                return 0;
        }

        // Pause and wait for user to press Enter
        printf("\nPress Enter to continue...");
        getchar(); // Consume newline
        getchar(); // Wait for Enter

    } while (choice != 0);

    return 0;
}

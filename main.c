#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu_operations.h"
#include "library-functions.h"


int main() {
    int choice;
    int NoDIRS = getDBlength();
    char DBNAME[NoDIRS][50]; // Contains Name of all the Available Databases.

    do {
        system("clear || cls");

        // Display Main Menu
        displayMenu();

        scanf("%d", &choice);

        // Handle the user's choice
        switch (choice) {
            case 1:
                printf("\nYou selected: Create Database\n");
                createDatabase();
                printf("\nPress Enter to continue...");
                getchar(); 
                getchar();
                main();
                break;
            case 2:
                printf("\nYou selected: View Databases\n");
                printf("Number of directories: %d\n", NoDIRS);
                if(NoDIRS != -1){
                    viewDatabases(DBNAME, NoDIRS);
                } else{
                    printf("Some Error in getDBLength() Function");
                }
                break;
            case 3:
                printf("\nYou selected: Delete Database\n");
                deleteDatabase(DBNAME, NoDIRS);
                printf("\nPress Enter to continue...");
                getchar(); 
                getchar();
                main();
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
        getchar(); 
        getchar(); 

    } while (choice != 0);

    return 0;
}

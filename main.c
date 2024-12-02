#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu_operations.h"
#include "library-functions.h"
#include "table_operations.h"
#include "record_operations.h"


int main() {
    int choice;
    int NoDIRS = getDBlength();
    int NoTables = getTableLength();
    printf("\ntable length: %d\n", NoTables);
    char TABLE_NAMES[NoTables][200];
    char DB_NAMES[NoDIRS][50]; // Contains Name of all the Available Databases.
    // char *path = TablePathConstructor("Name");
    // free(path);

    do {
        // system("clear || cls");

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
                    viewDatabases(DB_NAMES, NoDIRS);
                } else{
                    printf("Some Error in getDBLength() Function");
                }
                break;
            case 3:
                printf("\nYou selected: Delete Database\n");
                deleteDatabase(DB_NAMES, NoDIRS);
                printf("\nPress Enter to continue...");
                getchar(); 
                getchar();
                main();
                break;
            case 4:
                printf("\nYou selected: Tables Menu\n");
                displayTables(TABLE_NAMES, NoTables);
                break;
            case 5:
                printf("\nYou selected: Create Table\n");
                if(NoDIRS != -1){
                    viewDatabases(DB_NAMES, NoDIRS);
                } else{
                    printf("Some Error in getDBLength() Function");
                }
                createTable();
                printf("\nPress Enter To Return To Main Menu...");
                getchar();
                main();
                break;
            case 6:
                printf("\nYou selected: Delete Table\n");
                if(NoDIRS != -1){
                    viewDatabases(DB_NAMES, NoDIRS);
                } else{
                    printf("Some Error in getDBLength() Function");
                }
                deleteTable();
                printf("\nPress Enter To Return To Main Menu...");
                getchar();
                main();
                break;
            case 7:
                printf("\nYou Selected: Display Records");
                displayRecords(TABLE_NAMES, NoTables);
                break;
            case 8:
                printf("\n You Selected: Create Records");
                createRecord(TABLE_NAMES, NoTables);
                break;
            case 9:
                printf("\nYou Selected: Search Records");
                searchRecord(TABLE_NAMES, NoTables);
                break;
            case 10:
                printf("\nYou Selected: Delete Records");
                deleteRecord(TABLE_NAMES, NoTables);
                break;
            case 0:
                exit(0);
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

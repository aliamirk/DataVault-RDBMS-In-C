#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "menu_operations.h"
#include "library-functions.h"

// Displays the Available Tables and returns the table user selected.
int displayTables(char tables[][200], int tablelength) {
    getTableNames(tables);
    if (tablelength <= 0) {
        printf("No tables found.\n");
        return 0;
    }

    printf("\nAvailable Tables:\n");
    for (int i = 0; i < tablelength; i++) {
        if (strlen(tables[i]) > 0) { // Ensure the string is not empty
            printf("%d - Table: %s\n", i + 1, tables[i]);
        } else {
            printf("%d - (Empty Slot)\n", i + 1); // Debugging empty slots
        }
    }
    int selection;
    printf("\nSelect any Table to Progress further - (1 - %d): ", tablelength);
    scanf("%d", &selection);
    printf("\nYou Selected '%s'\n", tables[selection-1]);
    return selection-1; // Indicate success
}




void createTable(){

    // Call viewDatabases() in main
    getchar();
    char dbName[20];
    printf("\nEnter Name of the Database: ");
    if (fgets(dbName, sizeof(dbName), stdin)) {
        // Removing the newline character if present
        dbName[strcspn(dbName, "\n")] = '\0';
    }

    char tname[20];
    printf("\nEnter Name of the Table: ");
    if (fgets(tname, sizeof(tname), stdin)) {
        // Removing the newline character if present
        tname[strcspn(tname, "\n")] = '\0';
    }

    char *tablepath = TablePathConstructor(dbName, tname);
    printf("\nNew Table Created at '%s'", tablepath);
    


    // Creating the File
    FILE *fp;
    fp = fopen(tablepath, "w"); 

    if (fp == NULL) {
        // Error opening the file
        printf("Error 106: Table '%s' could no be created. [table_operations.c line 66]\n", tname);
    }

    fclose(fp);
    printf("Table '%s' has been successfully created at '%s'", tname, tablepath);
    free(tablepath);

}

void deleteTable(){

    // Call viewDatabases() in main
    getchar();
    char dbName[20];
    printf("\nEnter Name of the Database: ");
    if (fgets(dbName, sizeof(dbName), stdin)) {
        // Removing the newline character if present
        dbName[strcspn(dbName, "\n")] = '\0';
    }

    char tname[20];
    printf("\nEnter Name of the Table: ");
    if (fgets(tname, sizeof(tname), stdin)) {
        // Removing the newline character if present
        tname[strcspn(tname, "\n")] = '\0';
    }

    char *tablepath = TablePathConstructor(dbName, tname);
    printf("\nDeleting Table '%s'... ... .. .\n", tablepath);

    if (remove(tablepath) == 0){
        printf("File '%s' deleted successfully.", tname);
    } else {
        perror("\nError 107: Table '%s' cannot be deleted. [table_operations.c line 99]");
    }
}

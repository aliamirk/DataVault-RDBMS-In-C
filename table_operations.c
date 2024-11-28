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




// void createTable(){

//     // Call viewDatabases() in main
//     getchar();
//     char dbName[20];
//     printf("\nEnter Name of the Database: ");
//     if (fgets(dbName, sizeof(dbName), stdin)) {
//         // Removing the newline character if present
//         dbName[strcspn(dbName, "\n")] = '\0';
//     }

//     char tname[20];
//     printf("\nEnter Name of the Table: ");
//     if (fgets(tname, sizeof(tname), stdin)) {
//         // Removing the newline character if present
//         tname[strcspn(tname, "\n")] = '\0';
//     }

//     char *tablepath = TablePathConstructor(dbName, tname);
//     printf("\nNew Table Created at '%s'", tablepath);
    


//     // Creating the File
//     FILE *fp;
//     fp = fopen(tablepath, "w"); 

//     if (fp == NULL) {
//         // Error opening the file
//         printf("Error 106: Table '%s' could no be created. [table_operations.c line 66]\n", tname);
//     }

//     fclose(fp);
//     printf("Table '%s' has been successfully created at '%s'", tname, tablepath);
//     free(tablepath);

// }

// void createTable() {
//     // Input the Database Name
//     getchar();
//     char dbName[20];
//     printf("\nEnter the name of the Database: ");
//     if (fgets(dbName, sizeof(dbName), stdin)) {
//         // Remove the newline character
//         dbName[strcspn(dbName, "\n")] = '\0';
//     }

//     // Input the Table Name
//     char tname[20];
//     printf("\nEnter the name of the Table: ");
//     if (fgets(tname, sizeof(tname), stdin)) {
//         // Remove the newline character
//         tname[strcspn(tname, "\n")] = '\0';
//     }

//     // Construct the Table Path
//     char *tablepath = TablePathConstructor(dbName, tname);
//     printf("\nNew Table will be created at '%s'\n", tablepath);

//     // Creating the File
//     FILE *fp = fopen(tablepath, "w");
//     if (fp == NULL) {
//         // Error opening the file
//         printf("Error 106: Table '%s' could not be created. [table_operations.c line 66]\n", tname);
//         free(tablepath);
//         return;
//     }

//     // Dynamic Schema Input
//     int attrCount;
//     printf("\nEnter the number of attributes for the table: ");
//     scanf("%d", &attrCount);

//     getchar(); // Clear input buffer
//     char attributes[attrCount][50]; // Store attribute names
//     char types[attrCount][50];      // Store attribute types (e.g., int, float, char)
//     char schemaLine[500] = "";      // Schema line to write to file

//     for (int i = 0; i < attrCount; i++) {
//         printf("\nEnter the name of attribute %d: ", i + 1);
//         if (fgets(attributes[i], sizeof(attributes[i]), stdin)) {
//             attributes[i][strcspn(attributes[i], "\n")] = '\0'; // Remove newline
//         }

//         printf("Enter the type of attribute '%s' (e.g., int, float, char): ", attributes[i]);
//         if (fgets(types[i], sizeof(types[i]), stdin)) {
//             types[i][strcspn(types[i], "\n")] = '\0'; // Remove newline
//         }

//         // Append attribute and type to schema line
//         char attrWithType[100];
//         snprintf(attrWithType, sizeof(attrWithType), "%s:%s", attributes[i], types[i]);
//         strcat(schemaLine, attrWithType);
//         if (i < attrCount - 1) {
//             strcat(schemaLine, ","); // Separate attributes with commas
//         }
//     }

//     // Write the Schema as the First Line in the File
//     fprintf(fp, "%s\n", schemaLine);
//     fclose(fp);

//     // Success Message
//     printf("\nTable '%s' has been successfully created with schema:\n", tname);
//     printf("%s\n", schemaLine);

//     free(tablepath);
// }
void createTable() {
    // Input the Database Name
    getchar(); // Clear input buffer
    char dbName[20];
    printf("\nEnter the name of the Database: ");
    if (fgets(dbName, sizeof(dbName), stdin)) {
        dbName[strcspn(dbName, "\n")] = '\0'; // Remove the newline character
    }

    // Input the Table Name
    char tname[20];
    printf("\nEnter the name of the Table: ");
    if (fgets(tname, sizeof(tname), stdin)) {
        tname[strcspn(tname, "\n")] = '\0'; // Remove the newline character
    }

    // Construct the Table Path (add .csv extension)
    char *tablepath = TablePathConstructor(dbName, tname);
    printf("\nNew CSV Table will be created at '%s'\n", tablepath);

    // Creating the CSV File
    FILE *fp = fopen(tablepath, "w");
    if (fp == NULL) {
        printf("Error: Table '%s' could not be created.\n", tname);
        free(tablepath);
        return;
    }

    // Dynamic Schema Input
    int attrCount;
    printf("\nEnter the number of attributes for the table: ");
    scanf("%d", &attrCount);

    getchar(); // Clear input buffer
    char attributes[attrCount][50]; // Store attribute names
    char schemaLine[500] = "";      // Schema line to write to file

    for (int i = 0; i < attrCount; i++) {
        printf("\nEnter the name of attribute %d: ", i + 1);
        if (fgets(attributes[i], sizeof(attributes[i]), stdin)) {
            attributes[i][strcspn(attributes[i], "\n")] = '\0'; // Remove newline
        }

        // Append attribute to schema line
        strcat(schemaLine, attributes[i]);
        if (i < attrCount - 1) {
            strcat(schemaLine, ","); // Separate attributes with commas
        }
    }

    // Write the Schema as the First Line in the File
    fprintf(fp, "%s\n", schemaLine);
    fclose(fp);

    // Success Message
    printf("\nCSV Table '%s' has been successfully created with schema:\n", tname);
    printf("%s\n", schemaLine);

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

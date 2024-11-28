#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "library-functions.h"


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
                break;
            case 2:
                printf("\nYou selected: View Databases\n");
                printf("Number of directories: %d\n", NoDIRS);
                if(NoDIRS != -1){
                    viewDatabases(DBNAME);
                } else{
                    printf("Some Error in getDBLength() Function");
                }
                break;
            case 3:
                printf("\nYou selected: Delete Database\n");
                deleteDatabase(DBNAME, NoDIRS);
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


void createDatabase() {

    char dbName[100];
    char basePath[200];
    char fullPath[300];

    // Set the base path based on the operating system of the user
    #ifdef _WIN32
        strcpy(basePath, "C:\\Users\\Desktop");
    #elif __APPLE__
        strcpy(basePath, "/Users/apple/Desktop");
    #else
        printf("Unsupported operating system.\n");
        return;
    #endif


    // Get database name
    printf("Enter the database name: ");
    scanf("%s", dbName);

    // Join the Base Path and DbName to create full path
    #ifdef _WIN32
        snprintf(fullPath, sizeof(fullPath), "%s\\%s", basePath, dbName);
    #else
        snprintf(fullPath, sizeof(fullPath), "%s/%s", basePath, dbName);
    #endif


    // Create the folder
    #ifdef _WIN32
        if (_mkdir(fullPath) == 0) {
            printf("New Database '%s' created successfully at: %s\n", dbName, fullPath);
        } else {
            perror("Error creating Database");
        }
    #else
        if (mkdir(fullPath, 0777) == 0) {
            printf("Database '%s' created successfully at: %s\n", dbName, fullPath);
        } else {
            perror("Error creating database folder");
        }
    #endif
}


int getDBlength(){

    int nodirs = 0;
    DIR *directory;
    struct dirent *entry;


    directory = opendir("/Users/apple/Desktop"); // Open current directory
    if (directory == NULL) {
        printf("Unable to open directory.\n");
        return -1;
    }


    // Count the number of Databases availabe 
    while((entry = readdir(directory)) != NULL){
        if (entry->d_type == DT_DIR) {
            
            // Skip Hidden Directories
            if (entry->d_name[0] != '.' || (entry->d_name[1] != '\0' && entry->d_name[1] != '.')) {
                nodirs++;
            }
        }
    }

    closedir(directory);
    return nodirs;
}

void getDBNames(char dbName[][50]){
    int noDirs = getDBlength(); // Get the number of directories
    DIR *directory;
    struct dirent *entry;

    directory = opendir("/Users/apple/Desktop"); // Open current directory
    if (directory == NULL) {
        printf("Unable to open directory.\n");
        return;
    }

    printf("\n");

    // Store in Array and Output Available Databases

    int index = 0; 
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Skip Hidden Directories
            if (entry->d_name[0] != '.' || (entry->d_name[1] != '\0' && entry->d_name[1] != '.')) {
                strcpy(dbName[index], entry->d_name); // Store directory name in dbName
                // printf("%d. - %s\n", index + 1, dbName[index]);
                index++;
                if (index >= noDirs) break; // Break when we reach the end
            }
        }
    }

    closedir(directory);
}

void viewDatabases(char dbName[][50]) {
    int noDirs = getDBlength(); // Get the number of directories
    DIR *directory;
    struct dirent *entry;

    directory = opendir("/Users/apple/Desktop"); // Open current directory
    if (directory == NULL) {
        printf("Unable to open directory.\n");
        return;
    }

    printf("\n");

    // Store in Array and Output Available Databases

    int index = 0; 
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Skip Hidden Directories
            if (entry->d_name[0] != '.' || (entry->d_name[1] != '\0' && entry->d_name[1] != '.')) {
                strcpy(dbName[index], entry->d_name); // Store directory name in dbName
                // printf("%d. - %s\n", index + 1, dbName[index]);
                index++;
                if (index >= noDirs) break; // Break when we reach the end
            }
        }
    }

    closedir(directory);
}


// void viewDatabases(char dbName[][50]){
//     int i, noDirs = 0;
//     DIR *directory;
//     struct dirent *entry;

//     directory = opendir("/Users/apple/Desktop"); // Open current directory
//     if (directory == NULL) {
//         printf("Unable to open directory.\n");
//         return;
//     }

//     printf("\n");


//     // Second Pass - Store in Array and Output Available Databases 
//     for (i = 0; i < noDirs; i++) {

//         // Check For Valid Directory
//         while ((entry = readdir(directory)) != NULL) {
//             if (entry->d_type == DT_DIR) {

//                 // Skip Hidden Directories
//                 if (entry->d_name[0] != '.' || (entry->d_name[1] != '\0' && entry->d_name[1] != '.')) {
//                     strcpy(dbName[i], entry->d_name);
//                     printf("%d. - %s\n", i + 1, dbName[i]);
//                     break; // Exit the inner while loop after a valid directory is read.
//                 }
//             }
//         }
//     }

//     closedir(directory);
// }


void deleteDatabase(char dbName[][50], int NoDir){
    char Name[50];
    int i;
    printf("\n");
    viewDatabases(dbName); // Initialize Database Array
    for(i=0; i<NoDir; i++){
        printf("%d. %s\n", i+1, dbName[i]);
    }

    // Get the name of Database to Delete
    // printf("Enter the Name of Database to Delete: ");
    // getchar();
    // fgets(Name, sizeof(Name), stdin);
    // printf("\n%s", Name);

    
}

void tableMenu();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void deleteDatabase(char dbName[][50], int NoDir) {
    printf("\nHere\n");
    struct dirent *entry;
    char path[150], dbPath[100];
    int db;

    // View available databases
    // viewDatabases(dbName, NoDir); 

    // Get the name of the database to delete
    printf("\nSelect the Database to Delete: ");
    scanf("%d", &db);
    if (db < 1 || db > NoDir) {
        printf("Invalid database selection.\n");
        return;
    }
    printf("\nYou selected: %s\n", dbName[db - 1]);

    // Set the base directory path based on the operating system
    #ifdef _WIN32
        snprintf(dbPath, sizeof(dbPath), "C:\\Users\\Desktop\\Databases\\%s", dbName[db - 1]);
    #elif __APPLE__
        snprintf(dbPath, sizeof(dbPath), "/Users/apple/Desktop/Databases/%s", dbName[db - 1]);
    #else
        printf("Error: Unsupported operating system.\n");
        return;
    #endif

    // Open the directory
    DIR *dir = opendir(dbPath);
    if (!dir) {
        perror("Unable to open directory");
        return;
    }

    // Delete all files in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path for each file
        snprintf(path, sizeof(path), "%s/%s", dbPath, entry->d_name);

        // Check if it's a directory
        if (entry->d_type == DT_DIR) {
            printf("Cannot delete nested directories in this implementation: %s\n", path);
            continue;
        }

        // Attempt to delete the file
        printf("Deleting file: %s\n", path);
        if (unlink(path) != 0) {
            perror("Error deleting file");
        }
    }

    closedir(dir);

    // Remove the now-empty directory
    if (rmdir(dbPath) == 0) {
        printf("Database '%s' has been deleted successfully.\n", dbName[db - 1]);
    } else {
        perror("Error deleting database folder");
    }
}

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
    // getTableNames(tables);
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



// Stores the table names in a Array
int getTableLength(){

    int NoTables = 0;
    char basePath[200];
    DB_PathConstructor(basePath); // Get basePath of DB Directory

    if (strlen(basePath) > 0) {
        printf("Base Path: %s\n", basePath);
    } else {
        printf("Error 105: Base Path could not be constructed. [library_functions.c line 150]\n");
    }

    DIR *mainDir, *subDir;
    struct dirent *entry, *subEntry;

    // Open the main directory
    mainDir = opendir(basePath);
    if (mainDir == NULL) {
        perror("Error opening main directory");
        return -1;
    }

    printf("Counting Tables \n\n");

    // Traverse each subdirectory in the main directory
    while ((entry = readdir(mainDir)) != NULL) {
        if (entry->d_type == DT_DIR) { // Check if entry is a directory
            // Skip the current directory (.) and parent directory (..)
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Construct the path to the subdirectory
            char subDirPath[300];
            snprintf(subDirPath, sizeof(subDirPath), "%s/%s", basePath, entry->d_name);

            // Open the subdirectory
            subDir = opendir(subDirPath);
            if (subDir == NULL) {
                perror("Error opening subdirectory");
                continue;
            }

            // Traverse files in the subdirectory
            while ((subEntry = readdir(subDir)) != NULL) {
                // Check if the file has a .txt extension
                if (subEntry->d_type == DT_REG && strstr(subEntry->d_name, ".txt") != NULL) {
                    // Print the full path to the .txt file
                    NoTables +=1;
                }
            }

            closedir(subDir);
        }
    }
    closedir(mainDir);

    return NoTables;
}


void getTableNames(char tableName[][200], int tablesLength) {
    int index = 0; // Keep track of the number of tables found
    char basePath[200];
    DB_PathConstructor(basePath);

    if (strlen(basePath) == 0) {
        printf("Error: Base Path could not be constructed.\n");
        return;
    }

    DIR *mainDir = opendir(basePath);
    if (mainDir == NULL) {
        perror("Error opening main directory");
        return;
    }

    struct dirent *entry, *subEntry;

    // Traverse subdirectories in the main directory
    while ((entry = readdir(mainDir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue; // Skip hidden entries
        }

        char subDirPath[300];
        snprintf(subDirPath, sizeof(subDirPath), "%s/%s", basePath, entry->d_name); // Safely construct subdirectory path

        DIR *subDir = opendir(subDirPath);
        if (subDir == NULL) {
            continue; // Skip if unable to open subdirectory
        }

        // Traverse files in the subdirectory
        while ((subEntry = readdir(subDir)) != NULL) {
            if (subEntry->d_name[0] == '.' || index >= tablesLength) {
                continue; // Skip hidden files or if array is full
            }

            // Check if file has a .txt extension
            if (strstr(subEntry->d_name, ".txt") != NULL) {
                char *path = strstr(subDirPath, "/Databases") ? strstr(subDirPath, "/Databases") : strstr(subDirPath, "\\Databases");
                snprintf(tableName[index], sizeof(tableName[index]), "%s/%s", path, subEntry->d_name); // Safely format and store
                index++;
            }
        }

        closedir(subDir);
    }

    closedir(mainDir);
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu_operations.h"
#include "library-functions.h"
#include "table_operations.h"

int main() {
    int choice;

    do {
        // Dynamically update the number of databases and tables
        int NoDIRS = getDBlength();
        int NoTables = getTableLength();
        char TABLE_NAMES[NoTables][200];
        char DB_NAMES[NoDIRS][50];

        // Clear the screen (cross-platform)
        // system("clear || cls");

        // Display Main Menu
        displayMenu();

        // Get user input for menu choice
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Handle the user's choice
        switch (choice) {
            case 1:
                printf("\nYou selected: Create Database\n");
                createDatabase();
                printf("\nDatabase created successfully. Press Enter to continue...");
                getchar(); 
                getchar(); // To handle lingering newline
                break;

            case 2:
                printf("\nYou selected: View Databases\n");
                if (NoDIRS != -1) {
                    printf("\nNumber of databases: %d\n", NoDIRS);
                    // viewDatabases(DB_NAMES, NoDIRS);
                } else {
                    printf("\nError: Unable to fetch database count.\n");
                }
                printf("\nPress Enter to continue...");
                getchar(); 
                getchar();
                break;

            case 3:
                printf("\nYou selected: Delete Database\n");
                if (NoDIRS > 0) {
                    deleteDatabase(DB_NAMES, NoDIRS);
                } else {
                    printf("\nNo databases available to delete.\n");
                }
                printf("\nPress Enter to continue...");
                getchar(); 
                getchar();
                break;

            case 4:
                printf("\nYou selected: Tables Menu\n");
                if (NoTables > 0) {
                    displayTables(TABLE_NAMES, NoTables);
                } else {
                    printf("\nNo tables available to display.\n");
                }
                printf("\nPress Enter to continue...");
                getchar(); 
                getchar();
                break;

            case 6:
                printf("\nYou selected: Create Table\n");
                if (NoDIRS != -1 && NoDIRS > 0) {
                   // viewDatabases(DB_NAMES, NoDIRS);
                    createTable();
                } else {
                    printf("\nError: No databases available or unable to fetch database count.\n");
                }
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                break;

            case 7:
                printf("\nYou selected: Delete Table\n");
                if (NoDIRS != -1 && NoDIRS > 0) {
                    // viewDatabases(DB_NAMES, NoDIRS);
                    deleteTable();
                } else {
                    printf("\nError: No databases available or unable to fetch database count.\n");
                }
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                break;

            case 0:
                printf("\nExiting the program. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please select a valid option.\n");
                printf("\nPress Enter to continue...");
                getchar();
                getchar();
                break;
        }
    } while (choice != 0);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new record in the selected table (CSV file)
void createRecord(char TABLENAMES[][200], int NoTables) {
    int tableSelected = displayTables(TABLENAMES, NoTables); // Get table index
    char tablePath[300];

    // Construct the full path of the CSV file
    snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);
    printf("\nAdding records to the Table: %s\n", tablePath);

    // Open the CSV file in read mode to get the schema
    FILE *file = fopen(tablePath, "r+");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", tablePath);
        return;
    }

    // Read the first line (schema) from the file
    char schemaLine[500];
    if (fgets(schemaLine, sizeof(schemaLine), file) == NULL) {
        printf("Error: Could not read schema from file %s.\n", tablePath);
        fclose(file);
        return;
    }

    // Parse the schema into attribute names
    char *attributes[50]; // Assuming a maximum of 50 attributes
    int attrCount = 0;
    char *token = strtok(schemaLine, ",\n");
    while (token != NULL) {
        attributes[attrCount++] = strdup(token); // Store attribute name
        token = strtok(NULL, ",\n");
    }

    // Seek to the end of the file to append new records
    fseek(file, 0, SEEK_END);

    char addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        // Prompt the user to enter data for each attribute
        char recordLine[500] = "";
        for (int i = 0; i < attrCount; i++) {
            char value[100];
            printf("Enter value for %s: ", attributes[i]);
            if (fgets(value, sizeof(value), stdin)) {
                value[strcspn(value, "\n")] = '\0'; // Remove newline character
            }
            strcat(recordLine, value);
            if (i < attrCount - 1) {
                strcat(recordLine, ","); // Separate values with commas
            }
        }

        // Append the new record to the file
        fprintf(file, "%s\n", recordLine);
        printf("Record added successfully.\n");

        // Ask user if they want to add more records
        printf("Do you want to add another record? (y/n): ");
        scanf(" %c", &addMore);
        getchar(); // Clear input buffer
    }

    // Free allocated memory for attribute names
    for (int i = 0; i < attrCount; i++) {
        free(attributes[i]);
    }

    fclose(file); // Close the file
    printf("Exiting record creation.\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "menu_operations.h"
#include "library-functions.h"
#include "table_operations.h"

// This function displays all the records in the selected table.
// void displayRecords(char TABLENAMES[][200], int NoTables){
//     int tableSelected = displayTables(TABLENAMES, NoTables); // table index in array
//     char tablePath = TABLENAMES[tableSelected]; // string containing table path
//     printf("\nIn addRecord(): Table %s\n", tablePath);
// }


void displayRecords(char TABLENAMES[][200], int NoTables) {
    int tableSelected = displayTables(TABLENAMES, NoTables); // table index in array
    char tablePath[300]; 
    // Create Table Path
    snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);
    
    printf("\nDisplaying records from table: %s\n", tablePath);

    // Open the CSV file
    FILE *fp = fopen(tablePath, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file '%s'.\n", tablePath);
        return;
    }

    char buffer[1024];  // Buffer to read lines
    int recordNo = 0;   // Record index
    int attributeNo = 0; // Attribute index

    // Read the first line (Schema line)
    if (fgets(buffer, sizeof(buffer), fp)) {
        char *token;
        attributeNo = 0;

        // Display the table header
        printf("\n%-10s", "Record No"); // Header for record number
        token = strtok(buffer, ",");
        while (token != NULL) {
            printf("%-20s", token); // Align each attribute column
            token = strtok(NULL, ",");
        }
        printf("\n"); // End of header row

        // Print a separator line
        for (int i = 0; i < 80; i++) printf("-");
        printf("\n");
    } else {
        printf("Error: Unable to read the file.\n");
        fclose(fp);
        return;
    }

    // Check if the file contains records after the schema
    int hasRecords = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        hasRecords = 1;
        printf("%-10d", ++recordNo); // Print record number
        char *token = strtok(buffer, ",");
        while (token != NULL) {
            printf("%-20s", token); // Align each column
            token = strtok(NULL, ",");
        }
        printf("\n"); // End of record row
    }

    // If no records are present
    if (!hasRecords) {
        printf("\nThe table '%s' contains no records.\n", tablePath);
    }

    fclose(fp);
}


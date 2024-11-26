#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "menu_operations.h"
#include "table_operations.h"

void displayMenu() {
    printf("\n");
    printf(" ---------------------------------------------------\n");
    printf(" |            Database Management System           |\n");
    printf(" |-------------------------------------------------|\n");
    printf(" | 1. Create Database                              |\n");
    printf(" | 2. View Databases                               |\n");
    printf(" | 3. Delete Database                              |\n");
    printf(" ---------------------------------------------------\n");
    printf(" |                     Tables Menu                 |\n");
    printf(" ---------------------------------------------------\n");
    printf(" | 5. Display Table                                |\n");
    printf(" | 6. Create Table                                 |\n");
    printf(" | 7. Delete Table                                 |\n");
    printf(" ---------------------------------------------------\n");
    printf(" | 0. Exit.                                        |\n");
    printf(" ---------------------------------------------------\n");
    printf("\nEnter your choice: ");
}

int getDBlength(){
    int nodirs = 0;
    DIR *directory;
    struct dirent *entry;

    // Open Directory
    #ifdef _WIN32
        directory = opendir("C:\\Users\\Desktop\\Databases"); 
    #elif __APPLE__
        directory = opendir("/Users/apple/Desktop/Databases");
    #else
        printf("Error 102: Unsupported operating system. [library_functions.c line 60]\n");
        return;
    #endif

    if (directory == NULL) {
        printf("Unable to open directory.\n");
        return -1;
    }

    rewinddir(directory); // Reset for each new function call

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

// This function returns the populates the dbName array with the cuurently availabe databases;
void getDBNames(char dbName[][50]){
    int noDirs = getDBlength(); // Get the number of directories
    DIR *directory;
    struct dirent *entry;

    // Open Directory
    #ifdef _WIN32
        directory = opendir("C:\\Users\\Desktop\\Databases"); 
    #elif __APPLE__
        directory = opendir("/Users/apple/Desktop/Databases");
    #else
        printf("Error 102: Unsupported operating system. [library_functions.c line 60]\n");
        return;
    #endif

    
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


// This function returns a string which contains the constructed path of the table name that is to be created.
char* TablePathConstructor(char TableName[]){

    char *fullPath = malloc(300 * sizeof(char));

    if (fullPath == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Join the Base Path and DbName to create full path
    #ifdef _WIN32
        snprintf(fullPath, 300, "%s\\%s.txt", "C:\\Users\\Desktop\\Databases", TableName); 
    #else
        snprintf(fullPath, 300, "%s/%s.txt", "/Users/apple/Desktop/Databases", TableName);
    #endif

    printf("\n%s\n", fullPath);
    return fullPath;

}

  
void DB_PathConstructor(char *basePath) {

    // Set the base path depending on the operating system
    #ifdef _WIN32
        strcpy(basePath, "C:\\Users\\Desktop\\Databases");
    #elif __APPLE__
        strcpy(basePath, "/Users/apple/Desktop/Databases");
    #else
        printf("Error 102: Unsupported operating system. [table_operations.c line 18]\n");
        strcpy(basePath, ""); // Return an empty path in case of error
    #endif

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

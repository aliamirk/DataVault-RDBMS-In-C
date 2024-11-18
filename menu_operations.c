#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void createDatabase() {
    char dbName[100];
    char basePath[200];
    char fullPath[300];

    // Set the base path based on the operating system
    #ifdef _WIN32
        strcpy(basePath, "C:\\Users\\Desktop");
    #elif __APPLE__
        strcpy(basePath, "/Users/apple/Desktop");
    #else
        printf("Unsupported operating system.\n");
        return;
    #endif

    // Prompt the user for the database name
    printf("Enter the database name: ");
    scanf("%s", dbName);

    // Construct the full path
    #ifdef _WIN32
        snprintf(fullPath, sizeof(fullPath), "%s\\%s", basePath, dbName); // Use backslash for Windows
    #else
        snprintf(fullPath, sizeof(fullPath), "%s/%s", basePath, dbName);  // Use forward slash for macOS
    #endif

    // Create the folder
    #ifdef _WIN32
        if (_mkdir(fullPath) == 0) {
            printf("Database '%s' created successfully at: %s\n", dbName, fullPath);
        } else {
            perror("Error creating database folder");
        }
    #else
        if (mkdir(fullPath, 0777) == 0) {
            printf("Database '%s' created successfully at: %s\n", dbName, fullPath);
        } else {
            perror("Error creating database folder");
        }
    #endif
}

void viewDatabases();
void deleteDatabase();
void tableMenu();
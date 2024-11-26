#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "library-functions.h"
#include "table_operations.h"



void createDatabase() {

    char dbName[100];
    char basePath[200];
    char fullPath[300];

    // Set the base path based on the operating system of the user
    #ifdef _WIN32
        strcpy(basePath, "C:\\Users\\Desktop\\Databases");
    #elif __APPLE__
        strcpy(basePath, "/Users/apple/Desktop/Databases");
    #else
        printf("Error 102: Unsupported operating system. [menu_operations.c line 25]\n");
        return;
    #endif


    // Get Database name
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

void viewDatabases(char dbName[][50], int N) {
    getDBNames(dbName);  // Fetch the database names into the array

    if (N <= 0) {
        printf("No databases found. Please create a database first.\n");
        return;
    }

    printf("Listing Available Databases:\n");
    printf("-----------------------------\n");

    // Display the number of available databases
    printf("Total Databases: %d\n\n", N);
    
    // Loop through each database and display its name
    for (int i = 0; i < N; i++) {
        printf("%d. %s\n", i + 1, dbName[i]);
    }

    printf("\nSelect a database to view its tables or perform other operations.\n");
}


void deleteDatabase(char dbName[][50], int NoDir) {
    printf("\nHere\n");
    struct dirent *entry;
    char path[150], dbPath[100];
    int db;

    // View available databases
    viewDatabases(dbName, NoDir);

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
        printf("Deleting Table: %s\n", path);
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


// void deleteDatabase(char dbName[][50], int NoDir){
//     printf("\nHere\n");
//     struct dirent *entry;
//     char path[150], drPath[100]; 
//     int db;
//     printf("\n");
//     viewDatabases(dbName, NoDir); // Initialize Database Array

//     // Get the name of Database to Delete
//     printf("\nSelect the Database to Delete: ");
//     getchar();
//     scanf("%d", &db);
//     printf("\nYou selected: %s", dbName[db-1]);
    

//     // Removing the Directory

//     // Set the base path based on the operating system of the user
//     #ifdef _WIN32
//         strcpy(drPath, "C:\\Users\\Desktop\\Databases");
//     #elif __APPLE__
//         strcpy(drPath, "/Users/apple/Desktop/Databases");
//     #else
//         printf("Error 102: Unsupported operating system. [menu_operations.c line 125]\n");
//         return;
//     #endif

//     DIR *dir = opendir(drPath); // Open Directory
//     if (!dir) {
//         perror("Unable to open directory ---");
//         return;
//     }
       

//     // If then directory is not empty then call function recursively to delete
//     // all tables

//     while ((entry = readdir(dir)) != NULL)
//     {
//         // Skip hidden directories
//         if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
//             continue;
//         }

//         // Join the Base Path and Table Name to create full path
//         #ifdef _WIN32
//         snprintf(path, sizeof(path), "%s\\%s", drPath, entry->d_name); 
//         #else
//         snprintf(path, sizeof(path), "%s/%s", drPath, entry->d_name);
//         #endif  

//         if(unlink(path) != 0){ // Remove Table (File)
//             perror("Error 103: Table cannot be removed. [menu_operations.c line 156]");
//         }

//     }

//     closedir(dir);

//     if (rmdir(drPath) == 0)
//     {   
//         printf("Deleting Database...");
//         printf("\nDatabase '%s' has been deleted successfully..\n", dbName[db-1]);
//     } else{
//         perror("Error 104: Database cannot be removed. [menu_operations.c line 168]");
//     }
    
// }

void tableMenu();
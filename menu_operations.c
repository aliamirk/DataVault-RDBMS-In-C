#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "library-functions.h"



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



void viewDatabases(char dbName[][50], int NoDir) {
    getDBNames();
    int i;
    printf("\n");
    for(i=0; i<NoDir; i++){
        printf("%d. %s\n", i+1, dbName[i]);
    }
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
    struct dirent *entry;
    char path[150], drPath[100]; 
    int db;
    printf("\n");
    viewDatabases(dbName, NoDir); // Initialize Database Array

    // Get the name of Database to Delete
    printf("\nSelect the Database to Delete: ");
    getchar();
    scanf("%d", &db);
    printf("\nYou selected: %s", dbName[db-1]);
    

    // Removing the Directory

    // Set the base path based on the operating system of the user
    #ifdef _WIN32
        strcpy(drPath, "C:\\Users\\Desktop\\Databases");
    #elif __APPLE__
        strcpy(drPath, "/Users/apple/Desktop/Databases");
    #else
        printf("Error 102: Unsupported operating system. [menu_operations.c line 125]\n");
        return;
    #endif

    DIR *dir = opendir(path); // Open Directory
    if (!dir) {
        perror("Unable to open directory ---");
        return;
    }
       

    // If then directory is not empty then call function recursively to delete
    // all tables

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip hidden directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Join the Base Path and Table Name to create full path
        #ifdef _WIN32
        snprintf(path, sizeof(path), "%s\\%s", drPath, entry->d_name); 
        #else
        snprintf(path, sizeof(path), "%s/%s", drPath, entry->d_name);
        #endif  

        if(unlink(path) != 0){ // Remove Table (File)
            perror("Error 103: Table cannot be removed. [menu_operations.c line 156]");
        }

    }

    closedir(dir);

    if (rmdir(drPath) == 0)
    {   
        printf("Deleting Database...");
        printf("\nDatabase '%s' has been deleted successfully..\n", dbName[db-1]);
    } else{
        perror("Error 104: Database cannot be removed. [menu_operations.c line 168]");
    }
    
}

void tableMenu();
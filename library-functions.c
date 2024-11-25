#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
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
char* pathConstructor(char TableName[]){

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
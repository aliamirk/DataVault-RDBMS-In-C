#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

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

    directory = opendir("/Users/apple/Desktop"); // Open current directory
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
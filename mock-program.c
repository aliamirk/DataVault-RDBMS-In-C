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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>





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

    // Prompt the user for the database name
    printf("Enter the database name: ");
    scanf("%s", dbName);

    // Join the Base Path and DbName to create full path
    #ifdef _WIN32
        snprintf(fullPath, sizeof(fullPath), "%s\\%s", basePath, dbName); // Use backslash for Windows
    #else
        snprintf(fullPath, sizeof(fullPath), "%s/%s", basePath, dbName);  // Use forward slash for macOS
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

    int index = 0;  // to store index correctly in dbName
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Skip Hidden Directories
            if (entry->d_name[0] != '.' || (entry->d_name[1] != '\0' && entry->d_name[1] != '.')) {
                strcpy(dbName[index], entry->d_name); // Store directory name in dbName
                printf("%d. - %s\n", index + 1, dbName[index]);
                index++;
                if (index >= noDirs) break; // Break when we reach the expected number of directories
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



void deleteDatabase();
void tableMenu();
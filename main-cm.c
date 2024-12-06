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


// This function returns a string which contains the constructed path of the table name that is to be created.
// Remmmeber to free().
char* TablePathConstructor(char DBName[], char TableName[]){

    char *fullPath = malloc(300 * sizeof(char));

    if (fullPath == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Join the Base Path and DbName to create full path
    #ifdef _WIN32
        snprintf(fullPath, 300, "%s\\%s\\%s.csv", "C:\\Users\\Desktop\\Databases", DBName, TableName); 
    #else
        snprintf(fullPath, 300, "%s/%s/%s.csv", "/Users/apple/Desktop/Databases", DBName, TableName);
    #endif

    printf("\n%s\n", fullPath);
    return fullPath;

}
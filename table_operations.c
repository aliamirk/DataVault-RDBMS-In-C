#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "library-functions.h"

void createTable(){

    char dbName[20];
    printf("Enter Name of the Table: ");
    if (fgets(dbName, sizeof(dbName), stdin)) {
        // Removing the newline character if present
        dbName[strcspn(dbName, "\n")] = '\0';
    }

    char tname[20];
    printf("Enter Name of the Table: ");
    if (fgets(tname, sizeof(tname), stdin)) {
        // Removing the newline character if present
        tname[strcspn(tname, "\n")] = '\0';
    }

    

}
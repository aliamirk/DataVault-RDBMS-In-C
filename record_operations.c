#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "menu_operations.h"
#include "library-functions.h"
#include "table_operations.h"

// This function displays all the records in the selected table.
// void displayRecords(char TABLENAMES[][200], int NoTables){
//     int tableSelected = displayTables(TABLENAMES, NoTables); // table index in array
//     char tablePath = TABLENAMES[tableSelected]; // string containing table path
//     printf("\nIn addRecord(): Table %s\n", tablePath);
// }


void displayRecords(char TABLENAMES[][200], int NoTables) {
    int tableSelected = displayTables(TABLENAMES, NoTables); // table index in array
    char tablePath[300]; 
    // Create Table Path
    snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);
    
    printf("\nDisplaying records from table: %s\n", tablePath);

    // Open the CSV file
    FILE *fp = fopen(tablePath, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file '%s'.\n", tablePath);
        return;
    }

    char buffer[1024];  // Buffer to read lines
    int recordNo = 0;   // Record index
    int attributeNo = 0; // Attribute index

    // Read the first line (Schema line)
    if (fgets(buffer, sizeof(buffer), fp)) {
        char *token;
        attributeNo = 0;

        // Display the table header
        printf("\n%-10s", "Record No"); // Header for record number
        token = strtok(buffer, ",");
        while (token != NULL) {
            printf("%-20s", token); // Align each attribute column
            token = strtok(NULL, ",");
        }
        printf("\n"); // End of header row

        // Print a separator line
        for (int i = 0; i < 80; i++) printf("-");
        printf("\n");
    } else {
        printf("Error: Unable to read the file.\n");
        fclose(fp);
        return;
    }

    // Check if the file contains records after the schema
    int hasRecords = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        hasRecords = 1;
        printf("%-10d", ++recordNo); // Print record number
        char *token = strtok(buffer, ",");
        while (token != NULL) {
            printf("%-20s", token); // Align each column
            token = strtok(NULL, ",");
        }
        printf("\n"); // End of record row
    }

    // If no records are present
    if (!hasRecords) {
        printf("\nThe table '%s' contains no records.\n", tablePath);
    }

    fclose(fp);
}



// void createRecord(char TABLENAMES[][200], int NoTables){
//     int tableSelected = displayTables(TABLENAMES, NoTables); // table index in array
//     char tablePath[300]; 
//     // Create Table Path
//     snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);
//     printf("\nAdding records to the Table: %s\n", tablePath);



// }


// Function to create a new record in the selected table (CSV file)
void createRecord(char TABLENAMES[][200], int NoTables) {
    int tableSelected = displayTables(TABLENAMES, NoTables); // Get table index
    char tablePath[300];

    // Construct the full path of the CSV file
    snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);
    printf("\nAdding records to the Table: %s\n", tablePath);

    // Open the CSV file in read mode to get the schema
    FILE *file = fopen(tablePath, "r+");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", tablePath);
        return;
    }

    // Read the first line (schema) from the file
    char schemaLine[500];
    if (fgets(schemaLine, sizeof(schemaLine), file) == NULL) {
        printf("Error: Could not read schema from file %s.\n", tablePath);
        fclose(file);
        return;
    }

    // Parse the schema into attribute names
    char *attributes[50]; // Assuming a maximum of 50 attributes
    int attrCount = 0;
    char *token = strtok(schemaLine, ",\n");
    while (token != NULL) {
        attributes[attrCount++] = strdup(token); // Store attribute name
        token = strtok(NULL, ",\n");
    }

    // Seek to the end of the file to append new records
    fseek(file, 0, SEEK_END);

    char addMore[10] = "y";
    while (addMore[0] == 'y' || addMore[0] == 'Y') {
        // Prompt the user to enter data for each attribute
        char recordLine[500] = "";
        clearInputBuffer();
        for (int i = 0; i < attrCount; i++) {
            char value[100];
            printf("\nEnter value for %s: ", attributes[i]);

            // Use fgets for consistent input handling
            if (fgets(value, sizeof(value), stdin)) {
                value[strcspn(value, "\n")] = '\0'; // Remove newline character
            }
            strcat(recordLine, value);
            if (i < attrCount - 1) {
                strcat(recordLine, ","); // Separate values with commas
            }
        }

        // Append the new record to the file
        fprintf(file, "%s\n", recordLine);
        printf("Record added successfully.\n");

        // Ask user if they want to add more records
        printf("Do you want to add another record? (y/n): ");
        if (fgets(addMore, sizeof(addMore), stdin)) {
            addMore[strcspn(addMore, "\n")] = '\0'; // Remove newline character
        }
    }

    // Free allocated memory for attribute names
    for (int i = 0; i < attrCount; i++) {
        free(attributes[i]);
    }

    fclose(file); // Close the file
    printf("Exiting record creation.\n");
}




// Function to delete a record from a CSV file
void deleteRecord(char TABLENAMES[][200], int NoTables) {
    int tableSelected = displayTables(TABLENAMES, NoTables); // Get table index
    char tablePath[300];

    // Construct the full path of the CSV file
    snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);

    // Get Search ID from the User
    clearInputBuffer();
    char searchID[50];
    printf("\nEnter ID of the Record to Delete: ");
    fgets(searchID, sizeof(searchID), stdin);
    searchID[strcspn(searchID, "\n")] = '\0'; // Remove newline character

    // Open the original file in read mode
    FILE *file = fopen(tablePath, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", tablePath);
        return;
    }

    // Open a temporary file to write updated content
    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create a temporary file.\n");
        fclose(file);
        return;
    }

    char line[1000];      // Buffer for reading lines
    char lineCopy[1000];  // Copy of the line for tokenization
    int isDeleted = 0;    // Flag to track if the record was deleted
    int lineNum = 0;

    while (fgets(line, sizeof(line), file)) {
        lineNum++;
        strcpy(lineCopy, line); // Create a copy of the line for tokenization

        if (lineNum == 1) {
            // Write the schema (first row) to the temp file
            fprintf(tempFile, "%s", line);
            continue;
        }

        // Extract the ID (first value) from the copied line
        char *recordID = strtok(lineCopy, ",");
        if (recordID && strcmp(recordID, searchID) == 0) {
            // Match found, skip writing this line to the temp file
            isDeleted = 1;
            printf("Record with ID %s found and deleted.\n", searchID);
            continue;
        }

        // Write the unmodified line to the temp file
        fprintf(tempFile, "%s", line);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temp file
    if (isDeleted) {
        remove(tablePath);              // Delete the original file
        rename("temp.csv", tablePath);  // Rename temp file to original name
        printf("The table %s has been updated successfully.\n", TABLENAMES[tableSelected]);
    } else {
        printf("No record with ID %s was found in the table.\n", searchID);
        remove("temp.csv"); // Delete the temporary file since no changes were made
    }
}


void searchRecord();
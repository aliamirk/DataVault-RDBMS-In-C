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
    // int attributeNo; // Attribute index

    // Read the first line (Schema line)
    if (fgets(buffer, sizeof(buffer), fp)) {
        char *token;
        // attributeNo = 0;

        // Display the table header
        printf("\n%-10s", "#.No"); // Header for record number
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


// Function to search for a record by ID and store the record data in an array
void searchRecord(char TABLENAMES[][200], int NoTables) {
    int tableSelected = displayTables(TABLENAMES, NoTables); // Get table index
    char tablePath[300];

    // Construct the full path of the CSV file
    snprintf(tablePath, sizeof(tablePath), "%s%s", "/Users/apple/Desktop/", TABLENAMES[tableSelected]);

    // Get Search ID from the User
    clearInputBuffer();
    char searchID[50];
    printf("\nEnter ID of the Record to Search: ");
    fgets(searchID, sizeof(searchID), stdin);
    searchID[strcspn(searchID, "\n")] = '\0'; // Remove newline character

    // Open the file for reading
    FILE *file = fopen(tablePath, "r");
    if (!file) {
        printf("Error: Could not open file %s.\n", tablePath);
        return;
    }

    // Read schema (first line) from the file
    char schemaLine[1000];
    if (!fgets(schemaLine, sizeof(schemaLine), file)) {
        printf("Error: Could not read schema from the file.\n");
        fclose(file);
        return;
    }

    // Parse schema into an array
    char *schema[100];
    int attributeCount = 0;
    char *token = strtok(schemaLine, ",");
    while (token) {
        schema[attributeCount++] = strdup(token);
        token = strtok(NULL, ",");
    }

    // Array to store the record data as "AttributeName: Value"
    char *recordData[attributeCount];
    int found = 0;

    // Search for the record by ID
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char *recordValues[100];
        int valueIndex = 0;

        // Parse the record's values
        char *valueToken = strtok(line, ",");
        while (valueToken) {
            recordValues[valueIndex++] = strdup(valueToken);
            valueToken = strtok(NULL, ",");
        }

        // Check if the record matches the search ID
        if (strcmp(recordValues[0], searchID) == 0) {
            found = 1;

            // Store the record data as "AttributeName: Value"
            for (int i = 0; i < attributeCount; i++) {
                // Allocate memory for the "AttributeName: Value" format
                size_t length = strlen(schema[i]) + strlen(recordValues[i]) + 4; // For ": " and null terminator
                recordData[i] = malloc(length * sizeof(char));

                // Format and store the data
                snprintf(recordData[i], length, "%s: %s", schema[i], recordValues[i]);
            }
            break;
        }

        // Free memory for the current record values
        for (int i = 0; i < valueIndex; i++) {
            free(recordValues[i]);
        }
    }

    fclose(file);

    if (!found) {
        printf("\nNo record with ID %s was found.\n", searchID);
    } else {
        // Print the record data in the array format (for debugging purposes)
        printf("\nRecord Found (stored in array format):\n");
        printf("\n----------------------------------------------\n");
        for (int i = 0; i < attributeCount - 1; i++) {
            printf("%s  ", recordData[i]);
        }
        char *temp = recordData[attributeCount - 1];
        char *newline_pos = strchr(temp, '\n'); // Find the newline character

        if (newline_pos) {
        // Shift characters to remove the newline before the colon
        memmove(newline_pos, newline_pos + 1, strlen(newline_pos)); // Move characters to remove \n
        }
        printf("%s", temp);
        printf("---------------------------------------------\n");

        // Free memory for record data
        for (int i = 0; i < attributeCount; i++) {
            free(recordData[i]);
        }
    }

    // Free memory for schema
    for (int i = 0; i < attributeCount; i++) {
        free(schema[i]);
    }
}


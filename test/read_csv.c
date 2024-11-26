#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_LINE_LENGTH 200

// Define the employee struct
typedef struct {
    int id;                // Employee ID
    char name[50];         // Employee Name
    int age;               // Employee Age
    char department[50];   // Employee Department
    float salary;          // Employee Salary
} Employee;

// Function to read the employee data from a CSV file
int readEmployeeCSV(const char *filename, Employee employees[], int maxEmployees) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        perror("Error reading header line");
        fclose(file);
        return -1;
    }

    // Read each line of the file
    while (fgets(line, sizeof(line), file) != NULL && count < maxEmployees) {
        Employee emp;

        // Parse the CSV line
        if (sscanf(line, "%d,%49[^,],%d,%49[^,],%f",
                   &emp.id, emp.name, &emp.age, emp.department, &emp.salary) == 5) {
            employees[count++] = emp; // Add the parsed data to the array
        } else {
            printf("Skipping invalid line: %s", line);
        }
    }

    fclose(file);
    return count; // Return the number of employees read
}

// Function to display employees from the array
void displayEmployees(const Employee employees[], int count) {
    printf("ID\tName\t\tAge\tDepartment\tSalary\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%-10s\t%d\t%-10s\t%.2f\n",
               employees[i].id, employees[i].name, employees[i].age,
               employees[i].department, employees[i].salary);
    }
}

int main() {
    Employee employees[MAX_EMPLOYEES]; // Array to store employees
    const char *filename = "employees.csv"; // CSV file name

    // Read employee data from the CSV file
    int count = readEmployeeCSV(filename, employees, MAX_EMPLOYEES);
    if (count > 0) {
        printf("Read %d employees from the file:\n", count);
        displayEmployees(employees, count); // Display the employee data
    } else {
        printf("No employees read from the file.\n");
    }

    return 0;
}

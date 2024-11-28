#ifndef LIBRARY_FUNCTIONS_H
#define LIBRARY_FUNCTIONS_H

void getDBNames(char dbName[][50]); // Stores Availables Databases in Array
int getDBlength(); // Returns No of Databases Avaiable
void displayMenu(); // Display the Main Menu
char* TablePathConstructor(char dbName[], char TableName[]); // Returns pointer to the absolute path of the dbName directory
void DB_PathConstructor(char* basePath);
int getTableLength();
void getTableNames(char tableName[][200]);
void clearInputBuffer();

#endif

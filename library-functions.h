#ifndef LIBRARY_FUNCTIONS_H
#define LIBRARY_FUNCTIONS_H

void getDBNames(char dbName[][50]); // Stores Availables Databases in Array
int getDBlength(); // Returns No of Databases Avaiable
void displayMenu(); // Display the Main Menu
char* pathConstructor(char dbName[]); // Returns pointer to the absolute path of the dbName directory


#endif

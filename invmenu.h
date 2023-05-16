#ifndef INVMENU_H
#define INVMENU_H

#include <iostream>
#include <iomanip>
#include <string>
//#include <fstream>
#include <string.h>
#include "bookinfo.h"
#include "mainmenu.h"
#include "bookType.h"
using namespace std;

//Function Prototypes
void showAddBookOptions(bookType books[], int &recordCount, const int index);
void showInvOptions();
void showEditOptions(bookType books[], int& recordCount, int index);
int lookUpBook(bookType books[], int recordCount, const char mode);
void addBook(bookType books[], int &recordCount, bool &showWarning);
void editBook(bookType books[], int& recordCount);
void deleteBook(bookType books[], int& recordCount, bookType original[]);
string truncate(string input, int width);
string toLower(string target);

#endif
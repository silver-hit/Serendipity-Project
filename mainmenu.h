#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <iomanip>
#include <string>
#include "bookType.h"

 using namespace std;

 //Constant Definitions                                                                                                                                                                                                                     

const int DBSIZE = 20;

 //Function Prototypes                                                                                                                                                                                                                      
 void showMainOptions();
 void invmenu(bookType books[], int & recordCount);
 void reports();
 void cashier(bookType books[], int & recordCount);


int recordCount = 0;


 #endif
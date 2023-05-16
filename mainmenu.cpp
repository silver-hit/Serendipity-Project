#include "mainmenu.h"
#include "cashier.h"
#include "reports.h"
#include "bookinfo.h"
#include "invmenu.h"
#include "bookType.h"

using namespace std;


int main () {
	//Define variables
	string input;
	char choice;
	//bookData books[DBSIZE] {};
	bookType books[DBSIZE]; {}

	int recordCount = 0;

	
	do {
		//Display menu
		showMainOptions();
		cout << left << setw(16) << "┃" << "Enter Your Choice: ";
		
		getline(cin,input);
		if (input == "1") {
			choice = '1';
		} else if (input == "2") {
			choice = '2';
		} else if (input == "3") {
			choice = '3';
		} else if (input == "4") {
			choice = '4';
		} else {
			choice = '0';
		}
		
		while (choice == '0' || input.length() == 0) {
			cout << "\033[H\033[2J\033[3J";
			showMainOptions();
			cout << left << setw(16) << "┃" << "You entered: "; 
			if (input.length() != 0) {
				cout << "\"" << input << "\"" << right << setw(28-input.length()) << "┃" << endl;
			} else {
				cout << "'ENTER'" << right << setw(23) << "┃" << endl;
			}
			cout << left << setw(16) << "┃" << setw(42) << "Please enter a number in the range 1-4." << "┃" << endl 
				 << left << "┃" << right << setw(58) << "┃" << endl
				 << left << setw(16) << "┃" << "Enter Your Choice: ";

			getline(cin,input);
			if (input == "1") {
				choice = '1';
			} else if (input == "2") {
				choice = '2';
			} else if (input == "3") {
				choice = '3';
			} else if (input == "4") {
				choice = '4';
			} else {
				choice = '0';
			}
		}
		
		//Clear the screen
		if (choice != '4') {
			cout << "\033[H\033[2J\033[3J";
		}
		
		switch (choice) {
			case '1': {
				//Run Cashier Module
				cashier(books, recordCount);
				break;
			} case '2': {
				//Run Inventory Database Module
				invmenu(books, recordCount);
				break;
			} case '3': {
				///Run Report Module
				reports();
				break;
			}
		}
		
	} while (choice != '4');
	
	//Finish Displaying Menu
	cout << "\033[H\033[2J\033[3J";
	showMainOptions();
	cout << left << setw(16) << "┃" << "Enter Your Choice: 4                      ┃" << endl;
	cout << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl;
	
	return 0;
}

void showMainOptions() {
	cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓"
		 << endl << left << setw(18) << "┃" << setw(40) << "Serendipity Booksellers" 
		 << right << "┃" << endl
		 << left << setw(25) << "┃" << setw(33) << "Main Menu" 
		 << right << "┃" << endl
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "1. Cashier Module" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "2. Inventory Module" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "3. Reports Module" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "4. Exit" 
		 << right << "┃" << endl
		 << left << "┃" << right << setw(58) << "┃" << endl;
}
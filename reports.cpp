#include "mainmenu.h"
#include "reports.h"


void reports()
{
	//Define variables
	string input;
	char choice;
	
	//displays options
	 showRepOptions();
	 
	 do {
		
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
		} else if (input == "5") {
			choice = '5';
		} else if (input == "6") {
			choice = '6';
		} else if (input == "7") {
			choice = '7';
		} else {
			choice = '0';
		}
		
		while (choice == '0' || input.length() == 0) {
			cout << "\033[H\033[2J\033[3J";
			showRepOptions();
			cout << left << setw(16) << "┃" << "You entered: "; 
			if (input.length() != 0) {
				cout << "\"" << input << "\"" << right << setw(28-input.length()) << "┃" << endl;
			} else {
				cout << "'ENTER'" << right << setw(23) << "┃" << endl;
			}
			cout << left << setw(16) << "┃" << setw(42) << "Please enter a number in the range 1-7." << "┃" << endl 
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
			} else if (input == "5") {
				choice = '5'; 
			} else if (input == "6"){
				choice = '6';
			} else if (input == "7") {
				choice = '7';
			} else {
				choice = '0';
			}
		}
		
		while (choice != '7') {
			switch (choice) {
				case '1': {
					repListing();
					
					break;
				} case '2': {
					repWholesale();
					
					break;
				} case '3': {
					repRetail();
					
					break;
				} case '4': {
					repQty();
					
					break;
				} case '5': {
					repCost();
					
					break;
				} case '6': {
					repAge();
					
					break;
				} 
			}
			
			getline(cin,input);
			if (input == "1") {
				choice = '1';
			} else if (input == "2") {
				choice = '2';
			} else if (input == "3") {
				choice = '3';
			} else if (input == "4") {
				choice = '4';
			} else if (input == "5") {
				choice = '5'; 
			} else if (input == "6"){
				choice = '6';
			} else if (input == "7") {
				choice = '7';
			} else {
				choice = '0';
			}
			
			while (choice == '0' || input.length() == 0) {
				cout << "\033[H\033[2J\033[3J";
				showRepOptions();
				cout << left << setw(16) << "┃" << "You entered: "; 
				if (input.length() != 0) {
					cout << "\"" << input << "\"" << right << setw(28-input.length()) << "┃" << endl;
				} else {
					cout << "'ENTER'" << right << setw(23) << "┃" << endl;
				}
				cout << left << setw(16) << "┃" << setw(42) << "Please enter a number in the range 1-7." << "┃" << endl 
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
				} else if (input == "5") {
					choice = '5'; 
				} else if (input == "6"){
					choice = '6';
				} else if (input == "7") {
					choice = '7';
				} else {
					choice = '0';
				}
			}
		}
		
		//Clear the screen
		cout << "\033[H\033[2J\033[3J";
		
	} while (choice != '7');
	
	return;
}

void showRepOptions() {
	cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓"
		 << endl << left << setw(18) << "┃" << setw(40) << "Serendipity Booksellers" 
		 << right << "┃" << endl 
		 << left << setw(25) << "┃" << setw(33) << "Reports" 
		 << right << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "1. Inventory Listing" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "2. Inventory Wholesale Value" 
		 << right << "┃" << endl 
		 << left << setw(16) << "┃" << setw(42) << "3. Inventory Retail Value" 
		 << right << "┃" << endl 
		 << left << setw(16) << "┃" << setw(42) << "4. Listing by Quantity" 
		 << right << "┃" << endl 
		 << left << setw(16) << "┃" << setw(42) << "5. Listing by Cost" 
		 << right << "┃" << endl 
		 << left << setw(16) << "┃" << setw(42) << "6. Listing by Age" 
		 << right << "┃" << endl 
		 << left << setw(16) << "┃" << setw(42) << "7. Return to Main Menu" 
		 << right << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl;
}

void repListing() {
	cout << "\033[H\033[2J\033[3J";
	showRepOptions();
	cout << left << setw(16) << "┃" << setw(42) << "You selected Inventory Listing" << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << "Enter Your Choice: ";
	
	return;
}

void repWholesale() {
	cout << "\033[H\033[2J\033[3J";
	showRepOptions();
	cout << left << setw(16) << "┃" << setw(42) << "You selected Inventory Wholesale Value" << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << "Enter Your Choice: ";
		 
	return;
}

void repRetail() {
	cout << "\033[H\033[2J\033[3J";
	showRepOptions();
	cout << left << setw(16) << "┃" << setw(42) << "You selected Inventory Retail Value" << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << "Enter Your Choice: ";
		 
	return;
}

void repQty() {
	cout << "\033[H\033[2J\033[3J";
	showRepOptions();
	cout << left << setw(16) << "┃" << setw(42) << "You selected Listing by Quantity" << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << "Enter Your Choice: ";
		 
	return;
}

void repCost() {
	cout << "\033[H\033[2J\033[3J";
	showRepOptions();
	cout << left << setw(16) << "┃" << setw(42) << "You selected Listing by Cost" << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << "Enter Your Choice: ";
		 
	return;
}

void repAge() {
	cout << "\033[H\033[2J\033[3J";
	showRepOptions();
	cout << left << setw(16) << "┃" << setw(42) << "You selected Listing by Age" << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << "Enter Your Choice: ";
		 
	return;
}
#include "invmenu.h"
#include "mainmenu.h"

void invmenu(bookType books[] ,int &recordCount) {
	//Define variables
	bookType erased[1];
	
	//resetting struct to 0
	erased[0].setTitle(" ");
	erased[0].setISBN(" ");
	erased[0].setAuthor(" ");
	erased[0].setPublisher(" ");
	erased[0].setDate(" ");;
	erased[0].setQTY(0);
	erased[0].setWholesale(0.00);
	erased[0].setRetail(0.00);
	//end struct defintion
	
	string input;
	string dummy;
	char choice;
	bool showWarning = false;
	
	do {
		//Display menu
		cout << "\033[H\033[2J\033[3J";
		showInvOptions();
		if (showWarning == true) {
		//This code displays a warning message if the user tries to add a book when the database is full
			cout << left << setw(16) << "┃" << setw(42) << "The book database is currently full." << right << "┃" << endl 
				 << left << setw(16) << "┃" << setw(42) << "You must delete a book before adding" << right << "┃" << endl 
				 << left << setw(16) << "┃" << setw(42) << "another." << right << "┃" << endl
				 << left << "┃" << right << setw(58) << "┃" << endl;
				 showWarning = false;
		}
					//Get User input
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
		} else {
			choice = '0';
		}
		
		while (choice == '0' || input.length() == 0) {
			cout << "\033[H\033[2J\033[3J";
			showInvOptions();
			cout << left << setw(16) << "┃" << "You entered: "; 
			if (input.length() != 0) {
				cout << "\"" << input << "\"" << right << setw(30-input.length()) << "┃" << endl;
			} else {
				cout << "'ENTER'" << right << setw(25) << "┃" << endl;
			}
			cout << left << setw(16) << "┃" << setw(42) << "Please enter a number in the range 1-5." << "┃" << endl 
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
			} else {
				choice = '0';
			}
		}
		
		switch (choice) {
			case '1': {
				lookUpBook(books , recordCount, '0');
				cout << left << setw(16) << "┃" << "Enter Your Choice: ";
				
				break;
			} case '2': {
				addBook(books , recordCount, showWarning);
				if (showWarning == false) {
					if (recordCount == DBSIZE) {
						cout << "\033[H\033[2J\033[3J";
						showAddBookOptions(erased, recordCount, 0);
						cout << left << setw(2) << "┃" << "The database is now full. Press ENTER to continue...";
						getline(cin, dummy);
					}
				}
				break;
			} case '3': {
			
				editBook(books, recordCount);
				
				break;
			} case '4': {
				deleteBook(books, recordCount, erased);
				break;
			}
		}
		
		cout << "\033[H\033[2J\033[3J";
		
	} while (choice != '5');
}

void showInvOptions() {
 //Displays Inventory options
	cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓"
		 << endl << left << setw(18) << "┃" << setw(40) << "Serendipity Booksellers" 
		 << right << "┃" << endl
		 << left << setw(20) << "┃" << setw(38) << "Inventory Database" 
		 << right << "┃" << endl
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "1. Look Up a Book" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "2. Add a Book" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "3. Edit a Book" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "4. Delete a Book" 
		 << right << "┃" << endl
		 << left << setw(16) << "┃" << setw(42) << "5. Return to the Main Menu" 
		 << right << "┃" << endl
		 << left << "┃" << right << setw(58) << "┃" << endl;
}

int lookUpBook(bookType books[], int recordCount, const char mode) {

	bool *matching = new bool[recordCount]; //This array is used to store the results of the search. It is used to display the results of the search.
	string yesOrNo;
	string dummy;
	string query;
	string question;
	int bookIndex = -1;
	char yesNoChar = '0';
	int currentResult = 1;
	int results = 0;
	bool cancelSearch = false;
	//start of new segment
	if(mode == 'n') {
		getline(cin, query);
		for (int i = 0; i < recordCount; i++) {
//This if-statement compares the books titles to the user's query. If the code finds the a book title that mathces the user query regardless of capitlization. 
// Once the code finds thee book title it sets mathcing a value of true and increments the result.
			if (toLower(books[i].getTitle()).find(toLower(query)) != toLower(query).npos || toLower(books[i].getISBN()).find(toLower(query)) != toLower(query).npos ||
				toLower(books[i].getAuthor()).find(toLower(query)) != toLower(query).npos ||toLower(books[i].getPublisher()).find(toLower(query)) != toLower(query).npos) {
				matching[i] = true;
				results++;
			} else {
				matching[i] = false;
			}
	}
	
	if (results > 0) {
		for (int i = 0; i < recordCount; i++) {
			if (!cancelSearch) {
				if (matching[i] == true) {
					cout << "\033[H\033[2J\033[3J"; 
					//showInvOptions();
					cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl;
					cout << left << setw(16) << "┃" << setw(42) << ">> CASHIER LOOKUP" << right << "┃" << endl
						 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
						 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
						 << "RESULTS:" << endl
						 << "┃ RESULT #" << currentResult << "/" << results << ": " << endl 
						 << "┃ >> TITLE----: " << books[i].getTitle() << endl
						 //DISPLAY THESE BASED ON CASE (WHICH MATCHES)? - Daniela
						 << "┃ >> ISBN-----: " << books[i].getISBN() << endl
						 << "┃ >> AUTHOR---: " << books[i].getAuthor() << endl
						 << "┃ >> PUBLISHER: " << books[i].getPublisher() << endl
						 << "┃ " << endl
						 << "┃ View this book record?" << endl 
						 << "┃ -> 'y' = yes, 'n' = no, 'c' = cancel search" << endl
						 << "┃ Enter Your Choice: ";
						 
					getline(cin, yesOrNo);
					//Wouldn't it make more sense to use a switch statement here? - Mike
					if (yesOrNo == "y" || yesOrNo == "Y") {
						yesNoChar = 'y';
					} else if (yesOrNo == "n" || yesOrNo == "N") {
						yesNoChar = 'n';
					} else if (yesOrNo == "c" || yesOrNo == "C") {
						yesNoChar = 'c';
					} else {
						yesNoChar = '0';
					}
					
					while (yesNoChar == '0' || yesOrNo.length() == 0) {
			//This while loop  asks the user to input the correct value if the value the char that was entered wasn't y, n, or c i
						cout << "\033[H\033[2J\033[3J";
						//showInvOptions();
						cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl;
						cout << left << setw(16) << "┃" << setw(42) << ">> CASHIER LOOKUP" << right << "┃" << endl
							 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
							 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
							 << "RESULTS:" << endl
							 << "┃ RESULT #" << currentResult << "/" << results << ": " << endl 
							 << "┃ >> TITLE----: " << books[i].getTitle() << endl
							 << "┃ >> ISBN-----: " << books[i].getISBN() << endl
							 << "┃ >> AUTHOR---: " << books[i].getAuthor() << endl
							 << "┃ >> PUBLISHER: " << books[i].getPublisher() << endl
							 << "┃ " << endl
							 << "┃ ERROR: You entered ";
						if (yesOrNo.length() != 0) {
							cout << "\"" << yesOrNo << "\"" << endl;
						} else {
							cout << "'ENTER'" << endl;
						}
						cout << "┃ Please enter 'y', 'n', or 'c'." << endl 
							 << "┃ " << endl
							 << "┃ View this book record?" << endl 
							 << "┃ -> 'y' = yes | 'n' = no | 'c' = cancel search" << endl
							 << "┃ Enter Your Choice: ";
							
						getline(cin, yesOrNo);
						if (yesOrNo == "y" || yesOrNo == "Y") {
							yesNoChar = 'y';
						} else if (yesOrNo == "n" || yesOrNo == "N") {
							yesNoChar = 'n';
						} else if (yesOrNo == "c" || yesOrNo == "C") {
							yesNoChar = 'c';
						} else {
							yesNoChar = '0';
						}
					}
					
					switch (yesNoChar) {
						case 'c': {
							cancelSearch = true;
							break;
						} case 'y': {
							cout << "\033[H\033[2J\033[3J";
							//showInvOptions();
							cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl;
							cout << left << setw(16) << "┃" << setw(42) << ">> CASHIER LOOKUP" << right << "┃" << endl
								 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
								 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
								 << "BOOK INFO:" << endl;
							bookinfo(books , i);
							
							cout << "┃" << endl << "┃ Is this the book you are looking for (y/n)?" << endl
								 << "┃ Enter Your Choice: ";
							
							getline(cin, yesOrNo);
							if (yesOrNo == "y" || yesOrNo == "Y") {
								yesNoChar = 'y';
							} else if (yesOrNo == "n" || yesOrNo == "N") {
								yesNoChar = 'n';
							} else if (yesOrNo == "c" || yesOrNo == "C") {
								yesNoChar = 'c';
							} else {
								yesNoChar = '0';
							}
							
							while (yesNoChar == '0' || yesOrNo.length() == 0) {
								cout << "\033[H\033[2J\033[3J";
								//showInvOptions();
								cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl;
								cout << left << setw(16) << "┃" << setw(42) << ">> CASHIER LOOKUP" << right << "┃" << endl
									 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
								     << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
									 << "BOOK INFO" << endl;
									 bookinfo(books, i);
								cout << "┃ " << endl
									 << "┃ ERROR: You entered ";
								if (yesOrNo.length() != 0) {
									cout << "\"" << yesOrNo << "\"" << endl;
								} else {
									cout << "'ENTER'" << endl;
								}
								cout << "┃ Please enter 'y' or 'n'." << endl 
									 << "┃ " << endl
									 << "┃ Is this the book you are looking for?" << endl 
									 << "┃ Enter Your Choice: ";
									
								getline(cin, yesOrNo);
								if (yesOrNo == "y" || yesOrNo == "Y") {
									yesNoChar = 'y';
								} else if (yesOrNo == "n" || yesOrNo == "N") {
									yesNoChar = 'n';
								} else if (yesOrNo == "c" || yesOrNo == "C") {
									yesNoChar = 'c';
								} else {
									yesNoChar = '0';
								}
							}
							
							if (yesNoChar == 'y') {
								bookIndex = i;
								i = recordCount; //Erase this if major logic errors of unknown origin occur.
							}
//							break;
						}
					}
					
					if (currentResult == results && yesNoChar == 'n' && bookIndex == -1) {
						cout << "\033[H\033[2J\033[3J";
							//showInvOptions();
						//cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
						//	 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
						 cout<< "┣" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
							 << left << "┃ " << "There are no further results for your query." << right << endl
							 << left << "┃ " << "Press ENTER to continue...";
							getline(cin, dummy);
					}
					
					currentResult++;
					
					if (yesNoChar == 'c') {
						cout << "┃ Process abandoned. Press enter to continue...";
						getline(cin, dummy);
					}
				}
			}
		}
	} else {
		cout << "\033[H\033[2J\033[3J";
		//showInvOptions();
		cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl;
		cout << left << setw(16) << "┃" << setw(42) << ">> CASHIER LOOKUP" << right << "┃" << endl
			 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
		     << "┣" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
			 << "┃ There are no matches to your query." << endl
			 << "┃ Press ENTER to return to the main menu...";
		getline(cin, dummy);
	}
		return bookIndex;
	}
	//end of new segment
	cout << "\033[H\033[2J\033[3J";
	showInvOptions();
	cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl 
		 << left << setw(16) << "┃" << "Search: ";
	getline(cin, query);
	for (int i = 0; i < recordCount; i++) {
		if (toLower(books[i].getTitle()).find(toLower(query)) != toLower(query).npos || toLower(books[i].getISBN()).find(toLower(query)) != toLower(query).npos ||
			toLower(books[i].getAuthor()).find(toLower(query)) != toLower(query).npos ||toLower(books[i].getPublisher()).find(toLower(query)) != toLower(query).npos) {
			matching[i] = true;
			results++;
		} else {
			matching[i] = false;
		}
	}
	
	if (results > 0) {
		for (int i = 0; i < recordCount; i++) {
			if (!cancelSearch) {
				if (matching[i] == true) {
					cout << "\033[H\033[2J\033[3J";
					showInvOptions();
					cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
						 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
						 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
						 << "RESULTS:" << endl
						 << "┃ RESULT #" << currentResult << "/" << results << ": " << endl 
						 << "┃ >> TITLE----: " << books[i].getTitle() << endl
						 //DISPLAY THESE BASED ON CASE (WHICH MATCHES)? - Daniela
						 << "┃ >> ISBN-----: " << books[i].getISBN() << endl
						 << "┃ >> AUTHOR---: " << books[i].getAuthor() << endl
						 << "┃ >> PUBLISHER: " << books[i].getPublisher() << endl
						 << "┃ " << endl
						 << "┃ View this book record?" << endl 
						 << "┃ -> 'y' = yes, 'n' = no, 'c' = cancel search" << endl
						 << "┃ Enter Your Choice: ";
						 
					getline(cin, yesOrNo);
					if (yesOrNo == "y" || yesOrNo == "Y") {
						yesNoChar = 'y';
					} else if (yesOrNo == "n" || yesOrNo == "N") {
						yesNoChar = 'n';
					} else if (yesOrNo == "c" || yesOrNo == "C") {
						yesNoChar = 'c';
					} else {
						yesNoChar = '0';
					}
					
					while (yesNoChar == '0' || yesOrNo.length() == 0) {
						cout << "\033[H\033[2J\033[3J";
						showInvOptions();
						cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
							 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
							 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
							 << "RESULTS:" << endl
							 << "┃ RESULT #" << currentResult << "/" << results << ": " << endl 
							 << "┃ >> TITLE----: " << books[i].getTitle() << endl
							 << "┃ >> ISBN-----: " << books[i].getISBN() << endl
							 << "┃ >> AUTHOR---: " << books[i].getAuthor() << endl
							 << "┃ >> PUBLISHER: " << books[i].getPublisher() << endl
							 << "┃ " << endl
							 << "┃ ERROR: You entered ";
						if (yesOrNo.length() != 0) {
							cout << "\"" << yesOrNo << "\"" << endl;
						} else {
							cout << "'ENTER'" << endl;
						}
						cout << "┃ Please enter 'y', 'n', or 'c'." << endl 
							 << "┃ " << endl
							 << "┃ View this book record?" << endl 
							 << "┃ -> 'y' = yes | 'n' = no | 'c' = cancel search" << endl
							 << "┃ Enter Your Choice: ";
							
						getline(cin, yesOrNo);
						if (yesOrNo == "y" || yesOrNo == "Y") {
							yesNoChar = 'y';
						} else if (yesOrNo == "n" || yesOrNo == "N") {
							yesNoChar = 'n';
						} else if (yesOrNo == "c" || yesOrNo == "C") {
							yesNoChar = 'c';
						} else {
							yesNoChar = '0';
						}
					}
					
					switch (yesNoChar) {
						case 'c': {
							cancelSearch = true;
							break;
						} case 'y': {
							cout << "\033[H\033[2J\033[3J";
							showInvOptions();
							cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
								 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
								 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
								 << "BOOK INFO:" << endl;
							bookinfo(books , i);
							
							cout << "┃" << endl << "┃ Is this the book you are looking for (y/n)?" << endl
								 << "┃ Enter Your Choice: ";
							
							getline(cin, yesOrNo);
							if (yesOrNo == "y" || yesOrNo == "Y") {
								yesNoChar = 'y';
							} else if (yesOrNo == "n" || yesOrNo == "N") {
								yesNoChar = 'n';
							} else if (yesOrNo == "c" || yesOrNo == "C") {
								yesNoChar = 'c';
							} else {
								yesNoChar = '0';
							}
							
							while (yesNoChar == '0' || yesOrNo.length() == 0) {
								cout << "\033[H\033[2J\033[3J";
								showInvOptions();
								cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
									 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
									 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
									 << "BOOK INFO" << endl;
									 bookinfo(books, i);
								cout << "┃ " << endl
									 << "┃ ERROR: You entered ";
								if (yesOrNo.length() != 0) {
									cout << "\"" << yesOrNo << "\"" << endl;
								} else {
									cout << "'ENTER'" << endl;
								}
								cout << "┃ Please enter 'y' or 'n'." << endl 
									 << "┃ " << endl
									 << "┃ Is this the book you are looking for?" << endl 
									 << "┃ Enter Your Choice: ";
									
								getline(cin, yesOrNo);
								if (yesOrNo == "y" || yesOrNo == "Y") {
									yesNoChar = 'y';
								} else if (yesOrNo == "n" || yesOrNo == "N") {
									yesNoChar = 'n';
								} else if (yesOrNo == "c" || yesOrNo == "C") {
									yesNoChar = 'c';
								} else {
									yesNoChar = '0';
								}
							}
							
							if (yesNoChar == 'y') {
								bookIndex = i;
								i = recordCount; //Erase this if major logic errors of unknown origin occur.
							}
							break;
						}
					}
					
					if (currentResult == results && yesNoChar == 'n' && bookIndex == -1) {
						cout << "\033[H\033[2J\033[3J";
							showInvOptions();
						cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
							 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
							 << "┣" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
							 << left << "┃ " << "There are no further results for your query." << right << endl
							 << left << "┃ " << "Press ENTER to continue...";
							getline(cin, dummy);
					}
					
					currentResult++;
					
					if (yesNoChar == 'c') {
						cout << "┃ Process abandoned. Press enter to continue...";
						getline(cin, dummy);
					}
				}
			}
		}
	} else {
		cout << "\033[H\033[2J\033[3J";
		showInvOptions();
		cout << left << setw(16) << "┃" << setw(42) << ">> BOOK LOOKUP" << right << "┃" << endl
			 << left << setw(16) << "┃" << "Search: " << setw(34) << query << right << "┃" << endl
			 << "┣" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
			 << "┃ There are no matches to your query." << endl
			 << "┃ Press ENTER to continue...";
		getline(cin, dummy);
	}

		delete [] matching;
		matching = nullptr; 
	return bookIndex;
}

void addBook(bookType *books[] , int &recordCount, bool &showWarning) {
	string input;
	books =  new bookType*[recordCount];
	cin >> *books[recordCount];

	/*char choice;
	
	if (recordCount < DBSIZE) {
		cout << "\033[H\033[2J\033[3J";
		do {
			//Asks the user to eter a choice  of  numbers that range from 1-10. The numbers determine what  propertied of the book they are edditing.
		   //If the user adds in a value that isn't 1-9 then the code will sendd an error message and ask the user to input again.
			showAddBookOptions(books, recordCount, recordCount);
			cout << left << setw(2) << "┃" << "Enter Your Choice (1-10): ";
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
			} else if (input == "8") {
				choice = '8';
			} else if (input == "9") {
				choice = '9';
			} else if (input == "10") {
				choice = '0';
			} else {
				choice = 'a';
			}
			
			//Input Validation
			while (choice == 'a' || input.length() == 0) {
				cout << "\033[H\033[2J\033[3J";
				showAddBookOptions(books, recordCount, recordCount);
				cout << left << setw(2) << "┃" << "You entered: "; 
				if (input.length() != 0) {
					cout << "\"" << input << "\"" << right << setw(44-input.length()) << "┃" << endl;
				} else {
					cout << "'ENTER\'" << right << setw(37) << "┃" << endl;
				}
				cout << left << setw(2) << "┃" << setw(56) << "Please enter a number in the range 1-10." << "┃" << endl 
					 << left << "┃" << right << setw(58) << "┃" << endl
					 << left << setw(2) << "┃" << "Enter Your Choice: ";
				
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
				} else if (input == "8") {
					choice = '8';
				} else if (input == "9") {
					choice = '9';
				} else if (input == "10") {
					choice = '0';
				} else {
					choice = 'a';
				}
			}
			
			switch (choice) {
				case '1': {
					string tempName;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the title of the book: ";
					getline(cin, tempName);
					books[recordCount].setTitle(tempName);
					break;
				} case '2': {
					string tempISBN;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the ISBN of the book: ";
					getline(cin, tempISBN);
					books[recordCount].setISBN(tempISBN);
					break;
				} case '3': {
					string tempAuthor;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the author of the book: ";
					getline(cin, tempAuthor);
					books[recordCount].setAuthor(tempAuthor);
					break;
				} case '4': {
					string tempPub;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the publisher of the book: ";
					getline(cin, tempPub);
					books[recordCount].setPublisher(tempPub);
					break;
				} case '5': {
					string tempDate;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the date the book was added: ";
					getline(cin, tempDate);
					books[recordCount].setDate(tempDate);
					break;
				} case '6': {
					int tempQuantity;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the quanitity of the book on hand: ";
					cin >> tempQuantity;
					cin.ignore(1000, '\n');
					books[recordCount].setQTY(tempQuantity);
					break;
				} case '7': {
					double tempWholesale;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the wholesale cost of the book: ";
					cin >> tempWholesale;
					cin.ignore(1000, '\n');
					books[recordCount].setWholesale(tempWholesale);
					break;
				} case '8': {
					double tempRetail;
					cout << "\033[H\033[2J\033[3J";
					showAddBookOptions(books, recordCount, recordCount);
					cout << left << setw(2) << "┃" << "Please enter the retail price of the book: ";
					cin >> tempRetail;
					cin.ignore(1000, '\n');
					books[recordCount].setRetail(tempRetail);
					break;
				}
			}
			
			if (choice == '9') {
				string dummy;
				cout << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
					 << "ENTRY VALUES:" << endl;
 				bookinfo(books, recordCount);
				cout << "┃" << endl;
//				cout << "Are these values correct (y/n)? "; --Add later?
//				getline(cin, yesNo);
			cout << "┃ This is entry #" << recordCount+1 << ". Press ENTER to continue...";
				getline(cin, dummy);
				recordCount++;
			} else if (choice == '0') {
				books[recordCount].setTitle("");
				books[recordCount].setISBN("");
				books[recordCount].setAuthor("");
				books[recordCount].setPublisher("");
				books[recordCount].setDate("");
				books[recordCount].setQTY(0);
				books[recordCount].setWholesale(0.00);
				books[recordCount].setRetail(0.00);
			}
		} while (choice != '0' && recordCount < DBSIZE);
	} else if (recordCount == DBSIZE) {
		showWarning = true;
	}*/
	cout << "This is back in addBook function: " << endl;
	cout << books[recordCount];
	cout << "Is this info correct" << endl;
	getline(cin, input);
	if(input == "Y" || input == "y")
	{
		recordCount++;
	}

	delete [] books[recordCount];
	books[recordCount] = nullptr;
	return;
}


void editBook(bookType books[], int &recordCount) {
	string yesOrNo;
	char yesNoChar = '0';
	int index;
	bookType original;
	bool nineLastChoice = false;
	
	*books = bookType[recordCount]; //just changed the data structure for edditBook


	index = lookUpBook(books, recordCount, 'e');
	if (index > -1) {
		original = books[index];
	}
	showInvOptions();
	
	if (index > -1) {
		showEditOptions(books, recordCount, index);
		string input;
		char choice;
		
		if (recordCount < DBSIZE+1) {
			cout << "\033[H\033[2J\033[3J";
			do {
				showEditOptions(books , recordCount, index);
				cout << left << setw(2) << "┃" << "Enter Your Choice (1-10): ";
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
				} else if (input == "8") {
					choice = '8';
				} else if (input == "9") {
					choice = '9';
				} else if (input == "10") {
					choice = '0';
				} else {
					choice = 'a';
				}
				
				//Input Validation
				while (choice == 'a' || input.length() == 0) {
					cout << "\033[H\033[2J\033[3J";
					showEditOptions(books , recordCount, index);
					cout << left << setw(2) << "┃" << "You entered: "; 
					if (input.length() != 0) {
						cout << "\"" << input << "\"" << right << setw(44-input.length()) << "┃" << endl;
					} else {
						cout << "'ENTER\'" << right << setw(37) << "┃" << endl;
					}
					cout << left << setw(2) << "┃" << setw(56) << "Please enter a number in the range 1-10." << "┃" << endl 
						 << left << "┃" << right << setw(58) << "┃" << endl
						 << left << setw(2) << "┃" << "Enter Your Choice: ";
					
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
					} else if (input == "8") {
						choice = '8';
					} else if (input == "9") {
						choice = '9';
					} else if (input == "10") {
						choice = '0';
					} else {
						choice = 'a';
					}
				}
				
				switch (choice) {
					case '1': {
						string tempName;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the title of the book: ";
						getline(cin, tempName);
						books[index].setTitle(tempName);
						break;
					} case '2': {
						string tempISBN;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, recordCount);
						cout << left << setw(2) << "┃" << "Please enter the ISBN of the book: ";
						getline(cin, tempISBN);
						books[index].setISBN(tempISBN);
						break;
					} case '3': {
						string tempAuthor;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the author of the book: ";
						getline(cin, tempAuthor);
						books[index].setAuthor(tempAuthor);
						break;
					} case '4': {
						string tempPub;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the publisher of the book: ";
						getline(cin, tempPub);
						books[index].setPublisher(tempPub);
						break;
					} case '5': {
						string tempDate;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the date the book was added: ";
						getline(cin, tempDate);
						books[index].setDate(tempDate);
						break;
					} case '6': {
						int tempQuantity;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the quanitity of the book on hand: ";
						cin >> tempQuantity;
						cin.ignore(1000, '\n');
						books[index].setQTY(tempQuantity);
						break;
					} case '7': {
						double tempWholesale;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the wholesale cost of the book: ";
						cin >> tempWholesale;
						cin.ignore(1000, '\n');
						books[index].setWholesale(tempWholesale);
						break;
					} case '8': {
						double tempRetail;
						cout << "\033[H\033[2J\033[3J";
						showEditOptions(books, recordCount, index);
						cout << left << setw(2) << "┃" << "Please enter the retail price of the book: ";
						cin >> tempRetail;
						cin.ignore(1000, '\n');
						books[index].setRetail(tempRetail);
						break;
					} case '9': {
						string dummy;
						cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl
							 << "ENTRY VALUES:" << endl;
						bookinfo(books, index);
						cout << "┃" << endl;
						cout << "┃ This is entry #" << index+1<< ". Press ENTER to continue...";
						getline(cin, dummy);
						nineLastChoice = true;
						break;
					} case '0': {
						if (!nineLastChoice) {
							cout << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl
								 << "Do you want to save your changes? (y/n): ";
							
							getline(cin, yesOrNo);
							if (yesOrNo == "y" || yesOrNo == "Y") {
								yesNoChar = 'y';
							} else if (yesOrNo == "n" || yesOrNo == "N") {
								yesNoChar = 'n';
							} else {
								yesNoChar = '0';
							}
							
							while (yesNoChar == '0' || yesOrNo.length() == 0) {
									cout << "\033[H\033[2J\033[3J";
									showEditOptions(books , recordCount, index);
									cout << left << setw(2) << "┃" << "Enter Your Choice (1-10): 10" << endl;
									cout << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl;
									cout << "┃ Do you want to save your changes? (y/n): " << yesOrNo << endl
										 << "┃ " << endl
										 << "┃ ERROR: You entered ";
								if (yesOrNo.length() != 0) {
									cout << "\"" << yesOrNo << "\"" << endl;
								} else {
									cout << "'ENTER'" << endl;
								}
								cout << "┃ Please enter 'y' or 'n'." << endl 
									 << "┃ " << endl
									 << "┃ Do you want to save your changes? (y/n): ";					
								getline(cin, yesOrNo);
								if (yesOrNo == "y" || yesOrNo == "Y") {
									yesNoChar = 'y';
								} else if (yesOrNo == "n" || yesOrNo == "N") {
									yesNoChar = 'n';
								} else {
									yesNoChar = '0';
								}
							}
							
							if (yesNoChar == 'n') {
								books[index] = original;
							}
						}
						
						break;
					}
				}
			} while (choice != '0' && recordCount < DBSIZE+1);
		} else {
			cout << endl << "The current index is: " << index;
			cout << endl << "No such book exists.";
		}
	}
			delete [] books;
	
	return;
}

void deleteBook(bookType books[], int& recordCount, bookType original[], const string& isbn) {
	bookType *booksPtr = NULL;
	string yesOrNo;
	string dummy;
	char yesNoChar = '0';
	int loc;
	cout << "\033[H\033[2J\033[3J";
	showInvOptions();
	loc = lookUpBook(books, recordCount, 'd');
	if (loc > -1) {
		cout << "\033[H\033[2J\033[3J";
		cout << "BOOK INFO:" << endl;
		cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
		bookinfo(books, loc);
		cout << "┣" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
		cout << "┃ Are you sure you want to delete this book? (y/n): ";
		getline(cin, yesOrNo);
		if (yesOrNo == "y" || yesOrNo == "Y") {
			yesNoChar = 'y';
		} else if (yesOrNo == "n" || yesOrNo == "N") {
			yesNoChar = 'n';
		} else if (yesOrNo == "c" || yesOrNo == "C") {
			yesNoChar = 'c';
		} else {
			yesNoChar = '0';
		}
		
		while (yesNoChar == '0' || yesOrNo.length() == 0) {
				cout << "\033[H\033[2J\033[3J";
				cout << "BOOK INFO:";
				cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
				bookinfo(books, loc);
				cout << "┣" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
				cout << "┃ Are you sure you want to delete this book? (y/n): "
					 << "┃ " << endl
					 << "┃ ERROR: You entered ";
			if (yesOrNo.length() != 0) {
				cout << "\"" << yesOrNo << "\"" << endl;
			} else {
				cout << "'ENTER'" << endl;
			}
			cout << "┃ Please enter 'y' or 'n'." << endl 
				 << "┃ " << endl
				 << "┃ Are you sure you want to delete this book? (y/n): ";					
			getline(cin, yesOrNo);
			if (yesOrNo == "y" || yesOrNo == "Y") {
				yesNoChar = 'y';
			} else if (yesOrNo == "n" || yesOrNo == "N") {
				yesNoChar = 'n';
			} else if (yesOrNo == "c" || yesOrNo == "C") {
				yesNoChar = 'c';
			} else {
				yesNoChar = '0';
			}
		}
		
		if (yesNoChar == 'Y' || yesNoChar == 'y') {
			books[loc] = books[recordCount-1]; 
			books[recordCount-1] = original[0];
			cout << "┃ Book deleted! Press enter to continue...";
			recordCount--;
			getline(cin, dummy);
		} else if (yesNoChar == 'N' || yesNoChar == 'n') {
			cout << "┃ Process abandoned. Press enter to continue...";
			getline(cin, dummy);
		}
	}
		

		
	return ;
}

void showAddBookOptions(bookType books[], int &recordCount, const int index) {
	cout << "\033[H\033[2J\033[3J";
	cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓"
		 << endl << left << setw(18) << "┃" << setw(40) << "Serendipity Booksellers" 
		 << right << "┃" << endl 
		 << left << setw(25) << "┃" << setw(33) << "Add Book" 
		 << right << "┃" << endl 
		 << left << setw(11) << "┃" << "DATABASE SIZE: " << DBSIZE << " - CURRENT BOOK COUNT: " << setw(7) << recordCount << right << "┃" << endl
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(2) << "┃" << "1. Enter Book Title              -> --";
	//Check for values
	if (books[index].getTitle().length() != 0) {
		cout << setw(17) << truncate(books[index].getTitle(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl
		 << left << setw(2) << "┃" << "2. Enter ISBN                    -> --";
	if (books[index].getISBN().length() != 0) {
		cout << setw(17) << truncate(books[index].getISBN(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "3. Enter Author                  -> --"; 
	if (books[index].getAuthor().length() != 0) {
		cout << setw(17) << truncate(books[index].getAuthor(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "4. Enter Publisher               -> --";
	if (books[index].getPublisher().length() != 0) {
		cout << setw(17) << truncate(books[index].getPublisher(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "5. Enter Date Added (mm/dd/yyyy) -> --";
	if (books[index].getDate().length() != 0) {
		cout << setw(17) << truncate(books[index].getDate(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "6. Enter Quantity On Hand        -> --" << setw(17) << books[index].getQty()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << "7. Enter Wholesale Cost          -> --$" << setw(16) << fixed << setprecision(2) << books[index].getWholesale()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << "8. Enter Retail Price            -> --$" << setw(16) << fixed << setprecision(2) << books[index].getRetail()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << setw(55) << "9. Save Book to Database"
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << setw(55) << "10. Return to Inventory Menu"
		 << right << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl;
	return;
}

string truncate(string input, int width) {
	string output;
	
	if (input.length() > width) {
		output = input.substr(0, width);
		output.append("...");
	} else {
		output = input;
	}
	
	return output;
}

string toLower(string target) {
	string output = target;
	
	for (int i = 0; i < target.length(); i++) {
		if (isupper(target[i])) {
			output[i] = tolower(output[i]);
		}
	}
	return output;
}

void showEditOptions(bookType books[], int& recordCount, int index) {
	cout << "\033[H\033[2J\033[3J";
	cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓"
		 << endl << left << setw(18) << "┃" << setw(40) << "Serendipity Booksellers" 
		 << right << "┃" << endl 
		 << left << setw(25) << "┃" << setw(33) << "Edit Book" 
		 << right << "┃" << endl 
		 << left << setw(11) << "┃" << "DATABASE SIZE: " << DBSIZE << " - CURRENT BOOK COUNT: " << setw(7) << recordCount << right << "┃" << endl
		 << left << "┃" << right << setw(58) << "┃" << endl
		 << left << setw(2) << "┃" << "1. Edit Book Title              ->  --";
	//Check for values
	if (books[index].getTitle().length() != 0) {
		cout << setw(17) << truncate(books[index].getTitle(), 13);
	} else {
		cout << setw(17)<< "EMPTY";
	}
	
	cout << right << "┃" << endl
		 << left << setw(2) << "┃" << "2. Edit ISBN                    ->  --";
	if (books[index].getISBN().length() != 0) {
		cout << setw(17) << truncate(books[index].getISBN(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "3. Edit Author                  ->  --"; 
	if (books[index].getAuthor().length() != 0) {
		cout << setw(17) << truncate(books[index].getAuthor(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "4. Edit Publisher               ->  --";
	if (books[index].getPublisher().length() != 0) {
		cout << setw(17) << truncate(books[index].getPublisher(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "5. Edit Date Added (mm/dd/yyyy) ->  --";
	if (books[index].getDate().length() != 0) {
		cout << setw(17) << truncate(books[index].getDate(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "6. Edit Quantity On Hand        ->  --" << setw(17) << books[index].getQty()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << "7. Edit Wholesale Cost          ->  --$" << setw(16) << fixed << setprecision(2) << books[index].getWholesale()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << "8. Edit Retail Price            ->  --$" << setw(16) << fixed << setprecision(2) << books[index].getRetail()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << setw(55) << "9. Save Book to Database"
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << setw(55) << "10. Return to Inventory Menu"
		 << right << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl;
	return;
}

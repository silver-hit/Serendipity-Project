#include "cashier.h"
#include "invmenu.h"


//struct cart {
//	bookType book;
//	int buyNum = 0;
//};

void cashier(bookType books[], int &recordCount) {

	string dummy;
	string confirm;

	int index;
	int quantity;
	float subtotal = 0;
	float tax = 0;
	float total = 0;
	bool purchase = false;
//	bool addToCart = false;
//	bool cartDone = false;
//	cart cartItem[DBSIZE];

	cout << "Serendipity Book Sellers" << endl;
	cout << endl;
	
	cout << "Please enter book title, ISBN, or author of the book you wish to purchase" << endl;
	index = lookUpBook(books, recordCount, 'n');
	//tests if a book is found (for out of bounds error)
	if (index > -1) {
		while (purchase == false) {
			cout << "\033[H\033[2J\033[3J";
			
			bookinfo(books, index);
			cout << "┃" << endl;
			
			if(books[index].getQty() == 0) {
				cout << "\033[H\033[2J\033[3J";
				bookinfo(books, index);
				cout << "┃" << endl;
				
				cout << "┃ " << books[index].getTitle() << " is out of stock. Press ENTER to continue...";
				getline(cin, dummy);
				purchase = true;
			} else {
				string qtyInput;
				bool goodNumber = true;
				
				do {
					goodNumber = true;
					
					cout << "┃ How many do you wish to purchase?" << endl << "┃ Enter your choice (0 to cancel): ";
					getline(cin, qtyInput);
					
					cout << "┃" << endl;
					
					if (qtyInput.length() != 0) {
 						for(int i = 0; (i < qtyInput.length()) && goodNumber; i++) {
							goodNumber = ((qtyInput[i] >= '0') && (qtyInput[i] <= '9'));
						}
						
						if (goodNumber) {
							quantity = stoi(qtyInput);
						} else {
							cout << "\033[H\033[2J\033[3J";
							
							bookinfo(books, index);
							cout << "┃" << endl;
							cout << "┃ ERROR: You entered \"" << qtyInput << "\"" << endl << "┃ Please enter an integer between 0 and " << books[index].getQty() << endl << "┃" << endl;
							
							goodNumber = false;
						}
					} else {
						cout << "\033[H\033[2J\033[3J";
						bookinfo(books, index);
						cout << "┃" << endl;
						
						cout << "┃ ERROR: You entered 'ENTER'" << endl << "┃ Please enter an integer between 0 and " << books[index].getQty() << endl << "┃" << endl;
						
						goodNumber = false;
					}
				} while(!goodNumber);
				
				if(quantity == 0) {
					purchase = true;
				} else {
					cout << "\033[H\033[2J\033[3J";
					bookinfo(books, index);
					cout << "┃" << endl;
					
					if (quantity > books[index].getQty()) {
						bool invalidInput = false;
						
						do {
							cout << "\033[H\033[2J\033[3J";
							bookinfo(books, index);
							cout << "┃" << endl;
							
							if (!invalidInput) {
								cout << "┃ Sorry, there are only " << books[index].getQty() << " in stock." << endl 
									 << "┃ Would you like to continue and purchase them (y/n)?" << endl 
									 << "┃" << endl
									 << "┃ Enter your choice: ";
							} else {
								if (confirm.length() != 0) {
									cout << "┃ Sorry, there are only " << books[index].getQty() << " in stock." << endl 
										 << "┃ Would you like to continue and purchase them (y/n)?" << endl 
										 << "┃" << endl
										 << "┃ ERROR: You entered \"" << confirm << "\"" << endl
										 << "┃ Please enter \"y\" (yes) or \"n\" (no)" << endl
										 << "┃" << endl
										 << "┃ Enter your choice: ";
								} else {
									cout << "┃ Sorry, there are only " << books[index].getQty() << " in stock." << endl 
										 << "┃ Would you like to continue and purchase them (y/n)?" << endl 
										 << "┃" << endl
										 << "┃ ERROR: You entered 'ENTER'" << endl
										 << "┃ Please enter \"y\" (yes) or \"n\" (no)" << endl
										 << "┃" << endl
										 << "┃ Enter your choice: ";
								}
							}
								 
							getline(cin, confirm);
							
							if (toLower(confirm) == "yes" || toLower(confirm) == "y") {
								purchase = false;
								invalidInput = false;
								quantity = books[index].getQty();
							} else if (toLower(confirm) == "no" || toLower(confirm) == "n") {
								purchase = true;
								invalidInput = false;
								cout << "\033[H\033[2J\033[3J";
								bookinfo(books, index);
								cout << "┃" << endl;
								
								cout << "┃ Purchase canceled. Press ENTER to continue..." << endl;
								getline(cin, dummy);
							} else {
								invalidInput = true;
							}
						} while (invalidInput);
						
						//Reset variable to be used later
						confirm = "";
					}
					if (!purchase) {
						bool printError = false;
						
						do {
							purchase = true;
							cout << "\033[H\033[2J\033[3J";
							bookinfo(books, index);
							cout << "┃" << endl;
							
							if (printError) {
								if (confirm.length() > 0) {
									cout << "┃ ERROR: You entered \"" << confirm << "\"" << endl << "┃ Please enter \"yes\" or \"no\"" << endl;
									cout << "┃" << endl;
								} else {
									cout << "┃ ERROR: You entered 'ENTER'" << endl << "┃ Please enter \"yes\" or \"no\"" << endl;
									cout << "┃" << endl;
								}
							}
							
							cout << "┃ For " << quantity << " book(s), the price is: " << (books[index].getRetail() * quantity);
							cout << endl << "┃ Do you wish to complete the purchase? (Yes/No): ";
							getline(cin, confirm);
							
							cout << "┃" << endl;
							
							if (toLower(confirm) == "yes") {
								books[index].setQTY(books[index].getQty() - quantity);
								
								subtotal = quantity * books[index].getRetail();
								tax = subtotal * 0.06;
								total = subtotal + tax;
								
								cout << "\033[H\033[2J\033[3J";
								cout << "Serendipity Booksellers" << endl;
//								cout << "Date: " << date << endl << endl;
								cout << "┏" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┓" << endl
									 << "┃Qty   ISBN             Title                            Price        Total    ┃" << endl
									 << "┃______________________________________________________________________________┃" << endl;
								
								cout << "┃" << setw(6) << quantity 
									 << setw(17) << books[index].getISBN() 
									 << setw(33) << truncate(books[index].getTitle(), 29) << "$" << setprecision(2) << fixed 
									 << setw(7) << right << books[index].getRetail() 
									 << setw(5) << "" << "$" << setw(7) << subtotal << " ┃" << endl 
									 << "┃" << setw(81) << "┃" << endl;
								
								cout << "┃" << right << setw(27) << "" << setw(10) << left << "Subtotal" << setw(20) << right << "$" << setw(7) << subtotal << setw(17) << "┃" << endl;
								cout << "┃" << right << setw(27) << "" << setw(10) << left << "Tax" << setw(20) << right << "$" << setw(7) << tax << setw(17) << "┃" << endl;
								cout << "┃" << right << setw(27) << "" << setw(10) << left << "Total" << setw(20) << right << "$" << setw(7) << total << setw(17) << "┃" << endl 
									 << "┃" << setw(81) << "┃" << endl;
								
								cout << "┃" << setw(81) << right << "Thank you for shopping at Serendipity! ┃" << endl
									 << "┗" << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << "┛" << endl;
								
								purchase = true;
								cout << "| Press ENTER to continue...";
								getline(cin, dummy);
								
							} else if (toLower(confirm) == "no") {
								purchase = true;
								cout << "\033[H\033[2J\033[3J";
								bookinfo(books, index);
								cout << "┃" << endl;
								
								cout << "┃ Purchase canceled. Press ENTER to continue..." << endl;
								getline(cin, dummy);
							} else {
								printError = true;
							}
						} while (toLower(confirm) != "yes" && toLower(confirm) != "no");
					}
				}
			}
		}
	}
	
	cout << "\033[H\033[2J\033[3J";
	return;
}
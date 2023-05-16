#include "bookType.h"
#include "invmenu.h"
#include <iostream>


//bookType setters

void bookType :: setTitle(string title)
{
	bookTitle = title;
}
void bookType :: setISBN(string bookIsbn)
{
	isbn = bookIsbn;
}

void bookType :: setAuthor(string bookAuthor)
{
	author = bookAuthor;
}

void bookType :: setPublisher(string bookPub)
{
	publisher = bookPub;
}

void bookType :: setDate(string date)
{
	dateAdded = date;
}

void bookType :: setQTY(int qty)
{
	qtyOnHand = qty;
}

void bookType :: setWholesale(double bookPrice)
{
	wholesale = bookPrice;
}

void bookType :: setRetail(double bookRetail)
{
	retail = bookRetail;
}

//bookType getters
string bookType :: getTitle() const
{
	return bookTitle;
}

string bookType :: getAuthor() const
{
	return author;
}

string bookType :: getISBN() const
{
	return isbn;
}

string bookType :: getPublisher() const
{
	return publisher;
}
string bookType :: getDate() const
{
	return dateAdded;
}

int bookType :: getQty() const 
{
	return qtyOnHand;
}

double bookType :: getWholesale() const
{
	return wholesale;
}

double bookType :: getRetail() const
{
	return retail;
}

//overloaded bookType operators

bool bookType :: operator<(const bookType& otherBook) const
{
	return (qtyOnHand < otherBook.getQty());
} 
bool bookType :: operator<=(const bookType& otherBook) const
{
	return (qtyOnHand <= otherBook.getQty());
}
bool bookType :: operator>=(const bookType& otherBook) const
{
	return (qtyOnHand >= otherBook.getQty());
}
bool bookType :: operator==(const bookType& otherBook) const
{
	return (qtyOnHand == otherBook.getQty());
} 
bool bookType :: operator!=(const bookType& otherBook) const
{
	return (qtyOnHand != otherBook.getQty());
}
//overloaded streams
ostream& operator<< (ostream& write, const bookType& book) // for anyone using this prints like bookinfo
{
	write << left << "┃ Book Title------: ";
	//Check for values
	if (book.getTitle().length() != 0) {
		write << left << setw(18) << book.getTitle();
	} else {
		write << left << setw(18) << "EMPTY";
	}
		
	write << endl << "┃ ISBN------------: ";
	if (book.getISBN().length() != 0) {
		write << left << setw(18) << book.getISBN();
	} else {
		write << left << setw(18) << "EMPTY";
	}
	
	write << left << endl << "┃ Author----------: "; 
	if (book.getAuthor().length() != 0) {
		write << left << setw(18) << book.getAuthor();
	} else {
		write << left << setw(18) << "EMPTY";
	}
	
	write << left << endl << "┃ Publisher-------: ";
	if (book.getPublisher().length() != 0) {
		write << left << setw(18) << book.getPublisher();
	} else {
		write << left << setw(18) << "EMPTY";
	}
	
	write << left << endl << "┃ Date Added------: ";
	if (book.getDate().length() != 0) {
		write<< left << setw(18) << book.getDate();
	} else {
		write << left << setw(18) << "EMPTY";
	}
	
	write << endl << left << "┃ Quantity On Hand: " << setw(18) << book.getQty()<< endl
		 << left << "┃ Wholesale Cost--: $" << setw(17) << fixed << setprecision(2) << book.getWholesale() << endl
		 << left << "┃ Retail Price----: $" << setw(17) << fixed << setprecision(2) << book.getRetail() << endl;
	return write;
}

//do >> operator

istream& operator>>(istream& read, bookType& book)
{
	string dummy;
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
	if (book.getTitle().length() != 0) {
		cout << setw(17) << truncate(book.getTitle(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl
		 << left << setw(2) << "┃" << "2. Enter ISBN                    -> --";
	if (book.getISBN().length() != 0) {
		cout << setw(17) << truncate(book.getISBN(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "3. Enter Author                  -> --"; 
	if (book.getAuthor().length() != 0) {
		cout << setw(17) << truncate(book.getAuthor(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "4. Enter Publisher               -> --";
	if (book.getPublisher().length() != 0) {
		cout << setw(17) << truncate(book.getPublisher(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "5. Enter Date Added (mm/dd/yyyy) -> --";
	if (book.getDate().length() != 0) {
		cout << setw(17) << truncate(book.getDate(), 13);
	} else {
		cout << setw(17) << "EMPTY";
	}
	
	cout << right << "┃" << endl 
		 << left << setw(2) << "┃" << "6. Enter Quantity On Hand        -> --" << setw(17) << book.getQty()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << "7. Enter Wholesale Cost          -> --$" << setw(16) << fixed << setprecision(2) << book.getWholesale()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << "8. Enter Retail Price            -> --$" << setw(16) << fixed << setprecision(2) << book.getRetail()
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << setw(55) << "9. Save Book to Database"
		 << right << "┃" << endl 
		 << left << setw(2) << "┃" << setw(55) << "10. Return to Inventory Menu"
		 << right << "┃" << endl 
		 << left << "┃" << right << setw(58) << "┃" << endl;
	
	string input;
	int choice;
	cout << left << setw(2) << "┃" << "Enter Your Choice (1-10): ";
			getline(read,input);
			
			
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
				cout << book;
				cout << left << setw(2) << "┃" << "You entered: "; 
				if (input.length() != 0) {
					cout << "\"" << input << "\"" << right << setw(44-input.length()) << "┃" << endl;
				} else {
					cout << "'ENTER\'" << right << setw(37) << "┃" << endl;
				}
				cout << left << setw(2) << "┃" << setw(56) << "Please enter a number in the range 1-10." << "┃" << endl 
					 << left << "┃" << right << setw(58) << "┃" << endl
					 << left << setw(2) << "┃" << "Enter Your Choice: ";
				
				getline(read,input);
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
			
			while(choice != '9')
			{	
				
				switch (choice) 
				{
				case '1': {
					
					string tempName;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the title of the book: ";
					getline(read, tempName);
					book.setTitle(tempName);
					
					break;
				} case '2': {
					string tempISBN;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the ISBN of the book: ";
					getline(read, tempISBN);
					book.setISBN(tempISBN);
					break;
				} case '3': {
					string tempAuthor;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the author of the book: ";
					getline(read, tempAuthor);
					book.setAuthor(tempAuthor);
					break;
				} case '4': {
					string tempPub;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the publisher of the book: ";
					getline(read, tempPub);
					book.setPublisher(tempPub);
					break;
				} case '5': {
					string tempDate;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the date the book was added: ";
					getline(read, tempDate);
					book.setDate(tempDate);
					break;
				} case '6': {
					int tempQuantity;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the quanitity of the book on hand: ";
					read >> tempQuantity;
					read.ignore(1000, '\n');
					book.setQTY(tempQuantity);
					break;
				} case '7': {
					double tempWholesale;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the wholesale cost of the book: ";
					read >> tempWholesale;
					read.ignore(1000, '\n');
					book.setWholesale(tempWholesale);
					break;
				} case '8': {
					double tempRetail;
					cout << "\033[H\033[2J\033[3J";
					cout << book;
					cout << left << setw(2) << "┃" << "Please enter the retail price of the book: ";
					read >> tempRetail;
					read.ignore(1000, '\n');
					book.setRetail(tempRetail);
					break;
				} case '9': {
					
					break;
				}
				}
			cout << "\033[H\033[2J\033[3J";
			cout << book;
			cout << left << setw(2) << "┃" << "Enter Your Choice (1-10): ";
			getline(read,input);
			
			
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
				cout << book;
				cout << left << setw(2) << "┃" << "You entered: "; 
				if (input.length() != 0) {
					cout << "\"" << input << "\"" << right << setw(44-input.length()) << "┃" << endl;
				} else {
					cout << "'ENTER\'" << right << setw(37) << "┃" << endl;
				}
				cout << left << setw(2) << "┃" << setw(56) << "Please enter a number in the range 1-10." << "┃" << endl 
					 << left << "┃" << right << setw(58) << "┃" << endl
					 << left << setw(2) << "┃" << "Enter Your Choice: ";
				
				getline(read,input);
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
				
				}//end while
			
			return read;
}


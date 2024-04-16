#include <iostream>
#include <string>
#include <cctype>
#include "bookinfo.h"
#include "invmenu.h"

using namespace std;

extern fstream file;
extern string fileName;
extern BookData bookInfoInventory[SIZE];

void invMenu() {
	//choice declared for capturing user input
	int choice;
	//the program will not repeat if the user enters 5
	do {
		//options are displayed and user is then prompted to choose out of mentioned options
		cout << "Srendipity Booksellers" << endl;
		cout << "   Inventory Database " << endl;
		cout << endl;
		cout << "1.  Look up a book" << endl;
		cout << "2.  Add a Book" << endl;
		cout << "3.  Edit a Book's Record" << endl;
		cout << "4.  Delete a Book" << endl;
		cout << "5.  Return to the Main Menu" << endl;
		cout << endl;
		cout << "Enter Your Choice: ";
		cin >> choice;

		//if the user inputs a number outside the numbers prsented in the menu
		//then the appropriate error will print
		//and the user is prompted for input again
		//this process repeats until valid input is made
		while (choice > 5 || choice < 1) {
			cout << "Please enter a number in range 1 - 5" << endl;
			cout << "Enter Your Choice: ";
			cin >> choice;
		}
		cout << endl;

		//the appropriate response is given to each possible valid input the use can make
		switch (choice) {
		case 1:
			lookUpBook();
			break;
		case 2:
			addBook();
			break;
		case 3:
			editBook();
			break;
		case 4:
			deleteBook();
			break;
		case 5:
			cout << "You selected item 5" << endl;
			break;
		}
		cout << endl;
	} while (choice != 5);
}

void lookUpBook() {
	//declare a variable that captures user input 
	char titleQuery[BOOK_TITLE_MAX_LENGTH];
	//declare a variable that captures the index of the target book listing
	BookData book;

	//prompts user for book target
	cout << "Title: ";
	cin.ignore();
	cin.getline(titleQuery, BOOK_TITLE_MAX_LENGTH);

	//the input is turned to all uppercase for easier finding
	strUpper(titleQuery);

	//the book is searched for
	book = searchFileBook(file, fileName, titleQuery);

	//the appropriate response is given
	if (book.isEmpty() == 1) {
		cout << "There is no book with That title. " << endl;
	}
	else {
		cout << endl;
		bookInfo(book.getISBN(),
			book.getTitle(),
			book.getAuthor(),
			book.getPub(),
			book.getDateAdded(),
			book.getQty(),
			book.getWholesale(),
			book.getRetail());
	}
}

void addBook()
{
	//decalre variable to capture the target index
	int emptyIndex = -1;

	char inputTitle[BOOK_TITLE_MAX_LENGTH];
	char inputISBN[ISBN_MAX_LENGTH];
	char inputAuthor[AUTHOR_MAX_LENGTH];
	char inputPublisher[PUBLISHER_MAX_LENGTH];
	char inputDateAdded[DATE_ADDED_MAX_LENGTH];
	double inputWholesale, inputRetail;
	int inputQty;

	sync(file, fileName, bookInfoInventory, SIZE, SYNC_RECORD_TO_FILE);

	//the book is search for
	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			emptyIndex = i;
		}
	}

	//print the appropriate message
	if (emptyIndex == -1) {
		cout << "There is no space for more books." << endl;
	}
	else {
		//prompts the user for book information and caputures it
		cin.ignore();
		cout << "Title: ";
		cin.getline(inputTitle, BOOK_TITLE_MAX_LENGTH);

		cout << "ISBN: ";
		cin.getline(inputISBN, ISBN_MAX_LENGTH);

		cout << "Author's Name: ";
		cin.getline(inputAuthor, AUTHOR_MAX_LENGTH);

		cout << "Publisher: ";
		cin.ignore();
		cin.getline(inputPublisher, PUBLISHER_MAX_LENGTH);

		cout << "Date It Was Added: ";
		cin.getline(inputDateAdded, DATE_ADDED_MAX_LENGTH);

		cout << "Qunatity: ";
		cin >> inputQty;

		cout << "Wholesale Cost: ";
		cin >> inputWholesale;

		cout << "Retail Cost: ";
		cin >> inputRetail;

		//translates the book info into all uppercase
		strUpper(inputTitle);
		strUpper(inputAuthor);
		strUpper(inputDateAdded);
		strUpper(inputISBN);
		strUpper(inputPublisher);

		bookInfoInventory[emptyIndex].setAuthor(inputAuthor);
		bookInfoInventory[emptyIndex].setPub(inputPublisher);
		bookInfoInventory[emptyIndex].setDateAdded(inputDateAdded);
		bookInfoInventory[emptyIndex].setISBN(inputISBN);
		bookInfoInventory[emptyIndex].setTitle(inputTitle);
		bookInfoInventory[emptyIndex].setQty(inputQty);
		bookInfoInventory[emptyIndex].setWholesale(inputWholesale);
		bookInfoInventory[emptyIndex].setRetail(inputRetail);


		//file is updated with new book
		modifyFile(file, fileName, emptyIndex, bookInfoInventory[emptyIndex]);
	}

	sync(file, fileName, bookInfoInventory, SIZE, SYNCE_FILE_TO_RECORD);
}

void editBook() {


	char inputTitle[BOOK_TITLE_MAX_LENGTH];
	char inputISBN[ISBN_MAX_LENGTH];
	char inputAuthor[AUTHOR_MAX_LENGTH];
	char inputPublisher[PUBLISHER_MAX_LENGTH];
	char inputDateAdded[DATE_ADDED_MAX_LENGTH];
	double inputWholesale = 0, inputRetail = 0;
	int inputQty = 0;

	//declare array to capture user input
	char titleQuery[BOOK_TITLE_MAX_LENGTH];
	//declare varuable to capture target location
	int bookLocation = -1;
	//declare variable to caputre the user intended edit ot he listing
	int editChoice = 0;
	//declare variable for user input to continue
	char continueChoice = '-';

	//prompt the user for what listing the want to edit
	cout << "Title: ";
	cin.ignore();
	cin.getline(titleQuery, BOOK_TITLE_MAX_LENGTH);
	strUpper(titleQuery);

	//search for the title in the file 
	bookLocation = searchFile(file, fileName, titleQuery);

	//if no book is found in file then the appropriate message is made
	if (bookLocation == -1) {
		cout << "There is no book with that title." << endl;
	}
	else {

		//or else an edit loop is started
		do {
			//presents current information of book
			cout << endl;
			bookInfo(bookInfoInventory[bookLocation].getISBN(),
				bookInfoInventory[bookLocation].getTitle(),
				bookInfoInventory[bookLocation].getAuthor(),
				bookInfoInventory[bookLocation].getPub(),
				bookInfoInventory[bookLocation].getDateAdded(),
				bookInfoInventory[bookLocation].getQty(),
				bookInfoInventory[bookLocation].getWholesale(),
				bookInfoInventory[bookLocation].getRetail());

			//prompts which parts to edit
			cout << endl;
			cout << "Edit Menu:" << endl;
			cout << "1. ISBN field" << endl;
			cout << "2. Title field" << endl;
			cout << "3. Author Name field" << endl;
			cout << "4. Publisher field" << endl;
			cout << "5. Date field" << endl;
			cout << "6. Quantity field" << endl;
			cout << "7. Wholesale field" << endl;
			cout << "8. Retail field" << endl;
			cout << "9. Quit" << endl;
			cout << "What would you like to edit? ";
			cin >> editChoice;

			//gives appropriate prompts for every option inputed
			switch (editChoice) {
			case 1:
				cout << "Type New ISBN here: ";
				cin.ignore();
				cin.getline(inputISBN, ISBN_MAX_LENGTH);
				strUpper(inputISBN);
				break;
			case 2:
				cout << "Type New Title here: ";
				cin.ignore();
				cin.getline(inputTitle, BOOK_TITLE_MAX_LENGTH);
				strUpper(inputTitle);
				break;
			case 3:
				cout << "Type New Author Name here: ";
				cin.ignore();
				cin.getline(inputAuthor, AUTHOR_MAX_LENGTH);
				strUpper(inputAuthor);
				break;
			case 4:
				cout << "Type New Publisher here: ";
				cin.ignore();
				cin.getline(inputPublisher, PUBLISHER_MAX_LENGTH);
				strUpper(inputPublisher);
				break;
			case 5:
				cout << "Type New Date here: ";
				cin.ignore();
				cin.getline(inputDateAdded, DATE_ADDED_MAX_LENGTH);
				strUpper(inputDateAdded);
				break;
			case 6:
				cout << "Type New Quantity here: ";
				cin.ignore();
				cin >> inputQty;
				break;
			case 7:
				cout << "Type New Wholesale here: ";
				cin.ignore();
				cin >> inputWholesale;
				break;
			case 8:
				cout << "Type New Retail here: ";
				cin.ignore();
				cin >> inputRetail;
				break;
			case 9:
				continueChoice = 's';
				break;
			default:
				cout << "That is not an option, please retry." << endl;
				//if input validation fires off, then continue will default to 's', meaning skip to the next iteration of the loop
				continueChoice = 's';
				break;
			}

			bookInfoInventory[bookLocation].setAuthor(inputAuthor);
			bookInfoInventory[bookLocation].setPub(inputPublisher);
			bookInfoInventory[bookLocation].setDateAdded(inputDateAdded);
			bookInfoInventory[bookLocation].setISBN(inputISBN);
			bookInfoInventory[bookLocation].setTitle(inputTitle);
			bookInfoInventory[bookLocation].setQty(inputQty);
			bookInfoInventory[bookLocation].setWholesale(inputWholesale);
			bookInfoInventory[bookLocation].setRetail(inputRetail);

			//the newly edited version of the book is then saved to the file
			modifyFile(file, fileName, bookLocation, bookInfoInventory[bookLocation]);

			//if 's' is defaulted then skip to the next iteration as invalid input was made
			if (continueChoice == 's') {
				continue;
			}

			//prompt user to make another edit to book information 
			cout << "Would you like to edit another field? (y/n): ";
			cin >> continueChoice;

		} while (continueChoice == 'y' || continueChoice == 'Y');
	}


}

void deleteBook() {
	BookData empty;

	//variable that captures the input for what the user wants to delete
	char titleQuery[BOOK_TITLE_MAX_LENGTH];
	//variable that captures the location of the book the user wants to delete
	int bookLocation = -1;
	char continueChoice = '-';

	//prompts user for title of the book 
	cout << "Title: ";
	cin.ignore();
	cin.getline(titleQuery, BOOK_TITLE_MAX_LENGTH);
	strUpper(titleQuery);

	//title is searched for in the file
	bookLocation = searchFile(file, fileName, titleQuery);

	//if no such title is found in the file then print the appropriate message
	if (bookLocation == -1) {
		cout << "There is no book with That title. " << endl;
	}
	else {
		//print the found book
		bookInfo(bookInfoInventory[bookLocation].getISBN(),
			bookInfoInventory[bookLocation].getTitle(),
			bookInfoInventory[bookLocation].getAuthor(),
			bookInfoInventory[bookLocation].getPub(),
			bookInfoInventory[bookLocation].getDateAdded(),
			bookInfoInventory[bookLocation].getQty(),
			bookInfoInventory[bookLocation].getWholesale(),
			bookInfoInventory[bookLocation].getRetail());
		cout << endl;

		//promtpt the user for another chance to back out of deleting the book
		cout << "Are you sure you want to delete this book? (y/n): ";
		cin >> continueChoice;
		//if the prompt is confirmed then delelte the book listing in both the 
		//array and the file
		if (continueChoice == 'y' || continueChoice == 'Y') {
			modifyFile(file, fileName, bookLocation, empty);
			bookInfoInventory[bookLocation].removeBook();
			cout << "Book data has been deleted." << endl;
		}
	}


}


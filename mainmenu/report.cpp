#include <iostream>
#include <iomanip>
#include <string>
#include "bookinfo.h"
#include "report.h"


using namespace std;

extern fstream file;
extern string fileName;
extern BookData bookInfoInventory[SIZE];

void report() {
	//choice declared for capturing user input
	int choice = 0;

	do {

		//options are displayed and user is then prompted to choose out of mentioned options
		cout << "Serendipity Booksellers" << endl;
		cout << "        Reports        " << endl;
		cout << endl;
		cout << "1. Inventory Listing   " << endl;
		cout << "2. Inventory Wholesale Value" << endl;
		cout << "3. Inventory Retail Value" << endl;
		cout << "4. Lisiting by Quantity" << endl;
		cout << "5. Listing by Cost" << endl;
		cout << "6. Listing by Age" << endl;
		cout << "7. Return to Main Menu" << endl;
		cout << endl;
		cout << "Enter Your Choice: ";
		cin >> choice;

		//if the user inputs a number outside the numbers prsented in the menu
		//then the appropriate error will print
		//and the user is prompted for input again
		//This process repeats until valid input is made 
		while (choice > 7 || choice < 1) {
			cout << "Please enter a number in range 1 - 7" << endl;
			cout << "Enter Your Choice: ";
			cin >> choice;
		}
		cout << endl;

		//the appropriate response is given to each possible valid input the use can make
		switch (choice) {
		case 1:
			repListing();
			break;
		case 2:
			repWholesale();
			break;
		case 3:
			repRetail();
			break;
		case 4:
			repQty();
			break;
		case 5:
			repCost();
			break;
		case 6:
			repAge();
			break;
		case 7:
			cout << "You selected item 7" << endl;
			break;
		}
		cout << endl;
	} while (choice != 7);
}

void repListing() {
	char continuePress;
	cout << "Report Module - Listing - " << repDate() << endl;
	cout << endl;
	cout << "TITLE--------------------------------------------|ISBN---------|AUTHOR------------------------|PUBLISHER---------------------|DATE ADDED|QUANTITY  |RETAIL PRICE|WHOLESALE   |" << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			cout << "[Empty]" << endl;
			continue;
		}
		bookInfoLine(bookInfoInventory[i].getTitle(), BOOK_TITLE_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[i].getISBN(), ISBN_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[i].getAuthor(), AUTHOR_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[i].getPub(), PUBLISHER_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[i].getDateAdded(), DATE_ADDED_MAX_LENGTH);
		cout << setw(10) << left << bookInfoInventory[i].getQty();
		cout << showpoint << left << fixed << setprecision(2) << setw(12) << bookInfoInventory[i].getRetail();
		cout << showpoint << left << fixed << setprecision(2) << setw(12) << bookInfoInventory[i].getWholesale();
	}

	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continuePress);

}

void repWholesale() {
	char continuePress;
	cout << "Report Module - Listing WholeSale - " << repDate() << endl;
	cout << endl;
	cout << "TITLE--------------------------------------------|ISBN---------|QUANTITY  |WHOLESALE   |" << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			cout << "[Empty]" << endl;
			continue;
		}
		bookInfoLine(bookInfoInventory[i].getTitle(), BOOK_TITLE_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[i].getISBN(), ISBN_MAX_LENGTH);
		cout << setw(10) << left << bookInfoInventory[i].getQty();
		cout << showpoint << left << fixed << setprecision(2) << setw(12) << bookInfoInventory[i].getWholesale();
	}
	
	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continuePress);
}

void repRetail() {
	char continuePress;
	double totalRetail = 0;
	cout << "Report Module - Listing Retail- " << repDate() << endl;
	cout << endl;
	cout << "TITLE--------------------------------------------|ISBN---------|QUANTITY  |RETAIL PRICE  " << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			cout << "[Empty]" << endl;
			continue;
		}
		bookInfoLine(bookInfoInventory[i].getTitle(), BOOK_TITLE_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[i].getISBN(), ISBN_MAX_LENGTH);
		cout << showpoint << left << fixed << setprecision(2) << setw(12) << bookInfoInventory[i].getRetail();
		cout << showpoint << setprecision(2) << fixed << setw(10) << left << bookInfoInventory[i].getQty();
	}

	for (int i = 0; i < SIZE; i++) {
		totalRetail += bookInfoInventory[i].getRetail();
	}
	
	cout << endl;
	cout << showpoint << setprecision(2) << fixed << "The Total Retail value is $" << totalRetail;
	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continuePress);
}

void repQty() {
	int temp_quantity[SIZE] = { 0 };
	int orderOfData[SIZE] = { 0 };
	int availableItems = availableSlots();
	char continuePress;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() != 1) {
			temp_quantity[i] = bookInfoInventory[i].getQty();
		}
		else {
			temp_quantity[i] = -1;
		}
	}

	for (int i = 0; i < SIZE; i++) {
		orderOfData[i] = i;
	}
	selectionSort(temp_quantity, orderOfData, SIZE);

	cout << "Report Module - Listing Qunatity- " << repDate() << endl;
	cout << endl;
	cout << "TITLE--------------------------------------------|ISBN---------|QUANTITY   " << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			cout << "[Empty]" << endl;
			continue;
		}
		bookInfoLine(bookInfoInventory[orderOfData[i]].getTitle(), BOOK_TITLE_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[orderOfData[i]].getISBN(), ISBN_MAX_LENGTH);
		cout << setw(10) << left << bookInfoInventory[orderOfData[i]].getQty() << endl;
	}

	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continuePress);

}

void repCost() {
	double temp_Wholesale[SIZE] = { 0 };
	int orderOfData[SIZE] = { 0 };
	int availableItems = availableSlots();
	char continuePress;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() != 1) {
			temp_Wholesale[i] = bookInfoInventory[i].getWholesale();
		}
		else {
			temp_Wholesale[i] = -1;
		}
		
	}
	for (int i = 0; i < SIZE; i++) {
		orderOfData[i] = i;
	}
	selectionSort(temp_Wholesale, orderOfData, SIZE);

	cout << "Report Module - Listing Wholesale cost sorted- " << repDate() << endl;
	cout << endl;
	cout << "TITLE--------------------------------------------|ISBN---------|WHOLESALE   " << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			cout << "[Empty]" << endl;
			continue;
		}
		bookInfoLine(bookInfoInventory[orderOfData[i]].getTitle(), BOOK_TITLE_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[orderOfData[i]].getISBN(), ISBN_MAX_LENGTH);
		cout << showpoint << setprecision(2) << fixed << setw(10) << left << bookInfoInventory[orderOfData[i]].getWholesale() << endl;
	}


	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continuePress);

}

void repAge() {
	int orderOfData[SIZE] = { 0 };
	string date_intermediary_form[SIZE];
	Date temp_date[SIZE] = { {0,0,0} };
	int availableItems = availableSlots();
	char continuePress;
	

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < DATE_ADDED_MAX_LENGTH; j++) {
			date_intermediary_form[i] += bookInfoInventory[i].getDateAdded()[j];
		}
	}

	for (int i = 0; i < SIZE; i++) {
		orderOfData[i] = i;
	}

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() != 1) {
			temp_date[i].month = stoi(date_intermediary_form[i].substr(0, 2));
			temp_date[i].day = stoi(date_intermediary_form[i].substr(3, 2));
			temp_date[i].year = stoi(date_intermediary_form[i].substr(6, 4));
		}
		else {
			temp_date[i] = { -1,-1,-1 };
		}
	}

	selectionSort(temp_date, orderOfData, SIZE);

	cout << "Report Module - Listing by date sorted- " << repDate() << endl;
	cout << endl;
	cout << "TITLE--------------------------------------------|ISBN---------|DATE ADDED |QUANTITY  " << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			cout << "[Empty]" << endl;
			continue;
		}
		bookInfoLine(bookInfoInventory[orderOfData[i]].getTitle(), BOOK_TITLE_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[orderOfData[i]].getISBN(), ISBN_MAX_LENGTH);
		bookInfoLine(bookInfoInventory[orderOfData[i]].getDateAdded(), DATE_ADDED_MAX_LENGTH);
		cout << setw(10) << left << bookInfoInventory[orderOfData[i]].getQty() << endl;
	}

	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continuePress);
}
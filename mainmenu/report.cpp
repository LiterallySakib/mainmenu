#include <iostream>
#include <iomanip>
#include <string>
#include "bookinfo.h"
#include "report.h"


using namespace std;

extern Inventory file;
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

template <typename T>
void swapC(T& x, T& y) {
	T temp = x;
	x = y;
	y = temp;
}

template <typename T>
void selectionSort(T order_of_sorted_attribute[], int order_of_data[]) {
	int maxIndex = 0;
	T maxValue;
	for (int i = 0; i < SIZE; i++) {

		maxIndex = i;
		maxValue = order_of_sorted_attribute[i];

		for (int j = i; j < SIZE; j++) {
			if (maxValue > order_of_sorted_attribute[j]) {
				maxIndex = j;
				maxValue = order_of_sorted_attribute[j];
			}
		}

		swapC<T>(order_of_sorted_attribute[i], order_of_sorted_attribute[maxIndex]);
		swapC<int>(order_of_data[i], order_of_data[maxIndex]);
	}
}

void repListing() {
	char continue_press;
	cout << "Report Module - Listing - " << repDate() << endl;
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			continue;
		}
		bookInfo(bookInfoInventory[i].getISBN(),
			bookInfoInventory[i].getTitle(),
			bookInfoInventory[i].getAuthor(),
			bookInfoInventory[i].getPub(),
			bookInfoInventory[i].getDateAdded(),
			bookInfoInventory[i].getQty(),
			bookInfoInventory[i].getWholesale(),
			bookInfoInventory[i].getRetail());
	}

	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continue_press);

}

void repWholesale() {
	char continue_press;
	cout << "Report Module - Listing WholeSale - " << repDate() << endl;
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			continue;
		}
		bookInfo(bookInfoInventory[i].getISBN(),
			bookInfoInventory[i].getTitle(),
			bookInfoInventory[i].getAuthor(),
			bookInfoInventory[i].getPub(),
			bookInfoInventory[i].getDateAdded(),
			bookInfoInventory[i].getQty(),
			bookInfoInventory[i].getWholesale(),
			bookInfoInventory[i].getRetail());
	}
	
	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continue_press);
}

void repRetail() {
	char continue_press;
	double total_retail = 0;
	cout << "Report Module - Listing Retail- " << repDate() << endl;
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			continue;
		}
		bookInfo(bookInfoInventory[i].getISBN(),
			bookInfoInventory[i].getTitle(),
			bookInfoInventory[i].getAuthor(),
			bookInfoInventory[i].getPub(),
			bookInfoInventory[i].getDateAdded(),
			bookInfoInventory[i].getQty(),
			bookInfoInventory[i].getWholesale(),
			bookInfoInventory[i].getRetail());

		total_retail += bookInfoInventory[i].getRetail();
	}
	
	cout << endl;
	cout << showpoint << setprecision(2) << fixed << "The Total Retail value is $" << total_retail;
	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continue_press);
}

void repQty() {
	int temp_quantity[SIZE] = { 0 };
	int order_of_data[SIZE] = { 0 };
	char continue_press;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() != 1) {
			temp_quantity[i] = bookInfoInventory[i].getQty();
		}
		else {
			temp_quantity[i] = -1;
		}
	}

	orderInit(order_of_data);
	selectionSort<int>(temp_quantity, order_of_data);

	cout << "Report Module - Listing Qunatity- " << repDate() << endl;
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			continue;
		}
		bookInfo(bookInfoInventory[order_of_data[i]].getISBN(),
			bookInfoInventory[order_of_data[i]].getTitle(),
			bookInfoInventory[order_of_data[i]].getAuthor(),
			bookInfoInventory[order_of_data[i]].getPub(),
			bookInfoInventory[order_of_data[i]].getDateAdded(),
			bookInfoInventory[order_of_data[i]].getQty(),
			bookInfoInventory[order_of_data[i]].getWholesale(),
			bookInfoInventory[order_of_data[i]].getRetail());
	}

	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continue_press);

}

void repCost() {
	double temp_wholesale[SIZE] = { 0 };
	int order_of_data[SIZE] = { 0 };
	char continue_press;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() != 1) {
			temp_wholesale[i] = bookInfoInventory[i].getWholesale();
		}
		else {
			temp_wholesale[i] = -1;
		}
		
	}

	orderInit(order_of_data);
	selectionSort<double>(temp_wholesale, order_of_data);

	cout << "Report Module - Listing Wholesale cost sorted- " << repDate() << endl;
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			continue;
		}
		bookInfo(bookInfoInventory[order_of_data[i]].getISBN(),
			bookInfoInventory[order_of_data[i]].getTitle(),
			bookInfoInventory[order_of_data[i]].getAuthor(),
			bookInfoInventory[order_of_data[i]].getPub(),
			bookInfoInventory[order_of_data[i]].getDateAdded(),
			bookInfoInventory[order_of_data[i]].getQty(),
			bookInfoInventory[order_of_data[i]].getWholesale(),
			bookInfoInventory[order_of_data[i]].getRetail());
	}


	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continue_press);

}

void repAge() {
	int order_of_data[SIZE] = { 0 };
	Date temp_date[SIZE];
	char continue_press;

	for (int i = 0; i < SIZE; i++) {
		temp_date[i] = bookInfoInventory[i].getDateAdded();
	}
	
	orderInit(order_of_data);
	selectionSort<Date>(temp_date, order_of_data);

	cout << "Report Module - Listing by date sorted- " << repDate() << endl;
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		if (bookInfoInventory[i].isEmpty() == 1) {
			continue;
		}
		bookInfo(bookInfoInventory[order_of_data[i]].getISBN(),
			bookInfoInventory[order_of_data[i]].getTitle(),
			bookInfoInventory[order_of_data[i]].getAuthor(),
			bookInfoInventory[order_of_data[i]].getPub(),
			bookInfoInventory[order_of_data[i]].getDateAdded(),
			bookInfoInventory[order_of_data[i]].getQty(),
			bookInfoInventory[order_of_data[i]].getWholesale(),
			bookInfoInventory[order_of_data[i]].getRetail());
	}

	cout << endl;
	cout << "Press any Key to continue... ";
	cin.ignore();
	cin.get(continue_press);
}
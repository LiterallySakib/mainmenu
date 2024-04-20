/*
Sakib Niaz
CMSC 226 32240
Elia Shahbazi
Project 10
*/
#include <iostream>
#include <string>
#include "bookinfo.h"
#include "cashier.h"
#include "invmenu.h"
#include "report.h"
using namespace std;

BookData bookInfoInventory[SIZE];
Inventory file;

int main() {

	//choice declared for capturing user input
	int choice;

	file.glimpse();

	file.sync(bookInfoInventory, SIZE, SYNCE_FILE_TO_RECORD);
	

	//repeats until 4 is entered
	do {
		
		//options are displayed and user is then prompted to choose out of mentioned options
		cout << "Serendipity Booksellers" << endl;
		cout << "       Main Menu       " << endl;
		cout << "1. Cashier Module      " << endl;
		cout << "2. Inventory Database Module" << endl;
		cout << "3. Report Module" << endl;
		cout << "4. Exit" << endl;
		cout << endl;
		cout << "Enter Your Choice: ";
		cin >> choice;

		//if the user inputs a number outside the numbers prsented in the menu
		//then the appropriate error will print
		//and the user is prompted for input again
		//this process will repeat until user inputs valid option
		while (choice > 4 || choice < 1) {
			cout << "Please enter a number in range 1 - 4" << endl;
			cout << "Enter Your Choice: ";
			cin >> choice;
		}
		cout << endl;

		//the appropriate response is given to each possible valid input the use can make
		switch (choice) {
		case 1:
			cashier();
			break;
		case 2:
			invMenu();
			break;
		case 3:
			report();
			break;
		case 4:
			cout << "You selected item 4" << endl;
			break;
		}
		cout << endl;
	} while (choice != 4);
	
	return 0;
}
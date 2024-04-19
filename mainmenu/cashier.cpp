#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "bookinfo.h"
#include "cashier.h"

using namespace std;

extern Inventory file;
extern BookData bookInfoInventory[SIZE];

void cashier() {
	const double SALES_TAX = 0.06;

	//this vector is capture a purchase history of the user for more detailed receipts
	vector<int> reciept_list;
	//this vector is to capture a history of quantity per book 
	vector<int> quantity_per_item;

	//array to capture user's intended item of purchase
	char ISBNQuery[ISBN_MAX_LENGTH];

	//varaibles to capture purchase details
	int bookLocation = -1,
		quantity_of_books,
		temp_qty = 0;

	double
		subtotal_price = 0,
		tax_price = 0,
		total_price = 0;

	//variable to capture whether the user wants to make another consecutive purchases
	char repeatChoice;

	do {
		//reset bookLocation everytime user is prompted 
		bookLocation = -1;

		cout << endl;
		cout << "Serendipity Book Sellers" << endl;
		cout << "    Cashier Module" << endl;
		cout << endl;

		//prompt the user for the ISBN of the book they want to purchase
		cout << "ISBN: ";
		cin.ignore();
		cin.getline(ISBNQuery, ISBN_MAX_LENGTH);

		//search for book listing with same ISBN as entered
		for (int i = 0; i < SIZE; i++) {
			if (strcmp(bookInfoInventory[i].getISBN(), ISBNQuery) == 0) {
				bookLocation = i;
			}
		}

		//if the ISBN is not found then prompt the user to re-enter
		if (bookLocation == -1) {
			cout << "There is no book with ISBN: " << ISBNQuery << endl;
			cout << "Would you like to re-enter? (y/n) ";
			cin >> repeatChoice;

			//if the user confirmed then skip to the next iteration of the loop
			if ((repeatChoice == 'y' || repeatChoice == 'Y')) {
				continue;
			}
			else {
				//if the user does not want to re-enter then end the function
				return;
			}
		}

		//prompt the user for quantity of book that they're purchasing 
		cout << "How much of \'" << bookInfoInventory[bookLocation].getTitle() << "\' would you like? ";
		cin >> quantity_of_books;

		//if the user asks for more books than what is available print the appropriate message and terminate function
		if (bookInfoInventory[bookLocation].getQty() < quantity_of_books) {
			cout << "There is not enough stock to support this order as there are only " << bookInfoInventory[bookLocation].getQty() << " left in stock.";
			return;
		}
		
		//update the amount of that purchased book in current data base by substracting 
		temp_qty = bookInfoInventory[bookLocation].getQty();
		temp_qty -= quantity_of_books;
		bookInfoInventory[bookLocation].setQty(temp_qty);

		//update the accumulator values for receipt printing
		reciept_list.push_back(bookLocation);
		quantity_per_item.push_back(quantity_of_books);
		subtotal_price += quantity_of_books * bookInfoInventory[bookLocation].getRetail();
		tax_price += SALES_TAX * subtotal_price;
		total_price += tax_price + subtotal_price;

		//prompt user to enter a purchase again
		cout << endl << "Would you like to make another transaction? (y/n) ";
		cin >> repeatChoice;

		//if the user confirms then repeat the loop
	} while ((repeatChoice == 'y' || repeatChoice == 'Y'));
	cout << endl;

	//printing the receipt
	cout << "Qty  ISBN\t\tTitle\t\t\tPrice\tTotal" << endl;
	cout << "________________________________________________________________" << endl;

	//repeat a loop that prints the record purchase history
	for (int i = 0; i < reciept_list.size(); i++) {
		cout << setw(3) << left << quantity_per_item[i];
		cout << "  " << bookInfoInventory[reciept_list[i]].getISBN() << "\t";
		cout << bookInfoInventory[reciept_list[i]].getTitle() << " ";
		cout << setw(6) << right << setprecision(2) << fixed << "$" << bookInfoInventory[reciept_list[i]].getRetail() << "\t";
		cout << setw(6) << right << setprecision(2) << fixed << "$" << (bookInfoInventory[reciept_list[i]].getRetail() * quantity_per_item[i])  << endl;
	}

	//once purchase history is made clear, print the full pricing 
	cout << endl;
	cout << endl;
	cout << "\t\tSubTotal\t\t\t" << setprecision(2) << fixed << subtotal_price << endl;
	cout << "\t\tTax     \t\t\t" << setprecision(2) << fixed << tax_price << endl;
	cout << "\t\tTotal   \t\t\t" << setprecision(2) << fixed << total_price << endl;
	cout << endl;
	cout << "Thank You for Shopping at Serendipity!" << endl;

}
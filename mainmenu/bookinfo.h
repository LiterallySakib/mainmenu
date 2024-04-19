#pragma once

using namespace std;

const int SIZE = 20;
const int BOOK_TITLE_MAX_LENGTH = 51;
const int ISBN_MAX_LENGTH = 14;
const int AUTHOR_MAX_LENGTH = 31;
const int PUBLISHER_MAX_LENGTH = 31;
const int DATE_ADDED_MAX_LENGTH = 11;
const int SYNC_RECORD_TO_FILE = 1;
const int SYNCE_FILE_TO_RECORD = -1;

struct Date {
	int month, day, year;
};

class BookData {
private:
	char bookTitle[BOOK_TITLE_MAX_LENGTH],
		isbn[ISBN_MAX_LENGTH],
		author[AUTHOR_MAX_LENGTH],
		publisher[PUBLISHER_MAX_LENGTH],
		dateAdded[DATE_ADDED_MAX_LENGTH];

	int qtyOnHand;

	double wholesale,
		retail;
public:
	BookData() {
		for (int i = 0; i < BOOK_TITLE_MAX_LENGTH; i++) {
			bookTitle[i] = '\0';
		}
		for (int i = 0; i < ISBN_MAX_LENGTH; i++) {
			isbn[i] = '\0';
		}
		for (int i = 0; i < DATE_ADDED_MAX_LENGTH; i++) {
			dateAdded[i] = '\0';
		}
		for (int i = 0; i < AUTHOR_MAX_LENGTH; i++) {
			author[i] = '\0';
		}
		for (int i = 0; i < PUBLISHER_MAX_LENGTH; i++) {
			publisher[i] = '\0';
		}

		qtyOnHand = 0;
		wholesale = 0;
		retail = 0;
	}

	BookData(char title[], char isbni[], char authori[], char date[], char publisheri[], int qty, double wholesail, double price) {
		for (int i = 0; i < BOOK_TITLE_MAX_LENGTH; i++) {
			bookTitle[i] = title[i];
		}
		for (int i = 0; i < ISBN_MAX_LENGTH; i++) {
			isbn[i] = isbni[i];
		}
		for (int i = 0; i < DATE_ADDED_MAX_LENGTH; i++) {
			dateAdded[i] = date[i];
		}
		for (int i = 0; i < AUTHOR_MAX_LENGTH; i++) {
			author[i] = authori[i];
		}
		for (int i = 0; i < PUBLISHER_MAX_LENGTH; i++) {
			publisher[i] = publisheri[i];
		}

		qtyOnHand = qty;
		wholesale = wholesail;
		retail = price;
	}
	void setTitle(char[]);
	void setISBN(char[]);
	void setAuthor(char[]);
	void setPub(char[]);
	void setDateAdded(char[]);
	void setQty(int inputQty);
	void setWholesale(double inputWholesale);
	void setRetail(double inputRetail);
	void removeBook();
	int isEmpty();
	char* getTitle() {
		return bookTitle;
	}
	char * getISBN() {
		return isbn;
	}
	char* getAuthor() {
		return author;
	}
	char* getPub(){
		return publisher;
	}
	char* getDateAdded() {
		return dateAdded;
	}
	double getWholesale() const {
		return wholesale;
	}
	double getRetail() const {
		return retail;
	}
	int getQty() const {
		return qtyOnHand;
	}

	
};

BookData searchFileBook(fstream& file, string fileName, char target[]);
void sync(fstream& file, string fileName, BookData arr[], int size, int choice);
void modifyFile(fstream& file, string fileName, int target, BookData modified);
void addToFileAtEmpty(fstream& file, string fileName, BookData target);
int searchFile(fstream& file, string fileName, char target[]);
void bookInfo(char[], char[], char[], char[], char[], int, double, double);
void strUpper(char*);
string repDate();
int availableSlots();
bool isOlder(Date,Date);
void bookInfoLine(char[], int);
void selectionSort(int[], int [], int);
void selectionSort(double[] , int[], int);
void selectionSort(Date referenceToOrder[], int order[], int availableListings);

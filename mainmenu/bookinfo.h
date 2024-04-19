#pragma once

#include <fstream>
using namespace std;

const int SIZE = 20;
const int BOOK_TITLE_MAX_LENGTH = 51;
const int ISBN_MAX_LENGTH = 14;
const int AUTHOR_MAX_LENGTH = 31;
const int PUBLISHER_MAX_LENGTH = 31;
const int DATE_ADDED_MAX_LENGTH = 11;
const int SYNC_RECORD_TO_FILE = 1;
const int SYNCE_FILE_TO_RECORD = -1;



class Date {
private:
	int month, day, year;
public:
	Date(int month = 0, int day = 0, int year = 0) {
		this->month = month;
		this->day = day;
		this->year = year;
	}
	int getMonth() const {
		return month;
	}
	int getDay() const {
		return day;
	}
	int getYear() const {
		return year;
	}
	void setMonth(int month) {
		this->month = month;
	}
	void setDay(int day) {
		this->day = day;
	}
	void setYear(int year) {
		this->year = year;
	}

	bool operator>(const Date &day2);
	Date& operator=(const Date& day2);

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
	BookData();

	BookData(const char title[], const char isbni[], const char authori[], const char date[], const char publisheri[], int qty, double wholesail, double price);
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

	bool bookMatch(char target[]);
	
};

class Inventory {
private:
	fstream file;
	string file_name;
public:
	Inventory() {
		file_name = "BookData.dat";
	}
	string getFileName() {
		return file_name;
	}
	void setFileName(string file_name) {
		this->file_name = file_name;
	}

	BookData searchFileBook(char target[]);
	void sync(BookData arr[], int size, int choice);
	void modifyFile(int target, BookData modified);
	int searchFile(char target[]);
	void glimpse() {
		file.open(file_name, ios::out);
		file.close();
	}

	~Inventory() {
		file.close();
	}
};

void orderInit(int[]);
void bookInfo(char[], char[], char[], char[], char[], int, double, double);
void strUpper(char*);
string repDate();

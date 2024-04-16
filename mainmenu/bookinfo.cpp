#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "bookinfo.h"
using namespace std;

extern fstream file;
extern string fileName;
extern BookData bookInfoInventory[SIZE];


//function that prints the information of a single book
void bookInfo(char isbn[], char title[], char author[], char publisher[], char date[], int qty, double wholesale, double retail) {
    cout << "Seredipity Booksellers" << endl;
    cout << "   Book Information   " << endl;
    cout << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Date Added: " << date << endl;
    cout << "Quantity-On-Hand: " << qty << endl;
    cout << showpoint << setprecision(2) << fixed << "Wholesale Cost: " << wholesale << endl;
    cout << showpoint << setprecision(2) << fixed << "Retail Price: " << retail << endl;

}

//function that updates the structure array by reading and writing with the file 
void sync(fstream& file, string fileName, BookData arr[], int size, int choice) {
    //open the file
    file.open(fileName, ios::in | ios::out | ios::binary);

    //if the file isn't open then end the function
    if (!file.is_open()) {
        cout << "could not open file" << endl;
        return;
    }

    //based on the choice parameter, read or write to the file
    if (choice == SYNC_RECORD_TO_FILE) {
        file.seekg(0L, ios::beg);
        file.read(reinterpret_cast<char*>(arr), size * sizeof(BookData));
    }
    else {
        file.seekp(0L, ios::beg);
        file.write(reinterpret_cast<char*>(arr), size * sizeof(BookData));
    }

    //close the file
    file.close();
}

//function that searches the file for a certain book and then returns the information of that found book
BookData searchFileBook(fstream& file, string fileName, char target[]) {

    //make an empty book structure
    BookData temp;

    //open the file
    file.open(fileName, ios::in | ios::binary);

    //if the file is unable to be opened terminate program
    if (file.fail()) {
        cout << "Cannot open file";
        exit(0);
    }
    else {
        //else iteration through the file and search for the book
        int i = 0;
        while (!file.eof()) {
            file.seekg(i * sizeof(BookData));
            file.read(reinterpret_cast<char*>(&temp), sizeof(BookData));
            if (strstr(temp.getTitle(), target) != nullptr) {
                //if the book is found then end the loop and return the found book data
                break;
            }
            i++;
        }

    }
    
    //clear fail bit of the file
    file.clear();
    //close the file
    file.close();

    //return the book data
    return temp;
}

//function that searchs for a certain book within the file and returns the location of the book within the file
int searchFile(fstream& file, string fileName, char target[]) {

    //the location is default to init -1 so that errors be fired when no book is found
    int found = -1;

    //temporary book variable to capture the bookData structures in the file for the comparison
    BookData temp;

    //open the file
    file.open(fileName, ios::in | ios::binary);

    //if the file fails to open then terminate the program
    if (file.fail()) {
        cout << "Cannot open file";
        exit(0);
    }
    else {

        //else then iterate and search through the file for the book
        int i = 0;
        while (!file.eof()) {
            file.seekg(i * sizeof(BookData));
            file.read(reinterpret_cast<char*>(&temp), sizeof(BookData));
            if (strstr(temp.getTitle(), target) != nullptr) {
                //if the book is found then the found variable captures the location at the moment and the loop terminates
                found = i;
                break;
            }
            i++;
        }
    }

    //clear file of fail bit
    file.clear();

    //close file
    file.close();

    //return location of book in file
    return found;
}

//function that adds a certain book into the file's data base
void addToFileAtEmpty(fstream& file, string fileName, BookData target) {

    //Dynamically allocated array that captures the file data in array form
    BookData* ptrArr = nullptr;

    //variable that captures the size of the file in bytes
    streampos fileSize;

    //establish what empty book looked like the file
    char empty[] = { '/' };

    //search for empty books in the file
    int index = searchFile(file, fileName, empty);

    //open file
    file.open(fileName, ios::in | ios::out | ios::binary);

    //if the file fails to open, then terminate the function
    if (file.fail()) {
        cout << "Cannot open file" << endl;
        delete[] ptrArr;
        file.clear();
        file.close();
        return;
    }
    //clear fail bit within file
    file.clear();

    //get the file sizr and dynamically allocate a pointer array using that file size
    file.seekg(0L, ios::end);
    fileSize = file.tellg();
    ptrArr = new BookData[fileSize / sizeof(BookData)];


    //read file to array
    file.seekg(0L, ios::beg);
    file.read(reinterpret_cast<char*>(ptrArr), fileSize);

    //if an empty slot is not found then terminate the function 
    if (index == -1) {
        delete[] ptrArr;
        file.close();
        return;
    }
    else {
        //else set the dynamically allocated array at found location to the date of the target
        ptrArr[index] = target;
    }

    //write the array to the program
    file.seekp(0L, ios::beg);
    file.write(reinterpret_cast<char*>(ptrArr), fileSize);

    delete[] ptrArr;
    file.close();
}

//funcion that replaces a certain book listing int the file with a specified new book
void modifyFile(fstream& file, string fileName, int target, BookData modified) {

    //Dynamically allocated array that captures the file data in array form
    BookData* ptrArr = nullptr;

    //variable that captures the size of the file in bytes
    streampos fileSize;

    //open the file
    file.open(fileName, ios::in | ios::out | ios::binary);

    //if the file fails to open terminate the function
    if (file.fail()) {
        cout << "Cannot open file" << endl;
        delete[] ptrArr;
        file.close();
        return;
    }

    //clear file of fail bit
    file.clear();

    //get the size of thr file by moving cursor to the very end of the file
    file.seekg(0, ios::end);
    fileSize = file.tellg();

    //dynamically allocate the appropriate amount of bookData elements needed
    ptrArr = new BookData[fileSize / sizeof(BookData)];

    //read from file to the dynamically allocated array
    file.seekg(0);
    file.read(reinterpret_cast<char*>(ptrArr), fileSize);

    //replace pre-existing bookdata slot with new data 
    ptrArr[target] = modified;

    //overwrite entire array on the the file
    file.seekp(0);
    file.write(reinterpret_cast<char*>(ptrArr), fileSize);

    //closing
    delete[] ptrArr;
    file.close();
}

//function that converts a char array character elements into all CAPs version
void strUpper(char* arr)
{
    //iterate through the char array
    for (int i = 0; i < strlen(arr); i++) {
        //convert each char into the uppercase version
        arr[i] = toupper(arr[i]);
    }

}

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void swap(double& x, double& y) {
    double temp = x;
    x = y;
    y = temp;
}

void swap(Date& x, Date& y) {
    Date temp;;
    temp = x;
    x = y;
    y = temp;
}

//function that translate c++ __DATE__ macro into MM/DD/YYYY
//function that returns the current date without programmer input
string repDate() {

    //capture the original macro as string for processing
    string date_orginal_format = __DATE__;

    //variable to capture new format of macro
    string date_new_format;

    //translate the month from 3 letter abbreviation to MM/
    if (date_orginal_format.substr(0, 3) == "Jan") {
        date_new_format += "01/";
    }
    else if (date_orginal_format.substr(0, 3) == "Feb") {
        date_new_format += "02/";
    }
    else if (date_orginal_format.substr(0, 3) == "Mar") {
        date_new_format += "03/";
    }
    else if (date_orginal_format.substr(0, 3) == "Apr") {
        date_new_format += "04/";
    }
    else if (date_orginal_format.substr(0, 3) == "May") {
        date_new_format += "05/";
    }
    else if (date_orginal_format.substr(0, 3) == "Jun") {
        date_new_format += "06/";
    }
    else if (date_orginal_format.substr(0, 3) == "Jul") {
        date_new_format += "07/";
    }
    else if (date_orginal_format.substr(0, 3) == "Aug") {
        date_new_format += "08/";
    }
    else if (date_orginal_format.substr(0, 3) == "Sep") {
        date_new_format += "09/";
    }
    else if (date_orginal_format.substr(0, 3) == "Oct") {
        date_new_format += "10/";
    }
    else if (date_orginal_format.substr(0, 3) == "Nov") {
        date_new_format += "11/";
    }
    else if (date_orginal_format.substr(0, 3) == "Dec") {
        date_new_format += "11/";
    }

    //translates the date into DD
    if (date_orginal_format.substr(4, 1) == " ") {
        date_new_format += "0";
        date_new_format += (date_orginal_format.substr(5, 1));
    }
    else {
        date_new_format += (date_orginal_format.substr(4, 2));
    }

    //translates year into YYYY
    date_new_format += ("/" + date_orginal_format.substr(7, 4));

    //new format is returned 
    return date_new_format;
}

//function that calculatws the amount of empty space in the inventory
int availableSlots() {
    int availableSlots = 0;
    for (int i = 0; i < SIZE; i++) {
        if (bookInfoInventory[i].isEmpty() == 1) {
            availableSlots++;
        }
    }
    return availableSlots;
}

//function that returns which date is more older thand the other
bool isOlder(Date day1, Date day2) {

    if (day1.year > day2.year) {
        return true;
    }
    else if (day1.year == day2.year && day1.month > day2.month) {
        return true;
    }
    else if (day1.year == day2.year && day1.month == day2.month && day1.day > day2.day) {
        return true;
    }
    else {
        return false;
    }
}

//function that appends spacing to a char array for when they are displayed in report.cpp
void bookInfoLine(char arr[], int length) {

    char *display_arr = nullptr;
    display_arr = new char[length];
    for (int j = 0; j < length; j++) {
        if (arr[j] != '\0') {
            display_arr[j] = arr[j];
        }
        else {
            display_arr[j] = ' ';
        }
    }
    for (int j = 0; j < length; j++) {
        cout << display_arr[j];
    }

    delete[] display_arr;
    display_arr = nullptr;
}

void BookData::setTitle(char str[]) {
    for (int i = 0; i < BOOK_TITLE_MAX_LENGTH; i++) {
       bookTitle[i] = str[i];
    }
}

void BookData::setISBN(char str[]) {
    for (int i = 0; i < ISBN_MAX_LENGTH; i++) {
        isbn[i] = str[i];
    }
}

void BookData::setAuthor(char str[]) {
    for (int i = 0; i < AUTHOR_MAX_LENGTH; i++) {
        author[i] = str[i];
    }
}

void BookData::setPub(char str[]) {
    for (int i = 0; i < PUBLISHER_MAX_LENGTH; i++) {
        publisher[i] = str[i];
    }
}

void BookData::setDateAdded(char str[]) {
    for (int i = 0; i < DATE_ADDED_MAX_LENGTH; i++) {
        dateAdded[i] = str[i];
    }
}

void BookData::setQty(int inputQty) {
    qtyOnHand = inputQty;
}

void BookData::setWholesale(double inputWholesale) {
    wholesale = inputWholesale;
}

void BookData::setRetail(double inputRetail) {
    retail = inputRetail;
}

int BookData::isEmpty() {
    if (bookTitle[0] == '\0' || bookTitle[0] == '/') {
        return 1;
    }
    return 0;
}

void BookData::removeBook() {
    for (int i = 0; i < BOOK_TITLE_MAX_LENGTH; i++) {
        bookTitle[i] = '/';
    }
    for (int i = 0; i < ISBN_MAX_LENGTH; i++) {
        isbn[i] = '/';
    }
    for (int i = 0; i < DATE_ADDED_MAX_LENGTH; i++) {
        dateAdded[i] = '/';
    }
    for (int i = 0; i < AUTHOR_MAX_LENGTH; i++) {
        author[i] = '/';
    }
    for (int i = 0; i < PUBLISHER_MAX_LENGTH; i++) {
        publisher[i] = '/';
    }

    qtyOnHand = 0;
    wholesale = 0;
    retail = 0;
}

void selectionSort(int referenceToOrder[], int order[], int availableListings) {
    int maxIndex = 0,
        maxValue = 0;

    for (int i = 0; i < availableListings; i++) {

        maxIndex = i;
        maxValue = referenceToOrder[i];

        for (int j = i; j < availableListings; j++) {
            if (maxValue < referenceToOrder[j]) {
                maxIndex = j;
                maxValue = referenceToOrder[j];
            }
        }

        swap(referenceToOrder[i], referenceToOrder[maxIndex]);
        swap(order[i], order[maxIndex]);
    }
}

void orderInit(int OrderOfDate[]) {
    char order[SIZE] = {0};
            for (int i = 0; i < SIZE; i++) {
        order[i] = i;
    }
}

void selectionSort(double referenceToOrder[], int order[], int availableListings) {
    int maxIndex = 0;
    double maxValue = 0;

    for (int i = 0; i < availableListings; i++) {

        maxIndex = i;
        maxValue = referenceToOrder[i];

        for (int j = i; j < availableListings; j++) {
            if (maxValue < referenceToOrder[j]) {
                maxIndex = j;
                maxValue = referenceToOrder[j];
            }
        }

        swap(referenceToOrder[i], referenceToOrder[maxIndex]);
        swap(order[i], order[maxIndex]);
    }
}

void selectionSort(Date referenceToOrder[], int order[], int availableListings) {
    int maxIndex = 0;
    Date maxValue;
    for (int i = 0; i < SIZE; i++) {

        maxIndex = i;
        maxValue = referenceToOrder[i];

        for (int j = i; j < SIZE; j++) {
            if (isOlder(maxValue, referenceToOrder[j])) {
                maxIndex = j;
                maxValue.year = referenceToOrder[j].year;
                maxValue.month = referenceToOrder[j].month;
                maxValue.day = referenceToOrder[j].day;
            }
        }

        swap(referenceToOrder[i], referenceToOrder[maxIndex]);
        swap(order[i], order[maxIndex]);
    }
}
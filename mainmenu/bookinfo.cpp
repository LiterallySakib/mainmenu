#include <iostream>
#include <string>
#include <iomanip>
#include "bookinfo.h"
using namespace std;

extern Inventory file;
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
void Inventory::sync(BookData arr[], int size, int choice) {
    //open the file
    file.open(file_name, ios::in | ios::out | ios::binary);

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
BookData Inventory::searchFileBook(char target[]) {

    //make an empty book structure
    BookData temp;

    //open the file
    file.open(file_name, ios::in | ios::binary);

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
int Inventory::searchFile(char target[]) {

    //the location is default to init -1 so that errors be fired when no book is found
    int found = -1;

    //temporary book variable to capture the bookData structures in the file for the comparison
    BookData temp;

    //open the file
    file.open(file_name, ios::in | ios::binary);

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

//funcion that replaces a certain book listing int the file with a specified new book
void Inventory::modifyFile(int target, BookData modified) {

    file.open(file_name, ios::in | ios::out | ios::binary);

    //variable that captures the size of the file in bytes
    streampos file_size;
    file.seekg(0, ios::end);
    file_size = file.tellg();
    BookData* intermediary_array = nullptr;
    intermediary_array = new BookData[file_size / sizeof(BookData)];

    //if the file fails to open terminate the function
    if (!file.is_open()) {
        cout << "Cannot open file" << endl;
        delete[] intermediary_array;
        file.close();
        return;
    }

    file.seekg(0L, ios::beg);
    file.read(reinterpret_cast<char*>(intermediary_array), file_size);

    //replace pre-existing bookdata slot with new data 
    intermediary_array[target] = modified;

    //overwrite entire array on the the file
    file.seekp(0L, ios::beg);
    file.write(reinterpret_cast<char*>(intermediary_array), file_size);

    //closing
    delete[] intermediary_array;
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
    int available_slots = 0;
    for (int i = 0; i < SIZE; i++) {
        if (bookInfoInventory[i].isEmpty() == 1) {
            available_slots++;
        }
    }
    return available_slots;
}

bool Date::operator>(const Date& day2) {
    if (this->year > day2.year) {
        return true;
    }
    else if (this->year == day2.year && this->month > day2.month) {
        return true;
    }
    else if (this->year == day2.year && this->month == day2.month && this->day > day2.day) {
        return true;
    }
    else {
        return false;
    }
}

Date& Date::operator=(const Date& day2) {

    //address validation so self assignment is avoided
    if (this != &day2) {
        this->day = day2.day;
        this->month = day2.month;
        this->year = day2.year;
    }

    return *this;
}

Date& Date::operator=(const char date_in_c_string[]) {
    string date_intermediary_form = date_in_c_string;

    if (date_in_c_string[0] != '\0') {
        this->setMonth(stoi(date_intermediary_form.substr(0, 2)));
        this->setDay(stoi(date_intermediary_form.substr(3, 2)));
        this->setYear(stoi(date_intermediary_form.substr(6, 4)));
    }
    else {
        this->setDay(-1);
        this->setDay(-1);
        this->setDay(-1);
    }
    
    return *this;
}

//default constructor for BookData class
BookData::BookData() {
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

//construcr for all feilds in BookData class
BookData::BookData(const char title[], const char isbni[], const char authori[], const char date[], const char publisheri[], int qty, double wholesail, double price) {
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

//mutator method for bookTitle
void BookData::setTitle(char str[]) {
    for (int i = 0; i < BOOK_TITLE_MAX_LENGTH; i++) {
       bookTitle[i] = str[i];
    }
}

//mutator method for isbn
void BookData::setISBN(char str[]) {
    for (int i = 0; i < ISBN_MAX_LENGTH; i++) {
        isbn[i] = str[i];
    }
}

//mutator method for author
void BookData::setAuthor(char str[]) {
    for (int i = 0; i < AUTHOR_MAX_LENGTH; i++) {
        author[i] = str[i];
    }
}

//mutator method for publisher
void BookData::setPub(char str[]) {
    for (int i = 0; i < PUBLISHER_MAX_LENGTH; i++) {
        publisher[i] = str[i];
    }
}

//mutator method for date added
void BookData::setDateAdded(char str[]) {
    for (int i = 0; i < DATE_ADDED_MAX_LENGTH; i++) {
        dateAdded[i] = str[i];
    }
}

//mutator method for qunaitity
void BookData::setQty(int inputQty) {
    qtyOnHand = inputQty;
}

//mutator method for wholesale
void BookData::setWholesale(double inputWholesale) {
    wholesale = inputWholesale;
}

//mutator method for retail cost
void BookData::setRetail(double inputRetail) {
    retail = inputRetail;
}

//method for assessing if an object is empty
int BookData::isEmpty() {
    if (bookTitle[0] == '\0') {
        return 1;
    }
    return 0;
}

//method for assessing if an booktitle of object is similar to a given text
bool BookData::bookMatch(char target[]) {
    bool isMatch = false;
    if (strstr(bookTitle, target) != nullptr) {
        isMatch = true;
    }
    return isMatch;
}

//mutator method for deleting book
void BookData::removeBook() {
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

void orderInit(int order_of_data[]) {

    for (int i = 0; i < SIZE; i++) {
        order_of_data[i] = i;
    }
}


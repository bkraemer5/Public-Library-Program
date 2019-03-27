//Brittany Kraemer
//CS301 - 03
#include <iostream>
#include <string>
#include "person.cpp"
#include "book.cpp"
#include <vector>
#include <fstream>

using namespace std;

//void bookCheckout(vector<Book *>, vector<Person *>);
//void bookReturn(vector<Book *>, vector<Person *>);
//void viewAvailable(vector<Book *>);
//void viewBookRentals(vector<Book *>, vector<Person *>);
//void viewCardholderRentals(vector<Book *>, vector<Person *>);
//void openNewCardholder(vector<Person *>);

int main() {

  vector<Book *> books;
  vector<Person *> cardholders;

  ifstream bookFile;
  bookFile.open("books.txt");
  int bookNum;
  string intline;
  string bookTitle;
  string bookAuthor;
  string bookCategory;
  string line1;
  while(!bookFile.eof()) {
    bookFile >> bookNum;
    getline(bookFile, intline);
    getline(bookFile, bookTitle);
    getline(bookFile, bookAuthor);
    getline(bookFile, bookCategory);
    getline(bookFile, line1);
    books.emplace_back(new Book(bookNum, bookTitle, bookAuthor, bookCategory));
  }
  bookFile.close();

  ifstream personFile;
  personFile.open("persons.txt");
  int cardNum;
  string cardStatus;
  string cardFirstName;
  string cardLastName;
  string line2;
  while (!personFile.eof()) {
    personFile >> cardNum;
    personFile >> cardStatus;
    personFile >> cardFirstName;
    personFile >> cardLastName;
    getline(personFile, line2);
    cardholders.emplace_back(new Person(cardNum, cardStatus, cardFirstName, cardLastName));
  }
  return 0;
}

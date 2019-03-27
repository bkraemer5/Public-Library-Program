//Brittany Kraemer
//CS301 - 03
#include <iostream>
#include <string>
#include "person.cpp"
#include "book.cpp"
#include <vector>
#include <fstream>

using namespace std;

void bookCheckout(vector<Book *>, vector<Person *>);
void bookReturn(vector<Book *>);
void viewAvailable(vector<Book *>);
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

  bookCheckout(books, cardholders);
  bookReturn(books);
  viewAvailable(books);
  return 0;
}

// allows the user to check out a book by entering in the cardholder's ID and the books ID. 
void bookCheckout(vector<Book *> b, vector<Person *> p) {
  int card, cindex;
  int book, bindex;
  bool cardFound = false; 
  bool bookFound = false;
  bool rental = false;
 
  // searches for person
  cout << "Please enter the card ID: ";
  cin >> card;
  for (int i = 0; i < p.size(); i++) {
    if (p[i]->getID() == card && p[i]->getStatus() != "Inactive") {
      cout << "Cardholder: " << p[i]->fullName() << endl;
      cardFound = true;
      cindex = i;
    }
  }
  if (cardFound == false) {
    cout << "Card ID not found!" << endl;
    return;
  }
  
  // searches for book
  cout << "Please enter the book ID: ";
  cin >> book;
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->getBookID() == book) {
      cout << "Title: " << b[i]->getTitle() << endl;
      bookFound = true;
      bindex = i;
    }
  }
  
  ifstream inRentals;
  inRentals.open("rentals.txt");
  int bookNum;
  string nextline;
  while (!inRentals.eof()) {
    inRentals >> bookNum;
    getline(inRentals, nextline);
    if (b[bindex]->getBookID() == bookNum) {
      rental = true;
    }
  }
  inRentals.close();

  if (bookFound == false) {
    cout << "Book ID not found!" << endl;
    return;
  }
  else if (rental == true) {
    cout << "Book already checked out" << endl;
    return;
  }
  
  ofstream oRentals("rentals.txt", ios::out | ios::app);
  oRentals << b[bindex]->getBookID() << " " << p[cindex]->getID() << endl;
  oRentals.close();

  b[bindex]->setAvailable(false);
  
}

// this function allows the user to return a book by providing its id
void bookReturn(vector<Book *> b) {
  int book, bindex;
  bool bookFound = false;

  // searches for book
  cout << "Please enter the book ID to return: ";
  cin >> book;
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->getBookID() == book) {
      cout << "Title: " << b[i]->getTitle() << endl;
      bookFound = true;
      bindex = i;
    }
  }
  if (bookFound == false) {
    cout << "Book ID not found!" << endl;
    return;
  }

  ifstream inRentals;
  inRentals.open("rentals.txt");
  ofstream outfile;
  outfile.open("outfile.txt");
  string toDelete = to_string(b[bindex]->getBookID());
  string line;
  while(getline(inRentals, line)) {
    if(line.find(toDelete)) {
      outfile << line << endl;
    }
  }
  inRentals.close();
  outfile.close();
  remove("rentals.txt");
  rename("outfile.txt", "rentals.txt");
  b[bindex]->setAvailable(true);
  cout << "Return Completed" << endl;
}

void viewAvailable(vector<Book *> b) {
  bool atLeastOne = false;
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->isAvailable() == true) {
      atLeastOne = true;
      cout << "Book ID: " << b[i]->getBookID() << endl;
      cout << "Title: " << b[i]->getTitle() << endl;
      cout << "Author: " << b[i]->getAuthor() << endl;
      cout << "Category: " << b[i]->getCategory() << endl;
      cout << endl;
    }
  }
  if (atLeastOne == false) {
    cout << "No available books" << endl;
  }
}

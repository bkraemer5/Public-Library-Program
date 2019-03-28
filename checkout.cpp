//Brittany Kraemer
//CS301 - 03
#include <iostream>
#include <string>
#include "person.cpp"
#include "book.cpp"
#include <vector>
#include <fstream>

using namespace std;

void printMenu();
void bookCheckout(vector<Book *>, vector<Person *>);
void bookReturn(vector<Book *>);
void viewAvailable(vector<Book *>);
void viewBookRentals(vector<Book *>, vector<Person *>);
void viewCardholderRentals(vector<Book *>, vector<Person *>);
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
  string line, next;
  while(!bookFile.eof()) {
    bookFile >> bookNum;
    getline(bookFile, intline);
    getline(bookFile, bookTitle);
    getline(bookFile, bookAuthor);
    getline(bookFile, bookCategory);
    getline(bookFile, next);
    books.emplace_back(new Book(bookNum, bookTitle, bookAuthor, bookCategory));
  }
  bookFile.close();

  ifstream personFile;
  personFile.open("persons.txt");
  int cardNum;
  string cardStatus;
  bool act;
  string cardFirstName;
  string cardLastName;
  string line2;
  while (!personFile.eof()) {
    personFile >> cardNum;
    personFile >> cardStatus;
    personFile >> cardFirstName;
    personFile >> cardLastName;
    getline(personFile, line2);
    if (cardStatus == "Active") {
      act = true;
    }
    else {
      act = false;
    }
    cardholders.emplace_back(new Person(cardNum, act, cardFirstName, cardLastName));
  }
  int choice;
  do {
    printMenu();
    cin >> choice;
    switch(choice) {
      case 1:
          bookCheckout(books, cardholders);
          break;
      case 2:
          bookReturn(books);
          break;
      case 3:
          viewAvailable(books);
          break;
      case 4:
          viewBookRentals(books, cardholders);
          break;
      case 5:
          viewCardholderRentals(books, cardholders);
          break;
      case 6:
          break;
      case 7:
          break;
      case 8:
          break;
    }
  } while (choice != 8);
  return 0;
}

void printMenu() {
  cout << "-----------Library Book Rental System-----------" << endl;
  cout << "1. Book checkout" << endl;
  cout << "2. Book return" << endl;
  cout << "3. View all available books" << endl;
  cout << "4. View all outstanding rentals" << endl;
  cout << "5. View outstanding rentals for a cardholder" << endl;
  cout << "6. Open new library card" << endl;
  cout << "7. Close library card" << endl;
  cout << "8. Exit system" << endl;
}

// allows the user to check out a book by entering in the cardholder's ID and the books ID. 
void bookCheckout(vector<Book *> b, vector<Person *> p) {
  int card, cindex;
  int book;
  bool cardFound = false; 
  bool bookFound = false;
  bool rental = false;
 
  // searches for person
  cout << "Please enter the card ID: ";
  cin >> card;
  for (int i = 0; i < p.size(); i++) {
    if (p[i]->getID() == card && p[i]->isActive() == true) {
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
      if (b[i]->getPersonPtr() != nullptr) {
        cout << "Book already checked out" << endl;
        return;
      }
      b[i]->setPersonPtr(p[cindex]);
    }
  }
  if (bookFound == false) {
    cout << "Book ID not found!" << endl;
    return;
  }
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
  b[bindex]->setPersonPtr(nullptr);
  cout << "Return Completed" << endl;
}

// this function returns all available books to check out
void viewAvailable(vector<Book *> b) {
  bool atLeastOne = false;
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->getPersonPtr() == nullptr) {
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

void viewBookRentals(vector<Book *> b, vector<Person *> p) {
  bool bookFound = false;
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->getPersonPtr() != nullptr) {
      cout << "Book ID: " << b[i]->getBookID() << endl;
      cout << "Title: " << b[i]->getTitle() << endl;
      cout << "Author: " << b[i]->getAuthor() << endl;
      cout << "Cardholder: " << b[i]->getPersonPtr()->fullName() << endl;
      cout << "Card ID: " << b[i]->getPersonPtr()->getID() << endl;
      cout << endl;
      bookFound = true;
    }
  }
  if (bookFound == false) {
    cout << "No Outstanding Rentals" << endl;
  }
}

void viewCardholderRentals(vector<Book *> b, vector<Person *> p) {
  int id;
  cout << "Please enter the Card ID: ";
  cin >> id;
  for (int i = 0; i < p.size(); i++) {
    if (p[i]->getID() == id) {
      cout << "Cardholder: " << p[i]->fullName() << endl;
      cout << endl;
    }
  }
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->getPersonPtr() != nullptr) {
      if (b[i]->getPersonPtr()->getID() == id) {
        cout << "Book ID: " << b[i]->getBookID() << endl;
        cout << "Title: " << b[i]->getTitle() << endl;
        cout << "Author: " << b[i]->getAuthor() << endl;
        cout << endl;
      }
    }
  }
}

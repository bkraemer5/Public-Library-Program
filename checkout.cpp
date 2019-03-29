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
void bookCheckout(vector<Book *> &b, vector<Person *> &p);
void bookReturn(vector<Book *> &b);
void viewAvailable(vector<Book *> &b);
void viewBookRentals(vector<Book *> &b);
void viewCardholderRentals(vector<Book *> &b, vector<Person *> &p);
void openNewCardholder(vector<Person *> &p);
void closeLibraryCard(vector<Book *> &b, vector<Person *> &p);

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
  while (personFile >> cardNum) {
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
  personFile.close();

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
          viewBookRentals(books);
          break;
      case 5:
          viewCardholderRentals(books, cardholders);
          break;
      case 6:
          openNewCardholder(cardholders);
          break;
      case 7:
           closeLibraryCard(books, cardholders);
          break;
      case 8:
          ofstream outRentals;
          outRentals.open("rentals.txt");
          for (int i = 0; i < books.size(); i++) {
            if (books[i]->getPersonPtr() != nullptr) {
              outRentals << books[i]->getBookID() << " " << books[i]->getPersonPtr()->getID() << endl;
            }
          }
          outRentals.close();
          ofstream outPersons;
          outPersons.open("persons.txt");
          for (int i = 0; i < cardholders.size(); i++) {
            if (cardholders[i]->isActive() == true) {
              outPersons << cardholders[i]->getID() << " Active " << cardholders[i]->fullName() << endl;
            }
            else {
              outPersons << cardholders[i]->getID() << " Inactive " << cardholders[i]->fullName() << endl;
            }
          }
          outPersons.close();
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
void bookCheckout(vector<Book *> &b, vector<Person *> &p) {
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
void bookReturn(vector<Book *> &b) {
  int book;
  bool bookFound = false;

  // searches for book
  cout << "Please enter the book ID to return: ";
  cin >> book;
  for (int i = 0; i < b.size(); i++) {
    if (b[i]->getBookID() == book) {
      cout << "Title: " << b[i]->getTitle() << endl;
      bookFound = true;
      b[i]->setPersonPtr(nullptr);
      cout << "Return Completed" << endl;
    }
  }
  if (bookFound == false) {
    cout << "Book ID not found!" << endl;
    return;
  }
}

// this function returns all available books to check out
void viewAvailable(vector<Book *> &b) {
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

// this function allows you to view all outstanding book rentals
void viewBookRentals(vector<Book *> &b) {
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

// this function allows you to view rentals for a given cardholder
void viewCardholderRentals(vector<Book *> &b, vector<Person *> &p) {
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

// this function creates a new card by taking in the first and last name and generating an ID
void openNewCardholder(vector<Person *> &p) {
  string fname, lname;
  bool existing = false;
  int newid;
  cout << "Please enter the first name: ";
  cin >> fname;
  cout << "Please enter the last name: ";
  cin >> lname;
  string full = fname + " " + lname;
  for (int i = 0; i < p.size(); i++) {
    if (full == p[i]->fullName()) {
      p[i]->setActive(true);
      cout << "Card ID " << p[i]->getID() << " active" << endl;
      cout << "Cardholder: " << p[i]->fullName() << endl;
      existing = true;
    }
  } 
  if (existing == false) {
    newid = p[p.size()-1]->getID()+1;
    p.emplace_back(new Person(newid, true, fname, lname));
    cout << "Card ID " <<  p[p.size()-1]->getID() << " active" << endl;
    cout << "Cardholder: " << p[p.size()-1]->fullName() << endl;
  }
}

// this function closes the library card of a user by setting it as inactive and returns all rentals
void closeLibraryCard(vector<Book *> &b, vector<Person *> &p) {
  int id;
  char answer;
  bool found = false;
  cout << "Please enter the card ID: ";
  cin >> id;
  for (int i = 0; i < p.size(); i++) {
    if (id == p[i]->getID()) {
      cout << "Cardholder: " << p[i]->fullName() << endl;
      if (p[i]->isActive() == false) {
        cout << "Card ID is already inactive" << endl;
        return;
      }
      cout << "Are you sure you want to deactivate card? (y/n) ";
      cin >> answer;
      answer = tolower(answer);
      if (answer == 'y') {
        // returns all books the user has
        for (int j = 0; j < b.size(); j++) {
          if(b[j]->getPersonPtr() == p[i]) {
            b[j]->setPersonPtr(nullptr);
          }
        }
        p[i]->setActive(false);
        cout << "Card ID deactivated" << endl;
      }
      else {
        return;
      }
    }
  }
}

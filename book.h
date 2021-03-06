#ifndef BOOK_H
#define BOOK_H
#include <string>

using namespace std;
class Book {

  private:
    int bookID;
    string title;
    string author;
    string category;
    Person *personPtr = nullptr;
  public:
    Book();
    Book(int id, string t, string a, string c);
    int getBookID();
    string getTitle();
    string getAuthor();
    string getCategory();
    void setPersonPtr(Person * ptr);
    Person* getPersonPtr();

};

#endif

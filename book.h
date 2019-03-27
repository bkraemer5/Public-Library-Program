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
    bool available;
  public:
    Book();
    Book(int id, string t, string a, string c);
    int getBookID();
    string getTitle();
    string getAuthor();
    string getCategory();
    void setAvailable(bool a);
    bool isAvailable();

};

#endif

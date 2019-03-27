#ifndef BOOK_H
#define BOOK_H
#include <string>
class Book {

  private:
    int bookID;
    string title;
    string author;
    string category;
  public:
    Book();
    Book(int, string, string, string);

};

#endif

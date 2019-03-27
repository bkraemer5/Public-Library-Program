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
  public:
    Book();
    Book(int id, string t, string a, string c);

};

#endif

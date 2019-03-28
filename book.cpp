#include "book.h"
#include <string>

Book :: Book() {
  bookID = 0;
  title = "";
  author = "";
  category = "";
}

Book :: Book(int id, string t, string a, string c) {
  bookID = id;
  title = t;
  author = a;
  category = c;
}

int Book :: getBookID() {
  return bookID;
}

string Book :: getTitle() {
  return title;
}

string Book :: getAuthor() {
  return author;
}

string Book :: getCategory() {
  return category;
}

void Book :: setPersonPtr(Person * ptr) {
  personPtr = ptr;
}

Person* Book :: getPersonPtr() {
  return personPtr;
}

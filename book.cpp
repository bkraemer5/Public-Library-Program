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
  available = true;
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

void Book :: setAvailable(bool a) {
  available = a;
} 

bool Book :: isAvailable() {
  return available;
}

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

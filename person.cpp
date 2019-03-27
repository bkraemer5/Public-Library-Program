#include "person.h"
#include <string>

Person :: Person() {
  id = 0;
  status = "Inactive";
  firstName = "";
  lastName = "";
}

Person :: Person(int i, string s, string fname, string lname) {
  id = i;
  status = s;
  firstName = fname;
  lastName = lname;
}

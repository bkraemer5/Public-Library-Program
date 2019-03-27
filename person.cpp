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

string Person :: fullName() {
  string full = firstName + " " + lastName;
  return full;
}

int Person :: getID() {
  return id;
}

string Person :: getStatus() {
  return status;
}

string Person :: getFirstName() {
  return firstName;
}

string Person :: getLastName() {
  return lastName;
}

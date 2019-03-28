#include "person.h"
#include <string>

Person :: Person() {
  cardID = 0;
  active = false;
  firstName = "";
  lastName = "";
}

Person :: Person(int id, bool act, string fname, string lname) {
  cardID = id;
  active = act;
  firstName = fname;
  lastName = lname;
}

string Person :: fullName() {
  string full = firstName + " " + lastName;
  return full;
}

int Person :: getID() {
  return cardID;
}

bool Person :: isActive() {
  return active;
}

void Person :: setActive(bool a) {
  active = a;
}

string Person :: getFirstName() {
  return firstName;
}

string Person :: getLastName() {
  return lastName;
}

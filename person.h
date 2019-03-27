#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;
class Person {

  private:
    int id;
    string status;
    string firstName;
    string lastName;
  public:
    Person();
    Person(int i, string s, string fname, string lname);
    string fullName();
    int getID();
    string getStatus();
    string getFirstName();
    string getLastName();

};

#endif

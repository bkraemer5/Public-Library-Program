#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;
class Person {

  private:
    int cardID;
    bool active;
    string firstName;
    string lastName;
  public:
    Person();
    Person(int id, bool act, string fname, string lname);
    string fullName();
    int getID();
    void setActive(bool a);
    bool isActive();
    string getFirstName();
    string getLastName();

};

#endif

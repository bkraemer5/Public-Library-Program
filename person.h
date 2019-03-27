#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person {

  private:
    int id;
    string status;
    string firstName;
    string lastName;
  public:
    Person();
    Person(int, string, string, string);

};

#endif

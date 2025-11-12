#ifndef CHILD_H
#define CHILD_H

#include <string>
#include <iostream>

class Child {
public:
    // Constructors
    Child();
    Child(const std::string& first, const std::string& last, int age);

    // Copy constructor
    Child(const Child& other);

    // operator overload

    // assignment
    Child& operator=(const Child& other);

    // Comparison operators (compare by last name, then first name, then age)
    bool operator<(const Child& other) const;
    bool operator>(const Child& other) const;
    bool operator<=(const Child& other) const;
    bool operator>=(const Child& other) const;
    bool operator==(const Child& other) const;
    bool operator!=(const Child& other) const;

    // operator overload
    friend std::ostream& operator<<(std::ostream& os, const Child& child);
    friend std::istream& operator>>(std::istream& is, Child& child);

    // getters
    std::string getFirstName() const;
    std::string getLastName() const;
    int getAge() const;

private:
    std::string firstName;
    std::string lastName;
    int age;
};

#endif //CHILD_H

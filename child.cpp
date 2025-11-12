#include "child.h"

// Default constructor
Child::Child() : firstName(""), lastName(""), age(0) {}

// Parameterized constructor
Child::Child(const std::string& first, const std::string& last, int age)
    : firstName(first), lastName(last), age(age) {}

// Copy constructor
Child::Child(const Child& other)
    : firstName(other.firstName), lastName(other.lastName), age(other.age) {}

// Assignment operator
Child& Child::operator=(const Child& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        age = other.age;
    }
    return *this;
}

// Comparison operators
// Compare by last name first, then first name, then age
bool Child::operator<(const Child& other) const {
    if (lastName != other.lastName) {
        return lastName < other.lastName;
    }
    if (firstName != other.firstName) {
        return firstName < other.firstName;
    }
    return age < other.age;
}

bool Child::operator>(const Child& other) const {
    return other < *this;
}

bool Child::operator<=(const Child& other) const {
    return !(*this > other);
}

bool Child::operator>=(const Child& other) const {
    return !(*this < other);
}

// Equality operator - all three fields must match
bool Child::operator==(const Child& other) const {
    return firstName == other.firstName &&
           lastName == other.lastName &&
           age == other.age;
}

bool Child::operator!=(const Child& other) const {
    return !(*this == other);
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Child& child) {
    os << child.firstName << child.lastName << child.age;
    return os;
}

// Stream input operator - format: "firstname lastname age"
std::istream& operator>>(std::istream& is, Child& child) {
    is >> child.firstName >> child.lastName >> child.age;
    return is;
}

// Getters
std::string Child::getFirstName() const {
    return firstName;
}

std::string Child::getLastName() const {
    return lastName;
}

int Child::getAge() const {
    return age;
}

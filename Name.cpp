#include "Name.hpp"

using namespace std;

Name::Name() : name(""), lastName("") {

}

Name::Name(const Name& n) : Name() {

    name = n.getName();
    lastName = n.getLastName();
}

void Name::setName(const string& name){

    this->name = name;
}

void Name::setLastName(const string& lastName){

    this->lastName = lastName;
}

string Name::getName() const {

    return name;
}

string Name::getLastName() const {

    return lastName;
}

Name Name::operator = (const Name& n){

    name = n.getName();
    lastName = n.getLastName();

    return *this;
}

bool Name::operator < (const Name& n){

    return name < n.getName();
}

bool Name::operator <= (const Name& n){

    return name <= n.getName();
}

bool Name::operator > (const Name& n){

    return name > n.getName();
}

bool Name::operator >= (const Name& n){

    return name >= n.getName();
}

bool Name::operator != (const Name& n){

    return name != n.getName();
}

bool Name::operator == (const Name& n){

    return name == n.getName();
}

string Name::toString() const {

    string result = name + " " + lastName;

    return result;
}

void Name::initialize() {
    name = "";
    lastName = "";
}

ostream& operator<<(ostream& os, const Name& n) {
	os << n.name << endl;
	os << n.lastName;
	return os;
}

istream& operator>>(istream &is, Name &n) {
	getline(is, n.name);
	getline(is, n.lastName);

	return is;
}


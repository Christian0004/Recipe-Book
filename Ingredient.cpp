#include "Ingredient.hpp"

using namespace std;

Ingredient::Ingredient() : ingredient(""), amount(0), measureUnit("") {

}

Ingredient::Ingredient(const Ingredient& i) : Ingredient(){

    this->ingredient = i.getIngredient();
    this->amount = i.getAmount();
    this->measureUnit = i.getMeasureUnit();
}

void Ingredient::setIngredient(const string& i){

    this->ingredient = i;
}

void Ingredient::setAmount(const float& a){

    this->amount = a;
}

void Ingredient::setMeasureUnit(const string& m){
    this->measureUnit = m;
}

string Ingredient::getIngredient() const {

    return ingredient;
}

float Ingredient::getAmount() const {

    return amount;
}

string Ingredient::getMeasureUnit() const {

    return measureUnit;
}

string Ingredient::toString() const {

    stringstream writtenIngredient;

    writtenIngredient << "Nombre del ingrediente: " << ingredient << ", Cantidad: " << amount << " " << measureUnit << endl;

    return writtenIngredient.str();
}

Ingredient Ingredient::operator = (const Ingredient& i){

    ingredient = i.getIngredient();
    amount = i.getAmount();
    measureUnit = i.getMeasureUnit();

    return *this;
}

bool Ingredient::operator < (const Ingredient& i){

    return ingredient < i.getIngredient();
}

bool Ingredient::operator > (const Ingredient& i){

    return ingredient > i.getIngredient();
}

bool Ingredient::operator <= (const Ingredient& i){

    return ingredient <= i.getIngredient();
}

bool Ingredient::operator >= (const Ingredient& i){

    return ingredient >= i.getIngredient();
}

bool Ingredient::operator != (const Ingredient& i){

    return ingredient != i.getIngredient();
}

int Ingredient::compareByName(const Ingredient& a, const Ingredient& b) {

    int i = 0;

    if(a.getIngredient() == b.getIngredient()){
        i = 0;
    }

    if(a.getIngredient() < b.getIngredient()){
        i = -1;
    }

    if(a.getIngredient() > b.getIngredient()){
        i = 1;
    }

    return i;
}

void Ingredient::initialize() {

    ingredient = "";
    amount = 0;
    measureUnit = "";
}

std::ostream& operator<<(std::ostream& os, const Ingredient& i) {
	os << i.ingredient << endl;
	os << i.amount << endl;
	os << i.measureUnit;
	return os;
}

istream& operator>>(istream& is, Ingredient& i) {
	string myStr;

	getline(is, i.ingredient);
	getline(is, myStr);
	i.amount = atof(myStr.c_str());
	getline(is, i.measureUnit);

	return is;
}

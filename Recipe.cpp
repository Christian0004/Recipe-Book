#include "Recipe.hpp"

using namespace std;

Recipe::Recipe() : ingredientsList(), author(), preparationTime(0), recipeName(""), recipeType(""), procedure("") {

}

Recipe::Recipe(const Recipe& r) : Recipe() {

    ingredientsList = r.getIngredientsList();
    author = r.getAuthor();
    preparationTime = r.getPreparationTime();
    recipeName = r.getRecipeName();
    recipeType = r.getRecipeType();
    procedure = r.getProcedure();
}

void Recipe::setIngredientsList(SLList<Ingredient>& l){

    l.quickSort(Ingredient::compareByName);
    ingredientsList = l;
}

void Recipe::setAuthor(const Name& n){

    author = n;
}

void Recipe::setPreparationTime(const int& p){

    preparationTime = p;
}

void Recipe::setRecipeName(const string& r){

    recipeName = r;
}

void Recipe::setRecipeType(const string& r){

    recipeType = r;
}

void Recipe::setProcedure(const string& p){

    procedure = p;
}

SLList<Ingredient> Recipe::getIngredientsList() const {

    return ingredientsList;
}

Name Recipe::getAuthor() const {

    return author;
}

int Recipe::getPreparationTime() const {

    return preparationTime;
}

string Recipe::getRecipeName() const {

    return recipeName;
}

string Recipe::getRecipeType() const {

    return recipeType;
}

string Recipe::getProcedure() const {

    return procedure;
}

Recipe Recipe::operator = (const Recipe& r) {

    ingredientsList = r.getIngredientsList();
    author = r.getAuthor();
    preparationTime = r.getPreparationTime();
    recipeName = r.getRecipeName();
    recipeType = r.getRecipeType();
    procedure = r.getProcedure();

    return *this;
}

bool Recipe::operator < (const Recipe& r) {

    return recipeName < r.getRecipeName();
}

bool Recipe::operator <= (const Recipe& r) {

    return recipeName <= r.getRecipeName();
}

bool Recipe::operator > (const Recipe& r) {

    return recipeName > r.getRecipeName();
}

bool Recipe::operator >= (const Recipe& r) {

    return recipeName >= r.getRecipeName();
}

bool Recipe::operator != (const Recipe& r) {

    return recipeName != r.getRecipeName();
}

string Recipe::toString() const {

    stringstream writtenRecipe;
    writtenRecipe <<  "----------------------------- " << recipeName << " -----------------------------" << endl;
    writtenRecipe << "Autor: " << author.toString() << endl;
    writtenRecipe << "Tipo de receta: " << recipeType << endl;
    writtenRecipe << "Tiempo de preparacion: " << preparationTime << " minutos" << endl;
    writtenRecipe << "Ingredientes : " << endl;
    writtenRecipe << ingredientsList.toString() << endl;
    writtenRecipe << "Procedimiento: " << procedure << endl;

    return writtenRecipe.str();
}

int Recipe::compByName(const Recipe& a, const Recipe& b) {

    int i(0);

    if(a.getRecipeName() == b.getRecipeName()){
        i = 0;
    }

    if(a.getRecipeName() < b.getRecipeName()){
        i = -1;
    }

    if(a.getRecipeName() > b.getRecipeName()){
        i = 1;
    }

    return i;
}

int Recipe::compByType(const Recipe& a, const Recipe& b) {

    int i(0);

    if(a.getRecipeType() == b.getRecipeType()){
        i = 0;
    }

    if(a.getRecipeType() < b.getRecipeType()){
        i = -1;
    }

    if(a.getRecipeType() > b.getRecipeType()){
        i = 1;
    }

    return i;
}

int Recipe::compByPreparationTime(const Recipe& a, const Recipe& b) {

    int i(0);

    if(a.getPreparationTime() == b.getPreparationTime()){
        i = 0;
    }

    if(a.getPreparationTime() < b.getPreparationTime()){
        i = -1;
    }

    if(a.getPreparationTime() > b.getPreparationTime()){
        i = 1;
    }

    return i;
}

void Recipe::initialize() {

    ingredientsList.initialize();
    author.initialize();
    preparationTime = 0;
    recipeName = "";
    recipeType = "";
    procedure = "";
}

ostream& operator<<(ostream &os, const Recipe &r) {
	os << r.recipeName << endl;
	os << r.author << endl;
	os << r.recipeType << endl;
	os << r.preparationTime << endl;

	int i(0);
    SLList<Ingredient>::Position pos = r.ingredientsList.getFirstPos();
	while (pos != nullptr) {
		i++;
		pos = r.ingredientsList.getNextPos(pos);
	}
	os << i << endl;

    pos = r.ingredientsList.getFirstPos();
	while (pos != nullptr) {
		os << r.ingredientsList.retrieve(pos) << endl;
		pos = r.ingredientsList.getNextPos(pos);
	}

	os << r.procedure;

	return os;
}

istream& operator>>(istream &is, Recipe &r) {
	string myStr;

	getline(is, r.recipeName);
	is >> r.author;
	getline(is, r.recipeType);
	getline(is, myStr);
	r.preparationTime = atoi(myStr.c_str());

	getline(is, myStr);
    int numIngredients = atoi(myStr.c_str());

	SLList<Ingredient> tempIngList;
	Ingredient tempIngredient;

	for (int i = 0; i < numIngredients; i++) {
		is >> tempIngredient;
		tempIngList.insertData(nullptr, tempIngredient);
	}
	r.setIngredientsList(tempIngList);

	getline(is, r.procedure);

	return is;
}

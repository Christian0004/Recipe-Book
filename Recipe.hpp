#ifndef RECIPE_HPP
#define RECIPE_HPP


#include <iostream>
#include <sstream>

#include "SLList.hpp"
#include "Ingredient.hpp"
#include "Name.hpp"


class Recipe {

    private:

        SLList<Ingredient> ingredientsList;
        Name author;
        int preparationTime;
        std::string recipeName;
        std::string recipeType;
        std::string procedure;


    public:

        Recipe();
        Recipe(const Recipe&);

        void setIngredientsList(SLList<Ingredient>&);
        void setAuthor(const Name&);
        void setPreparationTime(const int&);
        void setRecipeName(const std::string&);
        void setRecipeType(const std::string&);
        void setProcedure(const std::string&);

        SLList<Ingredient> getIngredientsList() const;
        Name getAuthor() const;
        int getPreparationTime() const;
        std::string getRecipeName() const;
        std::string getRecipeType() const;
        std::string getProcedure() const;

        Recipe operator = (const Recipe&);
        bool operator < (const Recipe&);
        bool operator > (const Recipe&);
        bool operator <= (const Recipe&);
        bool operator >= (const Recipe&);
        bool operator != (const Recipe&);

        std::string toString() const;

        static int compByName(const Recipe&, const Recipe&);
        static int compByType(const Recipe&, const Recipe&);
        static int compByPreparationTime(const Recipe&, const Recipe&);

        void initialize();

        friend std::ostream& operator<<(std::ostream&, const Recipe&);
        friend std::istream& operator>>(std::istream&, Recipe&);
};

#endif // RECIPE_HPP

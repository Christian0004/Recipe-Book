#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <iostream>
#include <sstream>

class Ingredient {

    public:

        Ingredient();
        Ingredient(const Ingredient&);

        void setIngredient(const std::string&);
        void setAmount(const float&);
        void setMeasureUnit(const std::string&);

        std::string getIngredient() const;
        float getAmount() const;
        std::string getMeasureUnit() const;

        std::string toString() const;

        Ingredient operator = (const Ingredient&);
        bool operator < (const Ingredient&);
        bool operator > (const Ingredient&);
        bool operator <= (const Ingredient&);
        bool operator >= (const Ingredient&);
        bool operator != (const Ingredient&);

        static int compareByName(const Ingredient&, const Ingredient&);

        void initialize();

        friend std::ostream& operator<<(std::ostream&, const Ingredient&);
        friend std::istream& operator>>(std::istream&, Ingredient&);

    private:

        std::string ingredient;
        float amount;
        std::string measureUnit;
};

#endif // INGREDIENT_HPP

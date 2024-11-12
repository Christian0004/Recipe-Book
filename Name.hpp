#ifndef NAME_HPP
#define NAME_HPP

#include <iostream>

class Name {

    private:

        std::string name;
        std::string lastName;

    public:

        Name();
        Name(const Name&);

        void setName(const std::string&);
        void setLastName(const std::string&);

        std::string getName() const;
        std::string getLastName() const;

        Name operator = (const Name&);
        bool operator < (const Name&);
        bool operator > (const Name&);
        bool operator <= (const Name&);
        bool operator >= (const Name&);
        bool operator != (const Name&);
        bool operator == (const Name&);

        std::string toString() const;

        void initialize();

        friend std::ostream& operator<<(std::ostream&, const Name&);
        friend std::istream& operator>>(std::istream&, Name&);

};
#endif // NAME_HPP

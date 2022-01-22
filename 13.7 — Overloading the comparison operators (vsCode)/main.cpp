#include <iostream>
#include <string>

class Car
{
private:
    std::string m_company{};
    std::string m_model{};

public:
    Car(const std::string& company, const std::string& model)
        : m_company{ company }, m_model{ model }
    {

    }

    friend bool operator== (const Car& c1, const Car& c2);
    friend bool operator!= (const Car& c1, const Car& c2);

};

bool operator== (const Car& c1, const Car& c2)
{
    return (c1.m_company == c2.m_company &&
            c1.m_model == c2.m_model); 
}

bool operator!= (const Car& c1, const Car& c2)
{
    return (c1.m_company != c2.m_company ||
            c1.m_model != c2.m_model);
}
int main()
{
    /*
    In lesson 5.6 -- Relational operators and floating point comparisons, we discussed the six comparison operators. 
    Overloading these comparison operators is comparatively simple (see what I did there?), as they follow the same patterns 
    as we’ve seen in overloading other operators.

    Because the comparison operators are all binary operators that do not modify their left operands, we will make our 
    overloaded comparison operators friend functions.

    Here’s an example Car class with an overloaded operator== and operator!=.
    */
    Car corolla{ "Toyota", "Corolla" };
    Car camry{ "Toyota", "Camry" };
    
    if(corolla == camry)
        std::cout << "a Corolla and Camry are the same.\n";
    
    if(corolla != camry)
        std::cout << "a Corolla and Camry are not the same.\n";

    /*
    The code here should be straightforward.

    What about operator< and operator>? What would it mean for a Car to be greater or less than another Car? We typically 
    don’t think about cars this way. Since the results of operator< and operator> would not be immediately intuitive, it 
    may be better to leave these operators undefined.

    Best practice

    Only define overloaded operators that make intuitive sense for your class.

    However, there is one common exception to the above recommendation. What if we wanted to sort a list of Cars? In such a 
    case, we might want to overload the comparison operators to return the member (or members) you’re most likely to want to 
    sort on. For example, an overloaded operator< for Cars might sort based on make and model alphabetically.

    Some of the container classes in the standard library (classes that hold sets of other classes) require an overloaded 
    operator< so they can keep the elements sorted.

    Here’s a different example overloading all 6 logical comparison operators:
    */



    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "-" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    */

    return 0;
}
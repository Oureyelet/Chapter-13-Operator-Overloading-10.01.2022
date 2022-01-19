#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents)
        : m_cents{ cents }
    {
    }

    // Overload Cents + int
    friend Cents operator+(const Cents& cents, int value);

    int getCents() const { return m_cents; }
};

// note: this function is not a member function!
Cents operator+(const Cents& cents, int value)
{
    return Cents(cents.m_cents + value);
}

int main()
{
    /*
    In lesson 13.2 -- Overloading the arithmetic operators using friend functions, you learned how to overload the 
    arithmetic operators using friend functions. You also learned you can overload operators as normal functions. 
    Many operators can be overloaded in a different way: as a member function.

    Overloading operators using a member function is very similar to overloading operators using a friend function. 
    When overloading an operator using a member function:

        The overloaded operator must be added as a member function of the left operand.
        The left operand becomes the implicit *this object
        All other operands become function parameters.

    As a reminder, here’s how we overloaded operator+ using a friend function:
    */
    Cents cents1 { 6 };
    Cents cents2 { cents1 + 7 };

    std::cout << "I have " << cents2.getCents() << " cents." << '\n';

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading operator>>" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    */

    return 0;
}
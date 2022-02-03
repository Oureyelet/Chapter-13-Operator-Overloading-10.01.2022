#include <iostream>
#include <cassert>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};
public:

    //Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        assert( denominator != 0 );
    }

    // Copy constructor
    Fraction(const Fraction& copy)
        : m_numerator{ copy.m_numerator }, m_denominator{ copy.m_denominator }
    {
        // no need to check for a denominator of 0 here since copy must already be a valid Fraction
        std::cout << "Copy constructor called\n";// just to prove it works
    }

    // Overloaded assignment
    Fraction& operator= (const Fraction& fraction);

    friend std::ostream& operator<< (std::ostream& out, const Fraction& f);
};

// A simplistic implementation of operator= (see better implementation below)
Fraction& Fraction::operator= (const Fraction& fraction)
{
    // do the copy
    m_numerator = fraction.m_numerator;
    m_denominator = fraction.m_denominator;

    // return the existing object so we can chain this operator
    return *this;
}


std::ostream& operator<< (std::ostream& out, const Fraction& f)
{
    out << f.m_numerator << '/' << f.m_denominator;
}



int main()
{
    /*
    The assignment operator (operator=) is used to copy values from one object to another already existing object.
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Assignment vs Copy constructor" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    The purpose of the copy constructor and the assignment operator are almost equivalent -- both copy one object to another. 
    However, the copy constructor initializes new objects, whereas the assignment operator replaces the contents of existing 
    objects.

    The difference between the copy constructor and the assignment operator causes a lot of confusion for new programmers, but 
    it’s really not all that difficult. Summarizing:

    If a new object has to be created before the copying can occur, the copy constructor is used (note: this includes passing or 
    returning objects by value).
    If a new object does not have to be created before the copying can occur, the assignment operator is used.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading the assignment operator" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*

    */

    return 0;
}
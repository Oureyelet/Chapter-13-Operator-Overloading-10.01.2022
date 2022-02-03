#include <iostream>
#include <cassert>

class Fraction
{
private:
    int m_numerator{};
    int m_denominator{};

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        assert(denominator != 0);
    }

    // Copy constructor
    Fraction(const Fraction& copy)
        : m_numerator{ copy.m_numerator }, m_denominator{ copy.m_denominator }
    {
        // no need to check for a denominator of 0 here since copy must already be a valid Fraction
        std::cout << "Copy constructor called\n";// just to prove it works
    }

    int getNumerator() { return m_numerator;;  }
    void setNumerator(int numerator) { m_numerator = numerator; }


    friend std::ostream& operator<< (std::ostream& out, const Fraction& f1);
};

std::ostream& operator<< (std::ostream& out, const Fraction& f1)
{
    out << f1.m_numerator << '/' << f1.m_denominator;
    return out;
}

Fraction makeNavigation(Fraction f)
{
    f.setNumerator( -f.getNumerator() );

    return f;
}

int main()
{
    /*
    Consider the following line of code:
    */
    int x = 5;

    /*
    This statement uses copy initialization to initialize newly created integer variable x to the value of 5.

    However, classes are a little more complicated, since they use constructors for initialization. This lesson will examine 
    topics related to copy initialization for classes.
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Copy initialization for classes" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Given our Fraction class:
    */
    Fraction six = Fraction(6);
    std::cout << six << '\n';

    /*
    If you were to compile and run this, you’d see that it produces the expected output:

    6/1

    This form of copy initialization is evaluated the same way as the following:

    Fraction six(Fraction(6));

    And as you learned in the previous lesson, this can potentially make calls to both Fraction(int, int) and the Fraction copy 
    constructor (which may be elided for performance reasons). However, because eliding isn’t guaranteed (prior to C++17, where 
    elision in this particular case is now mandatory), it’s better to avoid copy initialization for classes, and use uniform 
    initialization instead.

    Best practice

    Avoid using copy initialization, and use uniform initialization instead.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Other places copy initialization is used" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    There are a few other places copy initialization is used, but two of them are worth mentioning explicitly. 
    When you pass or return a class by value, that process uses copy initialization.

    Consider:
    */
    Fraction eightSeventh{ 8, 7 };
    std::cout << makeNavigation( eightSeventh ) << '\n';

    /*
    The first copy constructor call happens when fiveThirds is passed as an argument into makeNegative() parameter f. The second 
    call happens when the return value from makeNegative() is passed back to main().

    In the above case, both the argument passed by value and the return value can not be elided. However, in other cases, if 
    the argument or return value meet specific criteria, the compiler may opt to elide the copy constructor. For example:
    */
    // see more on  https://www.learncpp.com/cpp-tutorial/copy-initialization/

    return 0;
}
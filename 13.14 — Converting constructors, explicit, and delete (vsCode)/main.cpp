#include <iostream>
#include <cassert>
#include <string>

class Fraction
{
private:
    int m_numearator{};
    int m_denominator{};

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numearator{ numerator }, m_denominator{ denominator }
    {
        assert( denominator != 0 );
    }

    // Copy constructor
    Fraction(const Fraction& copy)
        : m_numearator{ copy.m_numearator }, m_denominator{ copy.m_denominator }
    {
        // no need to check for a denominator of 0 here since copy must already be a valid Fraction
        std::cout << "Copy constructor called\n";// just to prove it works
    }

    friend std::ostream& operator<< (std::ostream& out, const Fraction& f);

    int getNumeator() { return m_numearator; }
    void setNumerator(int numerator) { m_numearator = numerator; }

};

void printFraction(Fraction f)
{
    std::cout << f << '\n';
}

std::ostream& operator<< (std::ostream& out, const Fraction& f)
{
    out << f.m_numearator << '/' << f.m_denominator;

    return out;
}

class MyString
{
private:
    std::string m_string{};

public:
    MyString(int x)
    {
        m_string.resize(x);
    }

    MyString(const char* string)
    {
        m_string = string;
    }

    friend std::ostream& operator<< (std::ostream& out, const MyString& s);
};

std::ostream& operator<< (std::ostream& out, const MyString& s)
{
    out << s.m_string;

    return out;
}

void printString(const MyString& s)
{
    std::cout << s;
}

int main()
{
    /*
    By default, C++ will treat any constructor as an implicit conversion operator. Consider the following case:
    */
    printFraction(6);

    /*
    Although function printFraction() is expecting a Fraction, we’ve given it the integer literal 6 instead. Because Fraction 
    has a constructor willing to take a single integer, the compiler will implicitly convert the literal 6 into a Fraction object. 
    It does this by initializing printFraction() parameter f using the Fraction(int, int) constructor.

    Consequently, the above program prints:

    6/1

    This implicit conversion works for all kinds of initialization (direct, uniform, and copy).

    Constructors eligible to be used for implicit conversions are called converting constructors (or conversion constructors).
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "The explicit keyword" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    While doing implicit conversions makes sense in the Fraction case, in other cases, this may be undesirable, or lead to 
    unexpected behaviors:
    */
    MyString mine = 'x'; // Will compile and use MyString(int)
    std::cout << mine << '\n';

    printString('x'); // Will compile and use MyString(int)

    /*
    In the above example, the user is trying to initialize a string with a char. Because chars are part of the integer family, 
    the compiler will use the converting constructor MyString(int) constructor to implicitly convert the char to a MyString. 
    The program will then print this MyString, to unexpected results. Similarly, a call to printString(‘x’) causes an implicit 
    conversion that results in the same issue.

    One way to address this issue is to make constructors (and conversion functions) explicit via the explicit keyword, which is 
    placed in front of the function’s name. Constructors and conversion functions made explicit will not be used for implicit 
    conversions or copy initialization:
    
    // explicit keyword makes this constructor ineligible for implicit conversions
	explicit MyString(int x) // allocate string of size x
	{
		m_string.resize(x);
	}

    The above program will not compile, since MyString(int) was made explicit, and an appropriate converting constructor could 
    not be found to implicitly convert ‘x’ to a MyString.

    However, note that making a constructor explicit only prevents implicit conversions. Explicit conversions (via casting) are 
    still allowed:

    std::cout << static_cast<MyString>(5); // Allowed: explicit cast of 5 to MyString(int)

    Direct or uniform initialization will also still convert parameters to match (uniform initialization will not do narrowing 
    conversions, but it will happily do other types of conversions).

    MyString str{'x'}; // Allowed: initialization parameters may still be implicitly converted to match

    Best practice

    Consider making your constructors and user-defined conversion member functions explicit to prevent implicit conversion 
    errors.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "The delete keyword" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    In our MyString case, we really want to completely disallow ‘x’ from being converted to a MyString (whether implicit or 
    explicit, since the results aren’t going to be intuitive). One way to partially do this is to add a MyString(char) 
    constructor, and make it private:
    */
    // see more on https://www.learncpp.com/cpp-tutorial/converting-constructors-explicit-and-delete/




    return 0;
}
#include <iostream>

class Digit
{
private:
    int m_digit{};

public:
    Digit(int digit)
        : m_digit{ digit }
    {    
    }

    Digit& operator++ ();
    Digit& operator-- ();

    friend std::ostream& operator<< (std::ostream& out, const Digit& digit);
};


Digit& Digit::operator++ ()
{

}

Digit& Digit::operator++ ()
{
    
}

std::ostream& operator<< (std::ostream& out, const Digit& digit)
{
    out << digit.m_digit;

    return out;
}

int main()
{
    /*
    Overloading the increment (++) and decrement (--) operators is pretty straightforward, with one small exception. 
    There are actually two versions of the increment and decrement operators: a prefix increment and decrement 
    (e.g. ++x; --y;) and a postfix increment and decrement (e.g. x++; y--;).

    Because the increment and decrement operators are both unary operators and they modify their operands, they’re best 
    overloaded as member functions. We’ll tackle the prefix versions first because they’re the most straightforward.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading prefix increment and decrement" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*

    */

    return 0;
}
#include <iostream>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cent)
    {
        m_cents = cent;
    }

    // add Cents + Cents using a friend function
    friend Cents operator+(const Cents& c1, const Cents& c2);
    friend Cents operator-(const Cents& c1, const Cents& c2);

    // multiple Cents + Cents using a friend function
    // This function is not considered a member of the class, even though the definition is inside the class
    friend Cents operator*(const Cents& c1, const Cents& c2)
    {
        // use the Cents constructor and operator*(int, int)
		// we can access m_cents directly because this is a friend function
        return (c1.m_cents * c2.m_cents);
    }

    int getCents() const
    {
        return m_cents;
    }
};

// note: this function is not a member function!
Cents operator+(const Cents& c1, const Cents& c2)
{
    // use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
    return Cents(c1.m_cents + c2.m_cents);
}

Cents operator-(const Cents& c1, const Cents& c2)
{
    // use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
    return Cents(c1.m_cents - c2.m_cents);
}

int main()
{
    /*
    Some of the most commonly used operators in C++ are the arithmetic operators -- that is, the plus operator (+), minus 
    operator (-), multiplication operator (*), and division operator (/). Note that all of the arithmetic operators are binary 
    operators -- meaning they take two operands -- one on each side of the operator. All four of these operators are overloaded 
    in the exact same way.

    It turns out that there are three different ways to overload operators: the member function way, the friend function way, 
    and the normal function way. In this lesson, we’ll cover the friend function way (because it’s more intuitive for most 
    binary operators). Next lesson, we’ll discuss the normal function way. Finally, in a later lesson in this chapter, we’ll 
    cover the member function way. And, of course, we’ll also summarize when to use each in more detail.
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading operators using friend functions" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Consider the following trivial class:
    */
    Cents oneCent{77};

    /*
    The following example shows how to overload operator plus (+) in order to add two “Cents” objects together:
    */
    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents centsSum{ cents1 + cents2 };

    std::cout << "I have " << centsSum.getCents() << " cents.\n";

    /*
    Overloading the plus operator (+) is as simple as declaring a function named operator+, giving it two parameters of the 
    type of the operands we want to add, picking an appropriate return type, and then writing the function.

    In the case of our Cents object, implementing our operator+() function is very simple. First, the parameter types: in 
    this version of operator+, we are going to add two Cents objects together, so our function will take two objects of 
    type Cents. Second, the return type: our operator+ is going to return a result of type Cents, so that’s our return type.

    Finally, implementation: to add two Cents objects together, we really need to add the m_cents member from each Cents 
    object. Because our overloaded operator+() function is a friend of the class, we can access the m_cents member of our 
    parameters directly. Also, because m_cents is an integer, and C++ knows how to add integers together using the built-in 
    version of the plus operator that works with integer operands, we can simply use the + operator to do the adding.

    Overloading the subtraction operator (-) is simple as well:
    */
    Cents cents3{ 10 };
    Cents cents4{ 8 };
    Cents centsDifference{ cents1 - cents2 };

    std::cout << "I have " << centsDifference.getCents() << " cents.\n";

    /*
    Overloading the multiplication operator (*) and the division operator (/) is as easy as defining functions for 
    operator* and operator/ respectively.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Friend functions can be defined inside the class" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Even though friend functions are not members of the class, they can still be defined inside the class if desired:
    */
    
    // go see our 'friend Cents operator*'

    /*
    We generally don’t recommend this, as non-trivial function definitions are better kept in a separate .cpp file, outside 
    of the class definition. However, we will use this pattern in future tutorials to keep the examples concise.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading operators for operands of different types" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    
    */



    return 0;
}
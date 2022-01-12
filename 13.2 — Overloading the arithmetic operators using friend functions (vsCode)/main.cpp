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

    // add Cents + int using a friend function
    friend Cents operator+(const Cents& c1, int value);

    // add int + Cents using a friend function
    //friend Cents operator+(int value, const Cents& c1);

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

// note: this function is not a member function!
Cents operator-(const Cents& c1, const Cents& c2)
{
    // use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
    return Cents(c1.m_cents - c2.m_cents);
}

// note: this function is not a member function!
Cents operator+(const Cents& c1, int value)
{
    // use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
    return (c1.m_cents + value);
}
/*

// note: this function is not a member function!
Cents operator+(int value, const Cents& c1)
{
    // use the Cents constructor and operator+(int, int)
	// we can access m_cents directly because this is a friend function
    return (value + c1.m_cents);
}
INFO: We dont need any more overload function then "Cents operator+(const Cents& c1, int value)" that one because is same...
*/

class MinMax
{
private:
    int m_min{}; //The min value seen so far
    int m_max{};// The max value seen so far

public:
    MinMax(int min, int max)
    {
        m_min = min;
        m_max = max;
    }

    int getMin() const { return m_min; }
    int getMax() const { return m_max; }

    friend MinMax operator+(const MinMax& m1, const MinMax& m2);
    friend MinMax operator+(const MinMax& m, int value);
    friend MinMax operator+(int value, const MinMax& m);

};

MinMax operator+(const MinMax& m1, const MinMax& m2)
{
    // Get the minimum value seen in m1 and m2
    int min{ m1.m_min < m2.m_min ? m1.m_min : m2.m_min };

    // Get the maximum value seen in m1 and m2
    int max{ m1.m_max > m2.m_max ? m1.m_max : m2.m_max };

    return { min, max };
}

MinMax operator+(const MinMax& m1, int value)
{
    // Get the minimum value seen in m1 and m2
    int min{ m1.m_min < value ? m1.m_min : value };

    // Get the maximum value seen in m1 and m2
    int max{ m1.m_max > value ? m1.m_max : value };

    return { min, max };
}

MinMax operator+(int value, const MinMax& m)
{
    return { m + value };
}

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int num, int deno=1)
        : m_numerator{ num }, m_denominator{ deno }
    {
    }

    void print()
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }


    // We don't want to pass by value, because copying is slow.
	// We can't and shouldn't pass by non-const reference, because then
	// our functions wouldn't work with r-values.
    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f1, int value);
 
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    int numerator{ f1.m_numerator * f2.m_numerator };
    int denominator{ f1.m_denominator * f2.m_denominator };

    return {numerator, denominator};
}

Fraction operator*(const Fraction& f1, int value)
{
    int numerator{ f1.m_numerator * value };

    return {numerator, f1.m_denominator};
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
    Often it is the case that you want your overloaded operators to work with operands that are different types. For example, 
    if we have Cents(4), we may want to add the integer 6 to this to produce the result Cents(10).

    When C++ evaluates the expression x + y, x becomes the first parameter, and y becomes the second parameter. When x and y 
    have the same type, it does not matter if you add x + y or y + x -- either way, the same version of operator+ gets called. 
    However, when the operands have different types, x + y does not call the same function as y + x.

    For example, Cents(4) + 6 would call operator+(Cents, int), and 6 + Cents(4) would call operator+(int, Cents). Consequently, 
    whenever we overload binary operators for operands of different types, we actually need to write two functions -- one for 
    each case. Here is an example of that:
    */
    Cents centOne{ Cents{ 44 } + 77  };
    Cents centTwo{ 88 + Cents{ 33 } };

    std::cout << "I have " << centOne.getCents() << " cents.\n";
    std::cout << "I have " << centTwo.getCents() << " cents.\n";

    /*
    Note that both overloaded functions have the same implementation -- that’s because they do the same thing, 
    they just take their parameters in a different order.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Another example" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Let’s take a look at another example:
    */
    MinMax m1{ 10, 15 };
    MinMax m2{ 8, 11 };
    MinMax m3{ 3, 12 };

    MinMax mFinal{ m1 + m2 + 5 + 8 + m3 + 16 };

    std::cout << "Results: (" << mFinal.getMin() << ", " << mFinal.getMax() << ").\n";

    /*
    The MinMax class keeps track of the minimum and maximum values that it has seen so far. We have overloaded 
    the + operator 3 times, so that we can add two MinMax objects together, or add integers to MinMax objects.

    This example produces the result:

    Result: (3, 16)

    which you will note is the minimum and maximum values that we added to mFinal.

    Let’s talk a little bit more about how “MinMax mFinal = m1 + m2 + 5 + 8 + m3 + 16” evaluates. Remember that operator+ has 
    higher precedence than operator=, and operator+ evaluates from left to right, so m1 + m2 evaluate first. This becomes a 
    call to operator+(m1, m2), which produces the return value MinMax(8, 15). Then MinMax(8, 15) + 5 evaluates next. 
    This becomes a call to operator+(MinMax(8, 15), 5), which produces return value MinMax(5, 15). Then MinMax(5, 15) + 8 
    evaluates in the same way to produce MinMax(5, 15). Then MinMax(5, 15) + m3 evaluates to produce MinMax(3, 15). And finally, 
    MinMax(3, 15) + 16 evaluates to MinMax(3, 16). This final result is then assigned to mFinal.

    In other words, this expression evaluates as “MinMax mFinal = (((((m1 + m2) + 5) + 8) + m3) + 16)”, with each successive 
    operation returning a MinMax object that becomes the left-hand operand for the following operator.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Implementing operators using other operators" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    In the above example, note that we defined operator+(int, MinMax) by calling operator+(MinMax, int) (which produces the 
    same result). This allows us to reduce the implementation of operator+(int, MinMax) to a single line, making our code easier 
    to maintain by minimizing redundancy and making the function simpler to understand.

    It is often possible to define overloaded operators by calling other overloaded operators. You should do so if and when 
    doing so produces simpler code. In cases where the implementation is trivial (e.g. a single line) it’s often not worth 
    doing this, as the added indirection of an additional function call is more complicated than just implementing the function 
    directly.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Quiz time" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Question #1

    a) Write a class named Fraction that has a integer numerator and denominator member. Write a print() function that prints 
    out the fraction.

    The following code should compile:
    */
    Fraction f1{ 1, 4 };
    f1.print();

    Fraction f2{ 1, 2 };
    f2.print();

    /*
    b) Add overloaded multiplication operators to handle multiplication between a Fraction and integer, and between 
    two Fractions. Use the friend function method.

    Hint: To multiply two fractions, first multiply the two numerators together, and then multiply the two denominators 
    together. To multiply a fraction and an integer, multiply the numerator of the fraction by the integer and leave 
    the denominator alone.

    The following code should compile:
    */
    Fraction f3{ 2, 5 };
    f3.print();

    Fraction f4{ 3, 8 };
    f4.print();

    Fraction f5{ f3 * f4 };
    f5.print();

    Fraction f6{ f3 * 2 };
    f6.print();

    Fraction f7{ 2 * f4 };
    f7.print();

    Fraction f8{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f8.print();

    /*
    c) Why does the program continue to work correctly if we remove the operators for integer multiplication from the 
    previous solution?

    // We can remove these operators, and the program continues to work
    
    Fraction operator*(const Fraction& f1, int value);
    Fraction operator*(int value, const Fraction& f1);
    */


    return 0;
}
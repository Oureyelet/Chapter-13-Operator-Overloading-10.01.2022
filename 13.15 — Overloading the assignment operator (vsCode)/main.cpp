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

    return out;
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
    Overloading the assignment operator (operator=) is fairly straightforward, with one specific caveat that we’ll get to. 
    The assignment operator must be overloaded as a member function.
    */
    Fraction fiveThirds{ 5, 3 };
    Fraction f;
    f = fiveThirds;// calls overloaded assignment
    std::cout << f << '\n';
    
    /*
    This prints:

    5/3

    This should all be pretty straightforward by now. Our overloaded operator= returns *this, so that we can chain multiple 
    assignments together:
    */
    
    Fraction f1{ 5, 3 };
    Fraction f2{ 7, 2 };
    Fraction f3{ 9, 5 };

    f1 = f2 = f3;

    std::cout << f1 << '\n';


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Issues due to self-assignment" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Here’s where things start to get a little more interesting. C++ allows self-assignment:
    */
    Fraction f4{ 5, 3 };
    f4 = f4;// self assignment

    /*
    This will call f1.operator=(f1), and under the simplistic implementation above, all of the members will be assigned to 
    themselves. In this particular example, the self-assignment causes each member to be assigned to itself, which has no 
    overall impact, other than wasting time. In most cases, a self-assignment doesn’t need to do anything at all!

    However, in cases where an assignment operator needs to dynamically assign memory, self-assignment can actually be dangerous:
    */

    // see more on : https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Detecting and handling self-assignment" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Fortunately, we can detect when self-assignment occurs. Here’s an updated implementation of our overloaded 
    operator= for the MyString class:
    */

    //see more on https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "When not to handle self-assignment" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Typically the self-assignment check is skipped for copy constructors. Because the object being copy constructed is newly created, the only case where the newly created object can be equal to the object being copied is when you try to initialize a newly defined object with itself:

    someClass c { c };

    In such cases, your compiler should warn you that ```c``` is an uninitialized variable.

    Second, the self-assignment check may be omitted in classes that can naturally handle self-assignment. 
    Consider this Fraction class assignment operator that has a self-assignment guard:
    
    A better implementation of operator=:

    Fraction& Fraction::operator= (const Fraction& fraction)
    {
        // self-assignment guard
        if (this == &fraction)
            return *this;

        // do the copy
        m_numerator = fraction.m_numerator; // can handle self-assignment
        m_denominator = fraction.m_denominator; // can handle self-assignment

        // return the existing object so we can chain this operator
        return *this;
    }
    
    If the self-assignment guard did not exist, this function would still operate correctly during a self-assignment 
    (because all of the operations done by the function can handle self-assignment properly).

    Because self-assignment is a rare event, some prominent C++ gurus recommend omitting the self-assignment guard even in 
    classes that would benefit from it. We do not recommend this, as we believe it’s a better practice to code defensively 
    and then selectively optimize later.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "The copy and swap idiom" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    see more: https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Default assignment operator" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Unlike other operators, the compiler will provide a default public assignment operator for your class if you do not provide 
    one. This assignment operator does memberwise assignment (which is essentially the same as the memberwise initialization 
    that default copy constructors do).

    Just like other constructors and operators, you can prevent assignments from being made by making your assignment operator 
    private or using the delete keyword:
    
    see more: https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/
    */

    
    
    return 0;
}
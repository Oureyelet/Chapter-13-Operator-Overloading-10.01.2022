#include <iostream>
#include <string>

class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents)
        : m_cents{ cents }
    {

    }

    // Overload -Cents as a member function
    Cents operator-() const;

    Cents operator+() const;

    int getCents() const
    {
        return m_cents;
    }
};

// note: this function is a member function!
Cents Cents::operator-() const
{
    return {-m_cents}; 
    /*
    since return type is a Cents, this does an implicit conversion from 
    int to Cents using the Cents(int) constructor
    */
}

Cents Cents::operator+() const
{
    return {+m_cents}; 
}

int main()
{
    std::cout << "Hello World" << '\n';

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading unary operators" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Unlike the operators you’ve seen so far, the positive (+), negative (-) and logical not (!) operators all are unary 
    operators, which means they only operate on one operand. Because they only operate on the object they are applied to, 
    typically unary operator overloads are implemented as member functions. All three operands are implemented in 
    an identical manner.

    Let’s take a look at how we’d implement operator- on the Cents class we used in a previous example:
    */
    const Cents nickle{ 5 };
    std::cout << "A nickle of debt is worth " << (-nickle).getCents() << " cents.\n";

    /*
    This should be straightforward. Our overloaded negative operator (-) is a unary operator implemented as a member 
    function, so it takes no parameters (it operates on the *this object). It returns a Cents object that is the negation 
    of the original Cents value. Because operator- does not modify the Cents object, we can (and should) make it a const 
    function (so it can be called on const Cents objects).

    Note that there’s no confusion between the negative operator- and the minus operator- since they have a different 
    number of parameters.
    
    Here’s another example. The ! operator is the logical negation operator -- if an expression evaluates to “true”, 
    operator! will return false, and vice-versa. We commonly see this applied to boolean variables to test whether 
    they are true or not:
    */

    std::string answer{};

    while (answer != "happy")
    {
        std::cout << "How are you today?";
    
        std::cin >> answer;
    }

    if(answer != "happy")
        std::cout << ":(" << '\n';
    else
        std::cout << ":)" << '\n';
    


    return 0;
}
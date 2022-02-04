#include <iostream>
#include <cassert>  // for assert()
#include <cstring> // for strlen()

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        assert(denominator != 0);
    }

    // Possible implementation of implicit copy constructor
    Fraction(const Fraction& copy)
        : m_numerator{ copy.m_numerator }, m_denominator{ copy.m_denominator }
    {
        std::cout << "hello here is constructor copy :)";
    }

    // Possible implementation of implicit assignment operator
    Fraction& operator= (const Fraction& fraction)
    {
        // self-assignment guard
        if(this == &fraction)
            return *this;
    
        // do the copy
        m_numerator = fraction.m_numerator;
        m_denominator = fraction.m_denominator;

        // return the existing object so we can chain this operator
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const Fraction& fraction); 
    
};

std::ostream& operator<< (std::ostream& out, const Fraction& fraction)
{
    out << fraction.m_numerator << '/' << fraction.m_denominator;    

    return out;
}

class Mystring
{
private:
    char* m_data{};
    int m_length{};

public:
    Mystring(const char* source = "")
    {
        assert(source);// make sure source isn't a null string

        // Find the length of the string
        // Plus one character for a terminator
        m_length = std::strlen(source)+1;

        // Allocate a buffer equal to this length
        m_data = new char[m_length];

        // Copy the parameter string into our internal buffer
        for(int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    ~Mystring()// destructor
    {
         // We need to deallocate our string
        delete[] m_data;
    }

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};   

int main()
{
    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Shallow copying" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Because C++ does not know much about your class, the default copy constructor and default assignment operators it provides 
    use a copying method known as a memberwise copy (also known as a shallow copy). This means that C++ copies each member of 
    the class individually (using the assignment operator for overloaded operator=, and direct initialization for the copy 
    constructor). When classes are simple (e.g. do not contain any dynamically allocated memory), this works very well.

    For example, let’s take a look at our Fraction class:
    
    see out Fraction class please...

    Note that because these default versions work just fine for copying this class, there’s really no reason to write our own 
    version of these functions in this case.

    However, when designing classes that handle dynamically allocated memory, memberwise (shallow) copying can get us in a lot of 
    ! This is because shallow copies of a pointer just copy the address of the pointer -- it does not allocate any memory or 
    copy the contents being pointed to!

    Let’s take a look at an example of this:
    
    see our Mystring class please...

    The above is a simple string class that allocates memory to hold a string that we pass in. Note that we have not 
    defined a copy constructor or overloaded assignment operator. Consequently, C++ will provide a default copy constructor 
    and default assignment operator that do a shallow copy. The copy constructor will look something like this:

    MyString::MyString(const MyString& source)
        : m_length( source.m_length )
        , m_data( source.m_data )
    {
    }

    Note that m_data is just a shallow pointer copy of source.m_data, meaning they now both point to the same thing.

    Now, consider the following snippet of code:
    */
    Mystring hello{ "Hello world!" };
    



    return 0;
}
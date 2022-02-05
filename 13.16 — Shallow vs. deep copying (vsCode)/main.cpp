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

    void deepCopy(const Mystring& source);

};

// assumes m_data is initialized
void Mystring::deepCopy(const Mystring& source)
{
    // first we need to deallocate any value that this string is holding!
    delete[] m_data;

    // because m_length is not a pointer, we can shallow copy it
    m_length = source.m_length;

    // m_data is a pointer, so we need to deep copy it if it is non-null
    if(source.m_data)
    {
        // allocate memory for our copy
        m_data = new char[m_length];

        // do the copy
        for(int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

// Copy constructor
Mystring::Mystring(const Mystring& source)
{
    deepCopy(source);
}

// Assignment operator
Mystring& Mystring::operator=(const Mystring& source)
{
    // check for self-assignment
    if(this != &source)
    {
        // now do the deep copy
        deepCopy(source);
    }

    return *this;
}

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

    // see more on https://www.learncpp.com/cpp-tutorial/shallow-vs-deep-copying/
    

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Deep copying" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    One answer to this problem is to do a deep copy on any non-null pointers being copied. A deep copy allocates memory for the 
    copy and then copies the actual value, so that the copy lives in distinct memory from the source. This way, the copy and 
    source are distinct and will not affect each other in any way. Doing deep copies requires that we write our own copy 
    constructors and overloaded assignment operators.

    Let’s go ahead and show how this is done for our MyString class:
    */

    // see our  deepCopy void function..

    /*
    As you can see, this is quite a bit more involved than a simple shallow copy! First, we have to check to make sure source 
    even has a string (line 11). If it does, then we allocate enough memory to hold a copy of that string (line 14). Finally, 
    we have to manually copy the string (lines 17 and 18).

    Now let’s do the overloaded assignment operator. The overloaded assignment operator is slightly trickier:
    */

    //see our Mystring& Mystring::operator=(const Mystring& source) above

    /*
    Note that our assignment operator is very similar to our copy constructor, but there are three major differences:

    We added a self-assignment check.
    We return *this so we can chain the assignment operator.
    We need to explicitly deallocate any value that the string is already holding (so we don’t have a memory leak when m_data 
    is reallocated later).

    When the overloaded assignment operator is called, the item being assigned to may already contain a previous value, which 
    we need to make sure we clean up before we assign memory for new values. For non-dynamically allocated variables 
    (which are a fixed size), we don’t have to bother because the new value just overwrite the old one. However, for 
    dynamically allocated variables, we need to explicitly deallocate any old memory before we allocate any new memory. 
    If we don’t, the code will not crash, but we will have a memory leak that will eat away our free memory every time we do 
    an assignment!
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "A better solution" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Classes in the standard library that deal with dynamic memory, such as std::string and std::vector, handle all of their 
    memory management, and have overloaded copy constructors and assignment operators that do proper deep copying. So instead 
    of doing your own memory management, you can just initialize or assign them like normal fundamental variables! That makes 
    these classes simpler to use, less error-prone, and you don’t have to spend time writing your own overloaded functions!
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Summary" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    1.The default copy constructor and default assignment operators do shallow copies, which is fine for classes that contain 
    no dynamically allocated variables.
    
    2.Classes with dynamically allocated variables need to have a copy constructor and assignment operator that do a deep copy.
    
    3.Favor using classes in the standard library over doing your own memory management.
    */

    return 0;
}
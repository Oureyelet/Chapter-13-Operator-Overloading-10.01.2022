#include <iostream>

class Cents
{
private:
    int m_cents{};
public:
    Cents(int cents)
        : m_cents{ cents }
    {

    }

    friend std::ostream& operator<< (std::ostream& out, const Cents& cents)
    {
        out << cents.m_cents;

        return out;
    }

    friend bool operator< (const Cents& c1, const Cents& c2)
    {
        return (c1.m_cents < c2.m_cents);
    }

    Cents operator+= (const Cents &cents)
    {
        m_cents += cents.m_cents;

        return *this;
    }
    
    Cents operator/= (int x)
    {
        m_cents /= x;

        return *this; 
    }
    
};

template <typename T>
const T& max(T x, T y)
{
    return (x < y) ? y : x;
}

template <typename T>
T average(const T* myArray, int numValues)
{
    T sum{ 0 };
    for(int count{ 0 }; count < numValues; ++count)
    {
        sum += myArray[count];
    }

    sum /= numValues;

    return sum;
}

int main()
{

    /*
    In lesson 8.14 -- Function template instantiation, we discussed how the compiler will use function templates to instantiate 
    functions, which are then compiled. We also noted that these functions may not compile, if the code in the function template 
    tries to perform some operation that the actual type doesn’t support (such as adding integer value 1 to a std::string).

    In this lesson, we’ll take a look at a few examples where our instantiated functions won’t compile because our actual class 
    types don’t support those operators, and show how we can define those operators so that the instantiated functions will then 
    compile.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Operators, function calls, and function templates" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    First, let’s create a simple class:

    see our Cents class...
    
    and define a max function template:

    see our new MAX functon above main()...

    Now, let’s see what happens when we try to call max() with object of type Cents:
    */
    Cents nickle{ 5 };
    Cents dime{ 10 };

    Cents bigger = max(nickle, dime);

    std::cout << bigger << " is bigger\n";

    /*
    C++ will create a template instance for max() that looks like this:

    template <>
    const Cents& max(const Cents& x, const Cents& y)
    {
        return (x < y) ? y : x;
    }

    And then it will try to compile this function. See the problem here? C++ has no idea how to evaluate x < y when x and y 
    are of type Cents! Consequently, this will produce a compile error.

    To get around this problem, simply overload operator< for any class we wish to use max with:

    see our new overload function with operator<

    This works as expected, and prints:

    10 is bigger
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Another example" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Let’s do one more example of a function template not working because of missing overloaded operators.

    The following function template will calculate the average of a number of objects in an array:
    */
    int intArray[] { 5, 3, 2, 1, 4 };
    std::cout << average(intArray, 5) << '\n';

    double doubleArray[] { 3.12, 3.45, 9.23, 6.34 };
    std::cout << average(doubleArray, 4) << '\n';

    /*
    This produces the values:

    3
    5.535

    As you can see, it works great for built-in types!

    Now let’s see what happens when we call this function on our Cents class:
    */
    Cents centsArray[] { Cents { 5 }, Cents { 10 }, Cents { 15 }, Cents { 14 } };
    std::cout << average(centsArray, 4) << '\n';

    /*
    If we compile again, we will get another error:

    error C2676: binary += : Cents does not define this operator or a conversion to a type acceptable to the predefined 
    operator

    This error is actually being caused by the function template instance created when we call average(const Cents*, int). 
    Remember that when we call a templated function, the compiler “stencils” out a copy of the function where the template 
    type parameters (the placeholder types) have been replaced with the actual types in the function call. Here is the 
    function template instance for average() when T is a Cents object:

    template <>

    Finally, our code will compile and run! Here is the result:

    11 cents

    Note that we didn’t have to modify average() at all to make it work with objects of type Cents. We simply had to define 
    the operators used to implement average() for the Cents class, and the compiler took care of the rest!
    */

    return 0;
}
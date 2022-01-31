#include <iostream>
#include <cassert> // for assert()
#include <string>

class Matrix
{
private:
    double m_data[4][4]{};

public:
    double& operator()(int row, int col);
    double operator()(int row, int col) const; // for const objects
    void operator()();
};

double& Matrix::operator()(int row, int col)
{
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);

    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);

    return m_data[row][col];
}

void Matrix::operator()()
{
    for(int row{ 0 }; row < 4; ++row)
    {
        for(int col{ 0 }; col < 4; ++col)
        {
            m_data[row][col] = 0.0;
        }
    }
}

class Accumulator
{
private:
    int m_counter{ 0 };

public:
    int operator() (int i) { return (m_counter += i); }

};

class String
{
private:
    std::string m_str{};

public:
    String() = default;

    char& operator()(int index, int length);

};
//               012345678
//               Niedziela
//    3 3           dzi

char& String::operator()(int index, int length)
{                               //8
    for(int i{ index }; i < m_str.length(); ++i)
    {
        std::cout << m_str[i];  
    }
    std::cout << std::endl;
}    

int main()
{
    /*
    All of the overloaded operators you have seen so far let you define the type of the operator’s parameters, but not the 
    number of parameters (which is fixed based on the type of the operator). For example, operator== always takes two parameters, 
    whereas operator! always takes one. The parenthesis operator (operator()) is a particularly interesting operator in that it 
    allows you to vary both the type AND number of parameters it takes.

    There are two things to keep in mind: first, the parenthesis operator must be implemented as a member function. Second, in 
    non-object-oriented C++, the () operator is used to call functions. In the case of classes, operator() is just a normal 
    operator that calls a function (named operator()) like any other overloaded operator.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "An example" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Let’s take a look at an example that lends itself to overloading this operator:
    
    //soo our Matrix class please...

    Matrices are a key component of linear algebra, and are often used to do geometric modeling and 3D computer graphics work. 
    In this case, all you need to recognize is that the Matrix class is a 4 by 4 two-dimensional array of doubles.

    In the lesson on overloading the subscript operator, you learned that we could overload operator[] to provide direct access 
    to a private one-dimensional array. However, in this case, we want access to a private two-dimensional array. Because 
    operator[] is limited to a single parameter, it is not sufficient to let us index a two-dimensional array.

    However, because the () operator can take as many parameters as we want it to have, we can declare a version of operator() 
    that takes two integer index parameters, and use it to access our two-dimensional array. Here is an example of this:
    */

    // see our upgade in Matix class...

    /*
    Now we can declare a Matrix and access its elements like this:
    */
    Matrix matrix{};

    matrix(1, 2) = 4.5;
    std::cout << matrix(1, 2) << '\n';

    /*
    which produces the result:

    4.5

    Now, let’s overload the () operator again, this time in a way that takes no parameters at all:
    */

    // see our new function 'operator()()'

    /*
    And here’s our new example:
    */
    Matrix matrix_two;

    matrix_two(1, 2) = 7.7;
    matrix_two();
    std::cout << matrix_two(1, 2) << '\n';

    /*
    which produces the result:

    0

    Because the () operator is so flexible, it can be tempting to use it for many different purposes. However, this is 
    strongly discouraged, since the () symbol does not really give any indication of what the operator is doing. In our example 
    above, it would be better to have written the erase functionality as a function called clear() or erase(), as matrix.erase() 
    is easier to understand than matrix() (which could do anything!).
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Having fun with functors" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Operator() is also commonly overloaded to implement functors (or function object), which are classes that operate 
    like functions. The advantage of a functor over a normal function is that functors can store data in member variables 
    (since they are classes).

    Here’s a simple functor:
    */
    Accumulator acc{};
    std::cout << acc(10) << '\n'; // print 10
    std::cout << acc(30) << '\n'; // print 40
    
    /*
    Note that using our Accumulator looks just like making a normal function call, but our Accumulator object is storing an 
    accumulated value.

    You may wonder why we couldn’t do the same thing with a normal function and a static local variable to preserve data 
    between function calls. We could, but because functions only have one global instance, we’d be limited to using it for 
    one thing at a time. With functors, we can instantiate as many separate functor objects as we need and use them all 
    simultaneously.
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Conclusion" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Operator() is sometimes overloaded with two parameters to index multidimensional arrays, or to retrieve a subset of a 
    one dimensional array (with the two parameters defining the subset to return). Anything else is probably better written 
    as a member function with a more descriptive name.

    Operator() is also often overloaded to create functors. Although simple functors (such as the example above) are fairly 
    easily understood, functors are typically used in more advanced programming topics, and deserve their own lesson.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Quiz Time" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Question #1

    Write a class that holds a string. Overload operator() to return the substring that starts at the index of the 
    first parameter. The length of the substring should be defined by the second parameter.

    Hint: You can use array indices to access individual chars within the std::string
    Hint: You can use operator+= to append something to a string

    The following code should run:
    */
    String string{ "Hello, world!" };


    return 0;
}
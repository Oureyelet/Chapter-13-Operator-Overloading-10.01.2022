#include <iostream>

class IntList
{
private:
    int m_list[10]{};
    int m_second_list[10]{0, 1, 2, 3, 122, 5, 6, 7, 8, 9}; // give this class some initial state for this example

public:
    IntList() = default;

    void setItem(int index, int value)
    {
        m_list[index] = value;
    }

    int* getList() { return m_list; }
    
    int getValue(int index)
    {
        return m_list[index];
    }
    
    int getValue_second_list(int index) const
    {
        return m_second_list[index];
    }

    int& operator[] (int index);
    const int& operator[] (int index) const;
};

int& IntList::operator[] (int index)// for non-const objects: can be used for assignment
{
    return m_list[index];
}

const int& IntList::operator[] (int index) const// for const objects: can only be used for access
{
    return m_second_list[index];
}

int main()
{
    /*
    When working with arrays, we typically use the subscript operator ([]) to index specific elements of an array:
    */
    int myArray[7];
    myArray[0] = 7; // put the value 7 in the first element of the array

    /*
    However, consider the following IntList class, which has a member variable that is an array:
    */
    IntList list{};
    // how do we access elements from m_list?

    /*
    Because the m_list member variable is private, we can not access it directly from variable list. 
    This means we have no way to directly get or set values in the m_list array. So how do we get or put elements into our list?

    Without operator overloading, the typical method would be to create access functions:
    */
    
    list.setItem(7, 77);
    std::cout << list.getValue(7) << '\n';

    /*
    While this works, it’s not particularly user friendly. Consider the following example:
    */
    IntList list2{};
    list2.setItem(2, 78);

    /*
    Are we setting element 2 to the value 3, or element 3 to the value 2? Without seeing the definition of setItem(), 
    it’s simply not clear.

    You could also just return the entire list and use operator[] to access the element:
    */ 

    //see our getList() function...

    /*
    While this also works, it’s syntactically odd:
    */
    IntList list3{};
    list3.getList()[2] = 6;


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading operator[]" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    However, a better solution in this case is to overload the subscript operator ([]) to allow access to the elements 
    of m_list. The subscript operator is one of the operators that must be overloaded as a member function. An overloaded 
    operator[] function will always take one parameter: the subscript that the user places between the hard braces. 
    In our IntList case, we expect the user to pass in an integer index, and we’ll return an integer value back as a result.
    */
    IntList o_list{};
    o_list[2] = 213; // set a value
    std::cout << o_list[2] << '\n';

    /*
    Now, whenever we use the subscript operator ([]) on an object of our class, the compiler will return 
    the corresponding element from the m_list member variable! This allows us to both get and set values of m_list directly.

    This is both easy syntactically and from a comprehension standpoint. When list[2] evaluates, the compiler 
    first checks to see if there’s an overloaded operator[] function. If so, it passes the value inside the hard braces 
    (in this case, 2) as an argument to the function.

    Note that although you can provide a default value for the function parameter, actually using operator[] without a 
    subscript inside is not considered a valid syntax, so there’s no point.

    Tip

    C++23 will add support for overloading operator[] with multiple subscripts.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Why operator[] returns a reference" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Let’s take a closer look at how list[2] = 3 evaluates. Because the subscript operator has a higher precedence than the 
    assignment operator, list[2] evaluates first. list[2] calls operator[], which we’ve defined to return a reference to 
    list.m_list[2]. Because operator[] is returning a reference, it returns the actual list.m_list[2] array element. 
    Our partially evaluated expression becomes list.m_list[2] = 3, which is a straightforward integer assignment.

    In lesson 1.3 -- Introduction to objects and variables, you learned that any value on the left hand side of an assignment 
    statement must be an l-value (which is a variable that has an actual memory address). Because the result of operator[] 
    can be used on the left hand side of an assignment (e.g. list[2] = 3), the return value of operator[] must be an l-value. 
    As it turns out, references are always l-values, because you can only take a reference of variables that have memory 
    addresses. So by returning a reference, the compiler is satisfied that we are returning an l-value.

    Consider what would happen if operator[] returned an integer by value instead of by reference. list[2] would call 
    operator[], which would return the value of list.m_list[2]. For example, if m_list[2] had the value of 6, operator[] 
    would return the value 6. list[2] = 3 would partially evaluate to 6 = 3, which makes no sense! If you try to do this, 
    the C++ compiler will complain:

    C:VCProjectsTest.cpp(386) : error C2106: '=' : left operand must be l-value
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Dealing with const objects" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    In the above IntList example, operator[] is non-const, and we can use it as an l-value to change the state of 
    non-const objects. However, what if our IntList object was const? In this case, we wouldn’t be able to call the non-const 
    version of operator[] because that would allow us to potentially change the state of a const object.

    The good news is that we can define a non-const and a const version of operator[] separately. The non-const version 
    will be used with non-const objects, and the const version with const-objects.
    */
    IntList op_list{};
    op_list[7] = 13;
    std::cout << op_list[7] << '\n';

    const IntList ww_list{};
    std::cout << ww_list.getValue_second_list(4) << '\n';

    /*
    If we comment out the line clist[2] = 3, the above program compiles and executes as expected.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Error checking" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    */


    return 0;
}
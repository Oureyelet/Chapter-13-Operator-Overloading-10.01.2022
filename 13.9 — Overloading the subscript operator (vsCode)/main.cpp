#include <iostream>

class IntList
{
private:
    int m_list[10]{};

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
};

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
    
    */

    return 0;
}
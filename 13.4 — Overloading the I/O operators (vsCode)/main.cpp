#include <iostream>

class Point
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point(double x, double y, double z)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }

    double getX() { return m_x; }
    double getY() { return m_y; }
    double getZ() { return m_z; }

    void print() const
    {
        std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ").\n";
    }
};

int main()
{
    /*
    For classes that have multiple member variables, printing each of the individual variables on the screen 
    can get tiresome fast. For example, consider the following class:
    */

    // see our Point class...

    /*
    If you wanted to print an instance of this class to the screen, you’d have to do something like this:
    */
    Point point{ 5.0, 6.0, 7.0 };

    std::cout << "Point(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ").\n";
 
    /*
    Of course, it makes more sense to do this as a reusable function. And in previous examples, you’ve 
    seen us create print() functions that work like this:
    */
    point.print();

    /*
    While this is much better, it still has some downsides. Because print() returns void, it can’t be called in 
    the middle of an output statement. Instead, you have to do this:
    */
    const Point pointX{ 7.7, 2.2, 6.6 };

    std::cout << "My point is: ";
    pointX.print();
    std::cout << " in Caresian space.\n";

    /*
    It would be much easier if you could simply type:
    */
    /*
    Point point{5.0, 6.0, 7.0};
    cout << "My point is: " << point << " in Cartesian space.\n";
    */

    /*
    and get the same result. There would be no breaking up output across multiple statements, and no having to 
    remember what you named the print function.

    Fortunately, by overloading the << operator, you can!
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Overloading operator<<" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Overloading operator<< is similar to overloading operator+ (they are both binary operators), except that the 
    parameter types are different.

    Consider the expression std::cout << point. If the operator is <<, what are the operands? The left operand is 
    the std::cout object, and the right operand is your Point class object. std::cout is actually an object of type 
    std::ostream. Therefore, our overloaded function will look like this:

    // std::ostream is the type for object std::cout
    friend std::ostream& operator<< (std::ostream& out, const Point& point);

    Implementation of operator<< for our Point class is fairly straightforward -- because C++ already knows how to 
    output doubles using operator<<, and our members are all doubles, we can simply use operator<< to output the 
    member variables of our Point. Here is the above Point class with the overloaded operator<<.
    */
    

    return 0;
}
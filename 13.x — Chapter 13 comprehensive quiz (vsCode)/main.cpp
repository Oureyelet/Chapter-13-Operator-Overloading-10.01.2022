#include <iostream>
#include <cassert>// for assert()
#include <cstdlib> // for std::size_t
#include <iomanip> // for setprecision
#include <cstdint> // for fixed width integers
#include <cmath> // for raund()


class Average
{
private:
    std::int_least32_t sum_of_all_the_numbers{ 0 };
    std::int_least8_t how_many_numbers_youve_seen_so_far{ 0 };

public:
    Average()
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Average& avg)
    {
        out << static_cast<double>(avg.sum_of_all_the_numbers) / avg.how_many_numbers_youve_seen_so_far << '\n';
        
        return out;
    }

    Average& operator += (int num)
    {   
        sum_of_all_the_numbers += num;

        ++how_many_numbers_youve_seen_so_far;
        
        return *this;
    }

};

class IntArray
{
private:
    int m_lenght{ 0 };
    int *m_array{ nullptr };

public:
    IntArray(int lenght)
        : m_lenght{ lenght }
    {
        assert(lenght > 0 && "No no no!");

        m_array = new int[ m_lenght ]{};
    }

    IntArray(const IntArray& copy)
    {
        m_array = new int[ m_lenght ];

        for(int count{ 0 }; count < copy.m_lenght; ++count)
            m_array[count] = copy.m_array[count];
    }

    ~IntArray()
    {
        delete[] m_array;
    }

    int& operator[] (const int arr)
    {
        assert(arr >= 0);
        assert(arr < m_lenght);

        return m_array[arr];
    }

    friend std::ostream& operator<< (std::ostream& out, const IntArray& arr)
    {
        for(int count{ 0 }; count < arr.m_lenght; ++count)
        {
            out << arr.m_array[count] << ' ';
        }
        
        return out;
    }

    // Assignment operator that does a deep copy
    IntArray& operator= (const IntArray& array)
    {
        // self-assignment guard
        if(this == &array)
            return *this;

        // If this array already exists, delete it so we don't leak memory
        delete[] m_array;

        m_lenght = array.m_lenght;

        // Allocate a new array
        m_array = new int[m_lenght];

        // Copy elements from original array to new array
        for(int count{ 0 }; count < array.m_lenght; ++count)
            m_array[count] = array.m_array[count];

        return *this;
    }
};

IntArray fillArray()
{
    IntArray a(5);

    a[0] = 5;
    a[1] = 8;
    a[2] = 2;
    a[3] = 3;
    a[4] = 6;

    return a;
}

class FixedPoint2
{
private:
    std::int_least32_t m_non_fractional_part_of_number{};
    std::int_least8_t m_fractional_component{};

public:

    FixedPoint2(std::int_least32_t p1 = 0, std::int_least8_t p2 = 0)
        : m_non_fractional_part_of_number{ p1 }, m_fractional_component{ p2 }
    {
        if (m_non_fractional_part_of_number < 0 || m_fractional_component < 0)
        {
            if(m_non_fractional_part_of_number > 0)
                m_non_fractional_part_of_number = -m_non_fractional_part_of_number;
            
            if(m_fractional_component > 0)
                m_fractional_component = -m_fractional_component;
        }

    }

    FixedPoint2(double p)
        :m_non_fractional_part_of_number{static_cast<int_least32_t>(std::round(p)) },
        m_fractional_component{ static_cast<int_least8_t>(std::round(p * 100)- m_non_fractional_part_of_number * 100) }
    {
        
    }

    friend std::ostream& operator<< (std::ostream& out, const FixedPoint2& fixedPoint)
    {
        out << static_cast<double>(fixedPoint);
        return out;
    }

    friend std::istream& operator>> (std::istream& in, FixedPoint2& fixedPoint)
    {
        in >> fixedPoint.m_non_fractional_part_of_number;
        in >> fixedPoint.m_fractional_component;

        return in;
    }

    operator double() const
    {
        return m_non_fractional_part_of_number + m_fractional_component / 100.0;
    }

    friend bool operator== (const FixedPoint2& f1, const FixedPoint2& f2)
    {   
        return (f1.m_non_fractional_part_of_number == f2.m_non_fractional_part_of_number &&
                f2.m_fractional_component == f2.m_fractional_component);
    }

    FixedPoint2 operator+ () const;
    FixedPoint2 operator- () const;

    friend FixedPoint2 operator+(const FixedPoint2& f1, double dob);
    friend FixedPoint2 operator-(const FixedPoint2& f1, double dob);
};

FixedPoint2 FixedPoint2::operator+ () const
{
    return FixedPoint2(m_non_fractional_part_of_number + m_fractional_component);
}

FixedPoint2 FixedPoint2::operator- () const
{
   // return FixedPoint2(m_non_fractional_part_of_number - m_fractional_component);
   return { static_cast<int_fast32_t>(-m_non_fractional_part_of_number), static_cast<int_fast8_t>(-m_fractional_component) };
}


FixedPoint2 operator+(const FixedPoint2& f1, double dob)
{
    return FixedPoint2(f1.m_non_fractional_part_of_number + dob, f1.m_non_fractional_part_of_number + dob);
}

FixedPoint2 operator-(const FixedPoint2& f1, double dob)
{
    return FixedPoint2(f1.m_non_fractional_part_of_number - dob, f1.m_non_fractional_part_of_number - dob);
}

void testAddition()
{
    std::cout << std::boolalpha;
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n'; // both positive, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n'; // both positive, with decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n'; // both negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n'; // both negative, with decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n'; // second negative, no decimal overflow
    std::cout << "false?"  << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n'; // second negative, possible decimal overflow
    std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n'; // first negative, no decimal overflow
	std::cout << "false?"  << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n'; // first negative, possible decimal overflow
}


int main()
{
    /*
    In this chapter, we explored topics related to operator overloading, as well as overloaded typecasts, 
    and topics related to the copy constructor.
    */

    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Summary" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Operator overloading is a variant of function overloading that lets you overload operators for your classes. When operators 
    are overloaded, the intent of the operators should be kept as close to the original intent of the operators as possible. If 
    the meaning of an operator when applied to a custom class is not clear and intuitive, use a named function instead.

    Operators can be overloaded as a normal function, a friend function, or a member function. The following rules of thumb can 
    help you determine which form is best for a given situation:

        If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member 
        function.
        If you’re overloading a unary operator, do so as a member function.
        If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), do so as a member function if 
        you can.
        If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function 
        or friend function.

    Typecasts can be overloaded to provide conversion functions, which can be used to explicitly or implicitly convert your class 
    into another type.

    A copy constructor is a special type of constructor used to initialize an object from another object of the same type. Copy 
    constructors are used for direct/uniform initialization from an object of the same type, copy initialization 
    (Fraction f = Fraction(5,3)), and when passing or returning a parameter by value.

    If you do not supply a copy constructor, the compiler will create one for you. Compiler-provided copy constructors will use 
    memberwise initialization, meaning each member of the copy is initialized from the original member. The copy constructor may 
    be elided for optimization purposes, even if it has side-effects, so do not rely on your copy constructor actually executing.

    Constructors are considered converting constructors by default, meaning that the compiler will use them to implicitly convert 
    objects of other types into objects of your class. You can avoid this by using the explicit keyword in front of your 
    constructor. You can also delete functions within your class, including the copy constructor and overloaded assignment 
    operator if desired. This will cause a compiler error if a deleted function would be called.

    The assignment operator can be overloaded to allow assignment to your class. If you do not provide an overloaded assignment 
    operator, the compiler will create one for you. Overloaded assignment operators should always include a self-assignment check 
    (unless it’s handled naturally, or you’re using the copy and swap idiom).

    New programmers often mix up when the assignment operator vs copy constructor are used, but it’s fairly straightforward:

        If a new object has to be created before the copying can occur, the copy constructor is used (note: this includes passing 
        or returning objects by value).
        If a new object does not have to be created before the copying can occur, the assignment operator is used.

    By default, the copy constructor and assignment operators provided by the compiler do a memberwise initialization or 
    assignment, which is a shallow copy. If your class dynamically allocates memory, this will likely lead to problems, as 
    multiple objects will end up pointing to the same allocated memory. In this case, you’ll need to explicitly define these 
    in order to do a deep copy. Even better, avoid doing your own memory management if you can and use classes from the standard 
    library.
    */


    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Quiz Time" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Assuming Point is a class and point is an instance of that class, should you use a normal/friend or member function 
    overload for the following operators?

    1a) point + point
    1b) -point
    1c) std::cout << point
    1d) point = 5;
    */
    
    /*
    Write a class named Average that will keep track of the average of all integers passed to it. Use two members: The first 
    one should be type std::int_least32_t, and used to keep track of the sum of all the numbers you’ve seen so far. 
    The second should be of type std::int_least8_t, and used to keep track of how many numbers you’ve seen so far. 
    You can divide them to find your average.
    
    2a) Write all of the functions necessary for the following program to run:
    */
    Average avg{};

    avg += 4;
    std::cout << avg; // 4 / 1 = 4

    avg += 8;
	std::cout << avg;// (4 + 8) / 2 = 6

    avg += 24;
	std::cout << avg;// (4 + 8 + 24) / 3 = 12

    avg += -10;
	std::cout << avg; // (4 + 8 + 24 - 10) / 4 = 6.5

    (avg += 6) += 10; // 2 calls chained together
	std::cout << avg; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

    Average copy{ avg };
	std::cout << copy << '\n';

    /*
    2b) Does this class need an explicit copy constructor or assignment operator?
    */

    /*
    Write your own integer array class named IntArray from scratch (do not use std::array or std::vector). 
    Users should pass in the size of the array when it is created, and the array should be dynamically allocated. 
    Use assert statements to guard against bad data. Create any constructors or overloaded operators needed to make the 
    following program operate correctly:
    */
    IntArray a{ fillArray() };
    std::cout << a << '\n';

    auto& ref{ a };
    a = ref;

    IntArray b(1);
    b = a;

    std::cout << b << '\n';

    /*
        Extra credit: This one is a little more tricky. A floating point number is a number with a decimal where the number of 
        digits after the decimal can be variable. A fixed point number is a number with a fractional component where the number 
        of digits in the fractional portion is fixed.

    In this quiz, we’re going to write a class to implement a fixed point number with two fractional digits (e.g. 12.34, 3.00, 
    or 1278.99). Assume that the range of the class should be -32768.99 to 32767.99, that the fractional component should hold 
    any two digits, that we don’t want precision errors, and that we want to conserve space.

    4a) What type of member variable(s) do you think we should use to implement our fixed point number with 2 digits after the 
    decimal? (Make sure you read the answer before proceeding with the next questions)
    
    4b) Write a class named FixedPoint2 that implements the recommended solution from the previous question. If either (or both) 
    of the non-fractional and fractional part of the number are negative, the number should be treated as negative. 
    Provide the overloaded operators and constructors required for the following program to run:
    */
    FixedPoint2 aa{ 34, 56 };
	std::cout << aa << '\n';

	FixedPoint2 bb{ -2, 8 };
	std::cout << bb << '\n';

	FixedPoint2 c{ 2, -8 };
	std::cout << c << '\n';

	FixedPoint2 d{ -2, -8 };
	std::cout << d << '\n';

	FixedPoint2 e{ 0, -5 };
	std::cout << e << '\n';

	std::cout << static_cast<double>(e) << '\n';

    /*
    4c) Now add a constructor that takes a double. The follow program should run:
    */
    std::cout << "4c" << '\n';

    FixedPoint2 aaa{ 0.01 };
	std::cout << aaa << '\n';

	FixedPoint2 bbb{ -0.01 };
	std::cout << bbb << '\n';

	FixedPoint2 ccc{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	std::cout << ccc << '\n';

	FixedPoint2 ddd{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	std::cout << ddd << '\n';

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 eee{ 106.9978 }; // should be stored with base 107 and decimal 0
	std::cout << eee << '\n';

    /*
    4d) Overload operator==, operator >>, operator- (unary), and operator+ (binary).
    */
    std::cout << "4d)" << '\n';

    testAddition();

    FixedPoint2 anna{ -0.48 };
    std::cout << anna << '\n';

    std::cout << -anna << '\n';

    std::cout << "Enter a number:"; // enter 5.678
    std::cin >> anna;

    std::cout << "You entered:" << anna << '\n';





    return 0;
}
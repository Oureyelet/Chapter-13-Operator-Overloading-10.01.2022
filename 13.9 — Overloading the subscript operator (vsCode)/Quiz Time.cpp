#include <iostream>
#include <cassert>// for asser()
#include <array>// for std::size()
#include <string>
#include <vector>
#include <algorithm>
#include <map> // for std::map


struct StudentGrade
{
	std::string name{};
	char grade{};
};

class GradeMap
{
private:
    std::vector<StudentGrade> m_map{};

public:
    GradeMap() = default;

    char& operator[](const std::string& name); 
};


char& GradeMap::operator[](const std::string& name)
{
    auto found{ std::find_if(m_map.begin(), m_map.end(),
                                [&](const auto& student)
                                {
                                    return (student.name == name);
                                }) };

    if(found != m_map.end())
    {
        return found->grade;
    }
    
    m_map.push_back({ name });

    return m_map.back().grade;
}


int main()
{
    std::cout << std::endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    std::cout << "Quiz Time" << '\n';
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////" << '\n';
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Question #1

    A map is a class that stores elements as a key-value pair. The key must be unique, and is used to access the associated pair. 
    In this quiz, we’re going to write an application that lets us assign grades to students by name, using a simple map class. 
    The student’s name will be the key, and the grade (as a char) will be the value.

    a) First, write a struct named StudentGrade that contains the student’s name (as a std::string) and grade (as a char).
    
    b) Add a class named GradeMap that contains a std::vector of StudentGrade named m_map.

    c) Write an overloaded operator[] for this class. This function should take a std::string parameter, and return a reference 
    to a char. In the body of the function, first see if the student’s name already exists (You can use std::find_if 
    from <algorithm>). If the student exists, return a reference to the grade and you’re done. Otherwise, use the 
    std::vector::push_back() function to add a StudentGrade for this new student. When you do this, std::vector will add a 
    copy of your StudentGrade to itself (resizing if needed, invalidating all previously returned references). Finally, we 
    need to return a reference to the grade for the student we just added to the std::vector. We can access the student we 
    just added using the std::vector::back() function.

    The following program should run:
    */
    GradeMap grades{};

	grades["Joe"] = 'A';
	grades["Frank"] = 'B';

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

    /*
    TIP !
   
    Since maps are common, the standard library offers std::map, which is not currently covered on learncpp. 
    Using std::map, we can simplify our code to
    */

    // std::map can be initialized
    std::map<std::string, char> map_grades
    {
        {"Ania", 'A'},
        {"Mateusz", 'C'}
    };

    // and assigned
    map_grades["Tobias"] = 'A';
    map_grades["Sofia"] = 'B';

    std::cout << "Sofia has a grade of " << map_grades["Sofia"] << '\n';
    std::cout << "Tobias has a grade of " << map_grades["Tobias"] << '\n';
    std::cout << "Ania has a grade of " << map_grades["Ania"] << '\n';
    std::cout << "Mateusz has a grade of " << map_grades["Mateusz"] << '\n';

    //Prefer using std::map over writing your own implementation.

    /*
    Question #2

    Extra credit #1: The GradeMap class and sample program we wrote is inefficient for many reasons. 
    Describe one way that the GradeMap class could be improved.
    
    std::vector is unsorted by nature. This means every time we call operator[], we’re potentially traversing the entire 
    std::vector to find our element. With a few elements, this isn’t a problem, but as we continue to add names, this will 
    become increasingly slow. We could optimize this by keeping our m_map sorted and using a binary search, so we minimize 
    the number of elements we have to look through to find the ones we’re interested in.
    */

    /*
    test
    */
    std::map<int, double> test_one
    {
        {7, 3.3},
        {8, 2.2}
    };

    return 0;
}
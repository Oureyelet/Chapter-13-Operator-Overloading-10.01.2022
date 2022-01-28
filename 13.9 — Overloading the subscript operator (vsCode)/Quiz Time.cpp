#include <iostream>
#include <cassert>// for asser()
#include <array>// for std::size()
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>

bool constainsName(std::string_view name)
{
    return (name.find(name) != std::string_view::npos);
}

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

    std::string& operator[](std::string map); 
};


std::string& GradeMap::operator[](std::string name, char grade)
{
    auto found{ std::find_if( m_map.begin(), m_map.end(), constainsName ) };

    if(found == m_map.end())
    {
        return name;
    }
    else
    {
        StudentGrade student = { name }
    }

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


    


    return 0;
}
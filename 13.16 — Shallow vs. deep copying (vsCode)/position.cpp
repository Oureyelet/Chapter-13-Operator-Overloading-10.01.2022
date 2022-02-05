#include <iostream>

class Position
{
private:
    int m_x{};
    int m_y{};

public:
    Position(int x, int y)
        : m_x{ x }, m_y{ y }
    {

    }

    friend bool operator== (const Position& p1, const Position& p2);


};

bool operator== (const Position& p1, const Position& p2)
{
    return (p1.m_x + p1.m_y == p2.m_x + p2.m_y);
}

int main()
{
    Position pos1{ 3, 4 };
    Position pos2{ 3, 5 };

    if( pos1 == pos2 )
    {
        std::cout << "Position is same !" << '\n';
        std::cout << "Jesus is Lord" << '\n';
        std::cout << "I love my God" << '\n';
    }
    else
        std::cout << "Position vary !" << '\n';


    return 0;
}
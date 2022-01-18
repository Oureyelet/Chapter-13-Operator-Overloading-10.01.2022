#include <iostream>
#include <numeric>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        reduce();
    }

    friend Fraction operator*(const Fraction& f1, const Fraction& f2);
    friend Fraction operator*(const Fraction& f1, int value);

    void reduce()
    {
        int gcd{ std::gcd(m_numerator, m_denominator) };

        if(gcd)
        {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
    }

    friend std::ostream& operator << ( std::ostream& out, const Fraction& fraction );
    friend std::istream& operator >> ( std::iostream& in, Fraction& fraction );
};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    int numerato{ f1.m_numerator * f2.m_numerator };
    int denominator{ f1.m_denominator * f2.m_denominator };

    return { numerato, denominator };
}

Fraction operator*(const Fraction& f1, int value)
{
    int numerator{ f1.m_numerator * value };

    return { numerator, f1.m_denominator };
}


std::ostream& operator << ( std::ostream& out, const Fraction& fraction )
{
    out << fraction.m_numerator 
}
    
std::istream& operator >> ( std::iostream& in, Fraction& fraction );
{

}

int main()
{
    Fraction f1;
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;

	Fraction f2;
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;

	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // note: The result of f1 * f2 is an r-value

    return 0;
}
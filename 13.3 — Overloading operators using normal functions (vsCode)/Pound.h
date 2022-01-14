#ifndef POUND_H
#define POUND_H

class Pound
{
private:
    int m_pound{};

public:
    Pound(int pound)
        : m_pound{ pound }
    {

    }

    int getPound() const { return m_pound; }
};

Pound operator-(const Pound& p1, const Pound& p2);

#endif // end POUND_H
#include "Pound.h"

Pound operator-(const Pound& p1, const Pound& p2)
{
    return { p1.getPound() - p2.getPound() };
}
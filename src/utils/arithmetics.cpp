#include "arithmetics.h"

double Arithmetics::Scale(double num, double inMin, double inMax, double outMin, double outMax)
{
    return (double) (num - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double Arithmetics::Clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}
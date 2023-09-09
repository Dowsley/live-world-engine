#ifndef ARITHMETICS_H
#define ARITHMETICS_H

class Arithmetics
{
    public:
        static double Scale(double num, double inMin, double inMax, double outMin, double outMax);
        static double Clamp(double x, double min, double max);
};

#endif

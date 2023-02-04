#include "arithmetics.h"

float Arithmetics::scale(float num,float in_min, float in_max,float out_min,float out_max)
{
    return (float) (num - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

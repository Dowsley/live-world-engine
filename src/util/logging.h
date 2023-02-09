#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include "../structures/color.h"

class Logging
{
public:
    static void LogColor(const Color &p);
};

#endif
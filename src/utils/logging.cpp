#include <cstdio>

#include "logging.h"

void LoggingUtils::LogColor(const Color &p)
{
    printf("R: %d, G: %d, B:%d\n", p.r, p.g, p.b);
}

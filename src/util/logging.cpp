#include "logging.h"

void Logging::LogColor(const Color &p)
{
    printf("R: %d, G: %d, B:%d\n", p.r, p.g, p.b);
}
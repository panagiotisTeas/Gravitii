#include <stdio.h>
#include <stdlib.h>

#include "app.h"

int main()
{
    Gravitii config;

    gravitiiInitConfig(&config);
    gravitiiRun(&config);

    return EXIT_SUCCESS;
}
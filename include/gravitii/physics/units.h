#ifndef _GRAVITII_UNITS_H
#define _GRAVITII_UNITS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "utils/arena.h"

typedef enum LengthUnit
{
    LU_METER = 0,
    LU_KILOMETER,
    LU_EARTH_RADIUS,
    LU_ASTRONOMICAL_UNIT,
    LU_LIGHT_YEAR,
    LU_PARSEC,
    LU_KILOPARSEC,
    LU_MEGAPARSEC,
} LengthUnit;

typedef enum TimeUnit
{
    TU_SECOND = 0,
    TU_HOUR,
    TU_DAY,
    TU_YEAR,
} TimeUnit;

typedef enum MassUnit
{
    MU_KILOGRAM = 0,
    MU_EARTH_MASS,
    MU_JUPITER_MASS,
    MU_SOLAR_MASS,
} MassUnit;

typedef struct UnitSystem
{
    double      G;
    LengthUnit  L;
    TimeUnit    T;
    MassUnit    M;
} UnitSystem;

UnitSystem* unitSystemCreate(LengthUnit L, TimeUnit T, MassUnit M, Arena* arena);

#ifdef __cplusplus
}
#endif

#endif // _GRAVITII_UNITS_H
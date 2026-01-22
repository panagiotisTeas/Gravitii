#include "physics/units.h"

static double length_to_meters(LengthUnit unit)
{
    switch (unit)
    {
        case LU_METER: return 1.0;
        case LU_KILOMETER: return 1.0e3;
        case LU_EARTH_RADIUS: return 6.371e6;
        case LU_ASTRONOMICAL_UNIT: return 1.496e11;
        case LU_LIGHT_YEAR: return 9.46e15;
        case LU_PARSEC: return 3.0857e16;
        case LU_KILOPARSEC: return 3.0857e19;
        case LU_MEGAPARSEC: return 3.0857e22;
        default: return 1.0;
    }
}

static double time_to_seconds(TimeUnit unit)
{
    switch (unit)
    {
        case TU_SECOND: return 1.0;
        case TU_HOUR: return 3600.0;
        case TU_DAY: return 86400.0;
        case TU_YEAR: return 31556926.0;
        default: return 1.0;
    }
}

static double mass_to_kilograms(MassUnit unit)
{
    switch (unit)
    {
        case MU_KILOGRAM: return 1.0;
        case MU_EARTH_MASS: return 5.972e24;
        case MU_JUPITER_MASS: return 1.898e27;
        case MU_SOLAR_MASS: return 1.9891e30;
        default: return 1.0;
    }
}

static void calculate_G(UnitSystem* system)
{
    const double G_SI = 6.67430e-11;

    double L = length_to_meters(system->L);
    double T = time_to_seconds(system->T);
    double M = mass_to_kilograms(system->M);
    
    system->G = G_SI * (M * T * T) / (L * L * L);
}

UnitSystem* unitSystemCreate(LengthUnit L, TimeUnit T, MassUnit M, Arena* arena)
{
    UnitSystem* unit_system = arenaPushStruct(arena, UnitSystem);

    unit_system->L = L;
    unit_system->T = T;
    unit_system->M = M;
    calculate_G(unit_system);

    return unit_system;
}
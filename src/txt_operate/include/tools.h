#ifndef TOOLS_H
#define TOOLS_H

#include "ros/ros.h"
#include <cmath>
#include <random>
using namespace std;

float randomFloat(float lower, float upper)
{
	return (lower + (static_cast<float>(rand()) / RAND_MAX) * (upper - lower));
}

double randomDouble(double lower, double upper)
{
	return (lower + (static_cast<double>(rand()) / RAND_MAX) * (upper - lower));
}

double gaussian_noise(double mu, double sigma)
{
    const double epsilon = std::numeric_limits<double>::min();
    const double two_pi = 2.0*3.14159265358979323846;

    static double z0, z1;
    static bool generate;
    generate = !generate;

    if (!generate)
        return z1 * sigma + mu;

    double u1, u2;
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    }
    while (u1 <= epsilon);

    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}


#endif

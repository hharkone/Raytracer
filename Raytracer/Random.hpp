#pragma once
#include <random>

class Random
{

public:
    Random(int seed);
    double next();

private:
    std::mt19937 engine;
    std::uniform_real_distribution<double> dist;
};
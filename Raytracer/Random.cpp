#include "Random.hpp"


Random::Random(int seed)
{
    engine.seed(seed);
    dist.reset();
}

double Random::next()
{
    return dist(engine);
}

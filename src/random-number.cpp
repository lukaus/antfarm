#include "random-number.h"

namespace Random
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937_64 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 6);

    int GetInt(int min, int max)
    {
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    // float GetFloat(float min, float max)
    // {
    //     std::uniform_int_distribution<float> dis(min, max);
    //     return dis(gen);
    // }
}
#include <cstdlib>
#include <ctime>
#include <random>
#include <time.h>

class RandomGenerator {
    std::random_device rd;
    std::mt19937 gen;
public:
    RandomGenerator() {
        gen = std::mt19937(rd());
    }

    int generateRandomInt(int a, int b) {
        std::uniform_int_distribution<> dist(a, b);
        return dist(gen);
    }
    float generateRandomFloat(float a, float b) {
        std::uniform_real_distribution<> dist(a, b);
        return dist(gen);
    }
    double generateRandomDouble(double a, double b){

        std::uniform_real_distribution<> dist(a, b);
        return dist(gen);
    }


};
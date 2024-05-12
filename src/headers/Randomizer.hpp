#pragma once

#include <random>
#include <string>

class Randomizer {
    private:
        Randomizer();
        std::mt19937 gen;
        std::uniform_int_distribution<> dis;
    public:
        static Randomizer& GetInstance();
        std::string randomString(int length);
};
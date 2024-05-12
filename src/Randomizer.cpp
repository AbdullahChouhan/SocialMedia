#include "headers/Randomizer.hpp"

Randomizer::Randomizer() : gen(std::random_device{}()), dis(0, 255) {}

Randomizer& Randomizer::GetInstance() {
    static Randomizer instance;
    return instance;
}

std::string Randomizer::randomString(int length) {
    std::string result = "";
    if (length > 0) {
        for (int i = 0; i < length; i++) {
            result += static_cast<char>(dis(gen));
        }
        return result;
    }
    return result;
}
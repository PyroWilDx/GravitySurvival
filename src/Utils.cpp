#include <ctime>
#include "Utils.hpp"

using namespace std;

std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
std::uniform_real_distribution<float> random(0.0f, 1.0f);

float Utils::randomFloat() {
    return random(rng);
}

void Utils::triNaif(vector<string> &T) {
    for (vector<int>::size_type i = 0; i < T.size(); i++) {
        float max = std::stof(T[i]);
        int max_index = i;
        for (vector<int>::size_type j = i + 1; j < T.size(); j++) {
            if (std::stof(T[j]) > max) {
                max = std::stof(T[j]);
                max_index = j;
            }
        }
        string tmp = T[i];
        T[i] = T[max_index];
        T[max_index] = tmp;
    }
}

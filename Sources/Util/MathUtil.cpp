#include "MathUtil.hpp"

#include <random>

double MathUtil::lerp(double a, double b, double t) {
    return (1.0 - t) * a + b * t;
}

double MathUtil::invLerp(double a, double b, double v) {
    return (v - a) / (b - a);
}

double MathUtil::remap(double iMin, double iMax, double oMin, double oMax, double v) {
    double t = invLerp(iMin, iMax, v);
    return lerp(oMin, oMax, t);
}

int MathUtil::random(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

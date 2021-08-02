#pragma once

#include <cmath>

namespace MathUtil {
    [[nodiscard]] double lerp(double a, double b, double t);
    [[nodiscard]] double invLerp(double a, double b, double t);
    [[nodiscard]] double remap(double iMin, double iMax, double oMin, double oMax, double v);
    template<typename T>
    [[nodiscard]] T range(T min, T max, T curr) {
        return std::max(std::min(curr, max), min);
    }
}

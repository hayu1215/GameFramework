#include"Mathf.h"
#include<cmath>
#include<random>

float mathf::Abs(float f) {
    return std::abs(f);
}

float mathf::Acos(float f) {
    return std::acos(f);
}

float mathf::Asin(float f) {
    return std::asin(f);
}

float mathf::Atan(float f) {
    return std::atan(f);
}

float mathf::Atan2(float y, float x) {
    return std::atan2(y, x);
}

float mathf::Ceil(float f) {
    return std::ceilf(f);
}

float mathf::Ceil(float f, unsigned int n) {
    if (n <= 0)return std::ceilf(f);

    int temp = static_cast<int>(std::pow(10, n - 1));
    return std::ceil(f * temp) / temp;
}

float mathf::Clamp(float value, float min, float max) {
    return std::min(std::max(value, min), max);
}

int mathf::Clamp(int value, int min, int max) {
    return std::min(std::max(value, min), max);
}

float mathf::Clamp01(float f) {
    return Clamp(f, 0.0f, 1.0f);
}

int mathf::Clamp01(int i) {
    return Clamp(i, 0, 1);
}

float mathf::Cos(float radian) {
    return std::cos(radian);
}

float mathf::DegreeNormalize(float degree) {
    return Round(RadianNormalize(degree * DEG2RAD) * RAD2DEG, 2);
}

float mathf::DeltaAngle(float current, float target) {
    float current_N = DegreeNormalize(current);
    float target_N = DegreeNormalize(target);

    return target_N - current_N;
}

float mathf::Floor(float f) {
    return std::floor(f);
}

float mathf::Floor(float f, int n) {
    if (n <= 0)return std::floor(f);

    int temp = static_cast<int>(std::pow(10, n - 1));
    return std::floor(f * temp) / temp;
}

float mathf::Log(float x, float base) {
    return std::log(x) / std::log(base);
}

float mathf::Log10(float x) {
    return std::log10(x);
}

float mathf::Maxf(float a, float b) {
    return std::max(a, b);
}

float mathf::Minf(float a, float b) {
    return std::min(a, b);
}

float mathf::Pow(float x, float y) {
    return std::pow(x, y);
}

float mathf::RadianNormalize(float radian) {
    return std::atan2(sin(radian), cos(radian));
}

float mathf::Random(float min, float max) {
    if (max <= min)return 0;

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_real_distribution<float> rand(min, max);
    return rand(mt);
}

int mathf::Random(int min, int max) {
    if (max <= min)return 0;

    std::random_device device;
    std::mt19937 mt(device());
    std::uniform_int_distribution<int> rand(min, max);
    return rand(mt);
}

float mathf::Round(float f) {
    return std::round(f);
}

float mathf::Round(float f, int n) {
    if (n <= 0)return std::round(f);

    int temp = static_cast<int>(std::pow(10, n - 1));
    return std::round(f * temp) / temp;
}

int mathf::Sign(float f) {
    return (f > 0) - (f < 0);
}

float mathf::Sin(float radian) {
    return std::sin(radian);
}

float mathf::Sqrt(float f) {
    if (f < 0)return 0;

    return std::sqrt(f);
}

float mathf::Tan(float radian) {
    return std::tan(radian);
}

float mathf::ToDegree(float radian) {
    return radian * RAD2DEG;
}

float mathf::ToRadian(float degree) {
    return degree * DEG2RAD;
}
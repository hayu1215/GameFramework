#include"Mathf.h"
#include<cmath>
#include<random>

float mathf::abs(float f)
{
	return std::abs(f);
}

float mathf::acos(float f)
{
	return std::acos(f);
}

float mathf::asin(float f)
{
	return std::asin(f);
}

float mathf::atan(float f)
{
	return std::atan(f);
}

float mathf::atan2(float y, float x)
{
	return std::atan2(y, x);
}

float mathf::ceil(float f)
{
	return std::ceilf(f);
}

float mathf::ceil(float f, unsigned int n)
{
	if (n <= 0)return std::ceilf(f);

	int temp = static_cast<int>(std::pow(10, n - 1));
	return std::ceil(f * temp) / temp;
}

float mathf::clamp(float value, float min, float max)
{
	return std::min(std::max(value, min), max);
}

int mathf::clamp(int value, int min, int max)
{
	return std::min(std::max(value, min), max);
}

float mathf::clamp01(float f)
{
	return clamp(f, 0.0f, 1.0f);
}

int mathf::clamp01(int i)
{
	return clamp(i, 0, 1);
}

float mathf::cos(float radian)
{
	return std::cos(radian);
}

float mathf::degreeNormalize(float degree)
{
	return round(radianNormalize(degree * DEG2RAD) * RAD2DEG, 2);
}

float mathf::deltaAngle(float current, float target)
{
	float current_N = degreeNormalize(current);
	float target_N = degreeNormalize(target);

	return target_N - current_N;
}

float mathf::floor(float f)
{
	return std::floor(f);
}

float mathf::floor(float f, int n)
{
	if (n <= 0)return std::floor(f);

	int temp = static_cast<int>(std::pow(10, n - 1));
	return std::floor(f * temp) / temp;
}

float mathf::log(float x, float base)
{
	return std::log(x) / std::log(base);
}

float mathf::log10(float x)
{
	return std::log10(x);
}

float mathf::max(float a, float b)
{
	return std::max(a, b);
}

float mathf::min(float a, float b)
{
	return std::min(a, b);
}

float mathf::pow(float x, float y)
{
	return std::pow(x, y);
}

float mathf::radianNormalize(float radian)
{
	return std::atan2(sin(radian), cos(radian));
}

float mathf::random(float min, float max)
{
	if (max <= min)return 0;

	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_real_distribution<float> rand(min, max);
	return rand(mt);
}

int mathf::random(int min, int max)
{
	if (max <= min)return 0;

	std::random_device device;
	std::mt19937 mt(device());
	std::uniform_int_distribution<int> rand(min, max);
	return rand(mt);
}

float mathf::round(float f)
{
	return std::round(f);
}

float mathf::round(float f, int n)
{
	if (n <= 0)return std::round(f);

	int temp = static_cast<int>(std::pow(10, n - 1));
	return std::round(f * temp) / temp;
}

int mathf::sign(float f)
{
	return (f > 0) - (f < 0);
}

float mathf::sin(float radian)
{
	return std::sin(radian);
}

float mathf::sqrt(float f)
{
	if (f < 0)return 0;

	return std::sqrt(f);
}

float mathf::tan(float radian)
{
	return std::tan(radian);
}

float mathf::toDegree(float radian)
{
	return radian * RAD2DEG;
}

float mathf::toRadian(float degree)
{
	return degree * DEG2RAD;
}
#pragma once

namespace mathf
{
	constexpr float PI = 3.14159f;
	constexpr float DEG2RAD = PI / 180.0f;
	constexpr float RAD2DEG = 180.0f / PI;

	//絶対値を返します
	float abs(float f);

	//Cosからラジアンで角度を返します
	float acos(float f);

	//Sinからラジアンで角度を返します
	float asin(float f);

	//Tanからラジアンで角度を返します
	float atan(float f);

	//座標からラジアンで角度を返します
	float atan2(float y, float x);

	//切り上げした値を返します
	float ceil(float f);

	//小数点第n位を切り上げした値を返します
	float ceil(float f, unsigned int n);

	//最小値と最大値の範囲内に収めた値を返します
	float clamp(float value, float min, float max);

	//最小値と最大値の範囲内に収めた値を整数で返します
	int clamp(int value, int min, int max);

	//0.0f～1.0fの範囲内に収めた値を返します
	float clamp01(float f);

	//0.0f～1.0fの範囲内に収めた値を整数で返します
	int clamp01(int i);

	//Cosを返します
	float cos(float radian);

	//度を-180°～180°に収めた値を返します
	float degreeNormalize(float degree);

	//ターゲットまでの角度を度で返します
	float deltaAngle(float current, float target);

	//切り捨てした値を返します
	float floor(float f);

	//小数点第n位を切り捨てした値を返します
	float floor(float f, int n);

	//指定された数を底とする数値の対数を返します
	float log(float x, float base);

	//10を底とする数値の対数を返します
	float log10(float x);

	//与えられた引数から大きい方の数を返します
	float max(float a, float b);

	//与えられた引数から小さいほうの数を返します
	float min(float a, float b);

	//xのy乗の値を計算します
	float pow(float x, float y);

	//ラジアンを-π～πに収めた値を返します
	float radianNormalize(float radian);

	//最小値から最大値までの範囲内の乱数を返します
	float random(float min, float max);

	//最小値から最大値までの範囲内の乱数を整数で返します
	int random(int min, int max);

	//四捨五入した値を返します
	float round(float f);

	//小数第n位を四捨五入した値を返します
	float round(float f, int num);

	//数値の正負を調べて返します（正:1, 負:-1, 0:0）
	int sign(float f);

	//Sinを返します
	float sin(float radian);

	//正の平方根を返します
	float sqrt(float f);

	//Tanを返します
	float tan(float radian);

	//ラジアンから度に変換します
	float toDegree(float radian);

	//度からラジアンに変換します
	float toRadian(float degree);
}
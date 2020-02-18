#pragma once

namespace mathf
{
	constexpr float PI = 3.14159f;
	constexpr float DEG2RAD = PI / 180.0f;
	constexpr float RAD2DEG = 180.0f / PI;

	//��Βl��Ԃ��܂�
	float Abs(float f);

	//Cos���烉�W�A���Ŋp�x��Ԃ��܂�
	float Acos(float f);

	//Sin���烉�W�A���Ŋp�x��Ԃ��܂�
	float Asin(float f);

	//Tan���烉�W�A���Ŋp�x��Ԃ��܂�
	float Atan(float f);

	//���W���烉�W�A���Ŋp�x��Ԃ��܂�
	float Atan2(float y, float x);

	//�؂�グ�����l��Ԃ��܂�
	float Ceil(float f);

	//�����_��n�ʂ�؂�グ�����l��Ԃ��܂�
	float Ceil(float f, unsigned int n);

	//�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l��Ԃ��܂�
	float Clamp(float value, float min, float max);

	//�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l�𐮐��ŕԂ��܂�
	int Clamp(int value, int min, int max);

	//0.0f�`1.0f�͈͓̔��Ɏ��߂��l��Ԃ��܂�
	float Clamp01(float f);

	//0.0f�`1.0f�͈͓̔��Ɏ��߂��l�𐮐��ŕԂ��܂�
	int Clamp01(int i);

	//Cos��Ԃ��܂�
	float Cos(float radian);

	//�x��-180���`180���Ɏ��߂��l��Ԃ��܂�
	float DegreeNormalize(float degree);

	//�^�[�Q�b�g�܂ł̊p�x��x�ŕԂ��܂�
	float DeltaAngle(float current, float target);

	//�؂�̂Ă����l��Ԃ��܂�
	float Floor(float f);

	//�����_��n�ʂ�؂�̂Ă����l��Ԃ��܂�
	float Floor(float f, int n);

	//�w�肳�ꂽ�����Ƃ��鐔�l�̑ΐ���Ԃ��܂�
	float Log(float x, float base);

	//10���Ƃ��鐔�l�̑ΐ���Ԃ��܂�
	float Log10(float x);

	//�^����ꂽ��������傫�����̐���Ԃ��܂�
	float Maxf(float a, float b);

	//�^����ꂽ�������珬�����ق��̐���Ԃ��܂�
	float Minf(float a, float b);

	//x��y��̒l���v�Z���܂�
	float Pow(float x, float y);

	//���W�A����-�΁`�΂Ɏ��߂��l��Ԃ��܂�
	float RadianNormalize(float radian);

	//�ŏ��l����ő�l�܂ł͈͓̔��̗�����Ԃ��܂�
	float Random(float min, float max);

	//�ŏ��l����ő�l�܂ł͈͓̔��̗����𐮐��ŕԂ��܂�
	int Random(int min, int max);

	//�l�̌ܓ������l��Ԃ��܂�
	float Round(float f);

	//������n�ʂ��l�̌ܓ������l��Ԃ��܂�
	float Round(float f, int num);

	//���l�̐����𒲂ׂĕԂ��܂��i��:1, ��:-1, 0:0�j
	int Sign(float f);

	//Sin��Ԃ��܂�
	float Sin(float radian);

	//���̕�������Ԃ��܂�
	float Sqrt(float f);

	//Tan��Ԃ��܂�
	float Tan(float radian);

	//���W�A������x�ɕϊ����܂�
	float ToDegree(float radian);

	//�x���烉�W�A���ɕϊ����܂�
	float ToRadian(float degree);
}
#pragma once

namespace mathf
{
	constexpr float PI = 3.14159f;
	constexpr float DEG2RAD = PI / 180.0f;
	constexpr float RAD2DEG = 180.0f / PI;

	//��Βl��Ԃ��܂�
	float abs(float f);

	//Cos���烉�W�A���Ŋp�x��Ԃ��܂�
	float acos(float f);

	//Sin���烉�W�A���Ŋp�x��Ԃ��܂�
	float asin(float f);

	//Tan���烉�W�A���Ŋp�x��Ԃ��܂�
	float atan(float f);

	//���W���烉�W�A���Ŋp�x��Ԃ��܂�
	float atan2(float y, float x);

	//�؂�グ�����l��Ԃ��܂�
	float ceil(float f);

	//�����_��n�ʂ�؂�グ�����l��Ԃ��܂�
	float ceil(float f, unsigned int n);

	//�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l��Ԃ��܂�
	float clamp(float value, float min, float max);

	//�ŏ��l�ƍő�l�͈͓̔��Ɏ��߂��l�𐮐��ŕԂ��܂�
	int clamp(int value, int min, int max);

	//0.0f�`1.0f�͈͓̔��Ɏ��߂��l��Ԃ��܂�
	float clamp01(float f);

	//0.0f�`1.0f�͈͓̔��Ɏ��߂��l�𐮐��ŕԂ��܂�
	int clamp01(int i);

	//Cos��Ԃ��܂�
	float cos(float radian);

	//�x��-180���`180���Ɏ��߂��l��Ԃ��܂�
	float degreeNormalize(float degree);

	//�^�[�Q�b�g�܂ł̊p�x��x�ŕԂ��܂�
	float deltaAngle(float current, float target);

	//�؂�̂Ă����l��Ԃ��܂�
	float floor(float f);

	//�����_��n�ʂ�؂�̂Ă����l��Ԃ��܂�
	float floor(float f, int n);

	//�w�肳�ꂽ�����Ƃ��鐔�l�̑ΐ���Ԃ��܂�
	float log(float x, float base);

	//10���Ƃ��鐔�l�̑ΐ���Ԃ��܂�
	float log10(float x);

	//�^����ꂽ��������傫�����̐���Ԃ��܂�
	float max(float a, float b);

	//�^����ꂽ�������珬�����ق��̐���Ԃ��܂�
	float min(float a, float b);

	//x��y��̒l���v�Z���܂�
	float pow(float x, float y);

	//���W�A����-�΁`�΂Ɏ��߂��l��Ԃ��܂�
	float radianNormalize(float radian);

	//�ŏ��l����ő�l�܂ł͈͓̔��̗�����Ԃ��܂�
	float random(float min, float max);

	//�ŏ��l����ő�l�܂ł͈͓̔��̗����𐮐��ŕԂ��܂�
	int random(int min, int max);

	//�l�̌ܓ������l��Ԃ��܂�
	float round(float f);

	//������n�ʂ��l�̌ܓ������l��Ԃ��܂�
	float round(float f, int num);

	//���l�̐����𒲂ׂĕԂ��܂��i��:1, ��:-1, 0:0�j
	int sign(float f);

	//Sin��Ԃ��܂�
	float sin(float radian);

	//���̕�������Ԃ��܂�
	float sqrt(float f);

	//Tan��Ԃ��܂�
	float tan(float radian);

	//���W�A������x�ɕϊ����܂�
	float toDegree(float radian);

	//�x���烉�W�A���ɕϊ����܂�
	float toRadian(float degree);
}
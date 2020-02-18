#include "Keyboard.h"
#include<Framework/Source/Utility/Judge.h>

Keyboard::Keyboard()
{
	//DirectInput�쐬
	bool result = SUCCEEDED(DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)m_dInput.GetAddressOf(), nullptr));
	assert_msg("DirectInput�쐬���s", result);

	//DirectInputDevice�쐬
	result = SUCCEEDED(m_dInput->CreateDevice(GUID_SysKeyboard, m_keyDevice.GetAddressOf(), nullptr));
	assert_msg("DirectInputDevice�쐬���s", result);

	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	m_keyDevice->SetDataFormat(&c_dfDIKeyboard);
}

Keyboard::Keyboard(HWND hwnd, DWORD dwrd)
{
	//DirectInput�쐬
	bool result = SUCCEEDED(DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)m_dInput.GetAddressOf(), nullptr));
	assert_msg("DirectInput�쐬���s", result);

	//DirectInputDevice�쐬
	result = SUCCEEDED(m_dInput->CreateDevice(GUID_SysKeyboard, m_keyDevice.GetAddressOf(), nullptr));
	assert_msg("DirectInputDevice�쐬���s", result);

	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	m_keyDevice->SetDataFormat(&c_dfDIKeyboard);

	//�������x���̐ݒ�
	m_keyDevice->SetCooperativeLevel(hwnd, dwrd);
}

Keyboard::~Keyboard()
{
}

//void Keyboard::setCooperativeLevel(HWND hwmd, DWORD dword)
//{
//	//�������x���̐ݒ�
//	m_keyDevice->SetCooperativeLevel(hwmd, dword);
//}

void Keyboard::update()
{
	m_keyDevice->Acquire();
	std::memcpy(m_keys, m_currentKeys, sizeof(m_currentKeys));
	m_keyDevice->GetDeviceState(sizeof(m_currentKeys), &m_currentKeys);
}

bool Keyboard::getKey(KeyCode key)
{
	return m_currentKeys[static_cast<unsigned char>(key)] & 0x80;
}

bool Keyboard::keyDown(KeyCode key)
{
	return getKey(key) && !(m_keys[static_cast<unsigned char>(key)] & 0x80);
}

bool Keyboard::keyUp(KeyCode key)
{
	return !getKey(key) && (m_keys[static_cast<unsigned char>(key)] & 0x80);
}

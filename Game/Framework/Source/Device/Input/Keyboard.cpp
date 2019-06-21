#include "Keyboard.h"
#include<Framework/Source/Utility/Judge.h>

Keyboard::Keyboard()
{
	//DirectInput作成
	bool result = SUCCEEDED(DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)m_pDinput.GetAddressOf(), nullptr));
	assert_msg("DirectInput作成失敗", result);

	//DirectInputDevice作成
	result = SUCCEEDED(m_pDinput->CreateDevice(GUID_SysKeyboard, m_pKeyDevice.GetAddressOf(), nullptr));
	assert_msg("DirectInputDevice作成失敗", result);

	//デバイスをキーボードに設定
	m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
}

Keyboard::Keyboard(HWND hwnd, DWORD dwrd)
{
	//DirectInput作成
	bool result = SUCCEEDED(DirectInput8Create(GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)m_pDinput.GetAddressOf(), nullptr));
	assert_msg("DirectInput作成失敗", result);

	//DirectInputDevice作成
	result = SUCCEEDED(m_pDinput->CreateDevice(GUID_SysKeyboard, m_pKeyDevice.GetAddressOf(), nullptr));
	assert_msg("DirectInputDevice作成失敗", result);

	//デバイスをキーボードに設定
	m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);

	//協調レベルの設定
	m_pKeyDevice->SetCooperativeLevel(hwnd, dwrd);
}

Keyboard::~Keyboard()
{
}

//void Keyboard::setCooperativeLevel(HWND hwmd, DWORD dword)
//{
//	//協調レベルの設定
//	m_pKeyDevice->SetCooperativeLevel(hwmd, dword);
//}

void Keyboard::update()
{
	m_pKeyDevice->Acquire();
	std::memcpy(m_Keys, m_CurrentKeys, sizeof(m_CurrentKeys));
	m_pKeyDevice->GetDeviceState(sizeof(m_CurrentKeys), &m_CurrentKeys);
}

bool Keyboard::getKey(KeyCode key)
{
	return m_CurrentKeys[static_cast<unsigned char>(key)] & 0x80;
}

bool Keyboard::keyDown(KeyCode key)
{
	return getKey(key) && !(m_Keys[static_cast<unsigned char>(key)] & 0x80);
}

bool Keyboard::keyUp(KeyCode key)
{
	return !getKey(key) && (m_Keys[static_cast<unsigned char>(key)] & 0x80);
}

#pragma once

#include<memory>
#include"Input/IKeyboard.h"
#include"Sound/IAudio.h"
#include"NullDevice.h"

class DeviceLocator
{
public:
	static IKeyboard& Keyboard() 
	{ 
		if (!m_pKeyboard)return m_NullDevice;
		return *m_pKeyboard.get(); 
	}

	static void ProvideKeyboard(std::unique_ptr<IKeyboard>&& service)
	{
		if (service == nullptr) {
			m_pKeyboard.release();
			return;
		}
		m_pKeyboard = move(service);
	}

	static IAudio& Audio()
	{
		if (!m_pAudio)return m_NullDevice;
		return *m_pAudio.get();
	}

	static void ProvideAudio(std::unique_ptr<IAudio>&& service)
	{
		if (service == nullptr) {
			m_pAudio.release();
			return;
		}
		m_pAudio = move(service);
	}

private:
	static std::unique_ptr<IKeyboard> m_pKeyboard;
	static std::unique_ptr<IAudio> m_pAudio;
	static NullDevice m_NullDevice;
};
#pragma once

#include<memory>
#include"Input/IKeyboard.h"
#include"Sound/IAudio.h"
#include"NullDevice.h"

class DeviceLocator {
public:
    DeviceLocator() = delete;

    static IKeyboard& Keyboard() {
        if (!m_Keyboard) return m_NullDevice;
        return *m_Keyboard.get();
    }

    static void ProvideKeyboard(std::unique_ptr<IKeyboard>&& service) {
        if (service == nullptr) {
            m_Keyboard.release();
            return;
        }
        m_Keyboard = move(service);
    }

    static IAudio& Audio() {
        if (!m_Audio) return m_NullDevice;
        return *m_Audio.get();
    }

    static void ProvideAudio(std::unique_ptr<IAudio>&& service) {
        if (service == nullptr) {
            m_Audio.release();
            return;
        }
        m_Audio = move(service);
    }

private:
    static std::unique_ptr<IKeyboard> m_Keyboard;
    static std::unique_ptr<IAudio> m_Audio;
    static NullDevice m_NullDevice;
};
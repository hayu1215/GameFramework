#include"DeviceLocator.h"

std::unique_ptr<IKeyboard> DeviceLocator::m_Keyboard = nullptr;
std::unique_ptr<IAudio> DeviceLocator::m_Audio = nullptr;
NullDevice DeviceLocator::m_NullDevice = NullDevice();
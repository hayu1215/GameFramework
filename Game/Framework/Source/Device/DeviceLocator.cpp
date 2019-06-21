#include"DeviceLocator.h"

std::unique_ptr<IKeyboard> DeviceLocator::m_pKeyboard = nullptr;
std::unique_ptr<IAudio> DeviceLocator::m_pAudio = nullptr;
NullDevice DeviceLocator::m_NullDevice = NullDevice();
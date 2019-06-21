//#include "XactAudio.h"
//#include<Framework/Source/Utility/Judge.h>
//
//XactAudio::XactAudio()
//{
//	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
//	assert_msg("XACTエンジン作成失敗", 
//		SUCCEEDED(XACT3CreateEngine(XACT_FLAG_API_DEBUG_MODE, m_pEngine.GetAddressOf())));
//
//	XACT_RUNTIME_PARAMETERS params = { 0 };
//	params.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
//	assert_msg("XACTエンジン設定失敗",
//		SUCCEEDED(m_pEngine->Initialize(&params)));
//
//	m_pEngine->DoWork();
//}
//
//XactAudio::~XactAudio()
//{
//	m_pEngine->ShutDown();
//	delete[] m_pSoundBankBuffer;
//	CoUninitialize();
//}
//
//unsigned short XactAudio::load(std::string waveBankName, std::string soundBankFile, const char * cueName)
//{
//	static int iIndex = -1;
//	//waveバンク
//	HANDLE file = CreateFile(waveBankName.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
//	if (file == INVALID_HANDLE_VALUE)return 0;
//	DWORD fileSize = GetFileSize(file, nullptr);
//	HANDLE mapFile = CreateFileMapping(file, nullptr, PAGE_READONLY, 0, fileSize, nullptr);
//	m_pWaveBankBuffer = MapViewOfFile(mapFile, FILE_MAP_READ, 0, 0, 0);
//	if (m_pWaveBankBuffer)m_pEngine->CreateInMemoryWaveBank(m_pWaveBankBuffer, fileSize, 0, 0, &m_pWaveBank);
//
//	//soundバンク
//	file = CreateFile(soundBankFile.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
//	if (file == INVALID_HANDLE_VALUE)return 0;
//	fileSize = GetFileSize(file, nullptr);
//	m_pSoundBankBuffer = new BYTE[fileSize];
//	if (m_pSoundBankBuffer)
//	{
//		DWORD dwBytesRead = 0;
//		ReadFile(file, m_pSoundBankBuffer, fileSize, &dwBytesRead, nullptr);
//		m_pEngine->CreateSoundBank(m_pSoundBankBuffer, fileSize, 0, 0, &m_pSoundBank);
//	}
//	CloseHandle(file);
//
//	iIndex = m_pSoundBank->GetCueIndex(cueName);
//
//	return iIndex;
//}
//
//
////XACTINDEX XactAudio::load(WCHAR * waveBankName, WCHAR * soundBankFile, char * cueName)
////{
////	HANDLE file = CreateFile(waveBankName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
////}
//
//void XactAudio::Play(unsigned short soundIndex)
//{
//	XACT_CUE_PROPERTIES prop;
//	m_pSoundBank->GetCueProperties(soundIndex, &prop);
//	if (prop.currentInstances > 0) return;
//	m_pSoundBank->Play(soundIndex, 0, 0, nullptr);
//}
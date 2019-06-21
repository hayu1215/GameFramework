//#pragma once
////#include<Windows.h>
//#include<xact3.h>
//#include<wrl/client.h>
//#include<string>
//#include"IAudio.h"
////#include<mmsystem.h>
////#include<shellapi.h>
////#include<strsafe.h>
////#include<stdio.h>
//
//using namespace Microsoft::WRL;
//
//class XactAudio :public IAudio
//{
//public:
//	XactAudio();
//	~XactAudio()override;
//
//	unsigned short load(std::string waveBankName, std::string soundBankFile, const char* cueName)override;
//	//XACTINDEX load(WCHAR*waveBankName, WCHAR*soundBankFile, char*cueName);
//	void Play(unsigned short soundIndex)override;
//
//private:
//	XACTINDEX m_SoundIndex;
//	ComPtr<IXACT3Engine> m_pEngine;
//	IXACT3WaveBank* m_pWaveBank;
//	IXACT3SoundBank* m_pSoundBank;
//	void* m_pWaveBankBuffer;
//	void* m_pSoundBankBuffer;
//};
//#pragma once
//#include <xaudio2.h>
//#include<wrl/client.h>
//
//using namespace Microsoft::WRL;
//
//class XAudio 
//{
//public:
//	XAudio();
//	~XAudio();
//
//	int Load(char* fileName);
//	void Play(int index);
//
//private:
//	ComPtr<IXAudio2> m_pXAudio;
//	IXAudio2MasteringVoice* m_pMasteringVoice;
//	IXAudio2SourceVoice* m_pSourceVoice[100];
//	BYTE* m_pWavBuffer[100];
//	DWORD m_dwWavSize[100];
//	int m_SoundIndex;
//};
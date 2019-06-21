//#include "XAudio.h"
//#include<Framework/Source/Utility/Judge.h>
//
//XAudio::XAudio()
//{
//	CoInitializeEx(NULL, COINIT_MULTITHREADED);
//	assert_msg("XAudio作成失敗", 
//		SUCCEEDED(XAudio2Create(m_pXAudio.GetAddressOf(), XAUDIO2_DEBUG_ENGINE)));
//
//	assert_msg("MasteringVoice作成失敗",
//		SUCCEEDED(m_pXAudio->CreateMasteringVoice(&m_pMasteringVoice)));
//}
//
//XAudio::~XAudio()
//{
//	delete[] m_pWavBuffer;
//}
//
//int XAudio::Load(char * fileName)
//{
//	static int iIndex = -1;
//	iIndex++;
//	HMMIO hMmio = NULL;//WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
//	DWORD dwWavSize = 0;//WAVファイル内　WAVデータのサイズ（WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一）
//	WAVEFORMATEX* pwfex;//WAVのフォーマット 例）16ビット、44100Hz、ステレオなど
//	MMCKINFO ckInfo;//　チャンク情報
//	MMCKINFO riffckInfo;// 最上部チャンク（RIFFチャンク）保存用
//	PCMWAVEFORMAT pcmWaveForm;
//	//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
//	hMmio = mmioOpenA(fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
//	//ファイルポインタをRIFFチャンクの先頭にセットする
//	mmioDescend(hMmio, &riffckInfo, NULL, 0);
//	// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
//	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
//	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
//	//フォーマットを読み込む
//	mmioRead(hMmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
//	pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
//	memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
//	pwfex->cbSize = 0;
//	mmioAscend(hMmio, &ckInfo, 0);
//	// WAVファイル内の音データの読み込み	
//	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
//	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);//データチャンクにセット
//	dwWavSize = ckInfo.cksize;
//	m_pWavBuffer[iIndex] = new BYTE[dwWavSize];
//	DWORD dwOffset = ckInfo.dwDataOffset;
//	mmioRead(hMmio, (HPSTR)m_pWavBuffer[iIndex], dwWavSize);
//	//ソースボイスにデータを詰め込む	
//	if (FAILED(m_pXAudio->CreateSourceVoice(&m_pSourceVoice[iIndex], pwfex)))
//	{
//		//MessageBox(0, L"ソースボイス作成失敗", 0, MB_OK);
//		return E_FAIL;
//	}
//	m_dwWavSize[iIndex] = dwWavSize;
//
//	return iIndex;
//}
//
//void XAudio::Play(int index)
//{
//	XAUDIO2_BUFFER buffer = { 0 };
//	buffer.pAudioData = m_pWavBuffer[index];
//	buffer.Flags = XAUDIO2_END_OF_STREAM;
//	buffer.AudioBytes = m_dwWavSize[index];
//	if (FAILED(m_pSourceVoice[index]->SubmitSourceBuffer(&buffer)))
//	{
//		//MessageBox(0, L"ソースボイスにサブミット失敗", 0, MB_OK);
//		return;
//	}
//
//	m_pSourceVoice[index]->Start(0, XAUDIO2_COMMIT_NOW);
//}

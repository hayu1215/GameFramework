//#include "XAudio.h"
//#include<Framework/Source/Utility/Judge.h>
//
//XAudio::XAudio()
//{
//	CoInitializeEx(NULL, COINIT_MULTITHREADED);
//	assert_msg("XAudio�쐬���s", 
//		SUCCEEDED(XAudio2Create(m_pXAudio.GetAddressOf(), XAUDIO2_DEBUG_ENGINE)));
//
//	assert_msg("MasteringVoice�쐬���s",
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
//	HMMIO hMmio = NULL;//Windows�}���`���f�B�AAPI�̃n���h��(Windows�}���`���f�B�AAPI��WAV�t�@�C���֌W�̑���p��API)
//	DWORD dwWavSize = 0;//WAV�t�@�C�����@WAV�f�[�^�̃T�C�Y�iWAV�t�@�C����WAV�f�[�^�Ő�߂��Ă���̂ŁA�قڃt�@�C���T�C�Y�Ɠ���j
//	WAVEFORMATEX* pwfex;//WAV�̃t�H�[�}�b�g ��j16�r�b�g�A44100Hz�A�X�e���I�Ȃ�
//	MMCKINFO ckInfo;//�@�`�����N���
//	MMCKINFO riffckInfo;// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
//	PCMWAVEFORMAT pcmWaveForm;
//	//WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
//	hMmio = mmioOpenA(fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
//	//�t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
//	mmioDescend(hMmio, &riffckInfo, NULL, 0);
//	// �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g����
//	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
//	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
//	//�t�H�[�}�b�g��ǂݍ���
//	mmioRead(hMmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
//	pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
//	memcpy(pwfex, &pcmWaveForm, sizeof(pcmWaveForm));
//	pwfex->cbSize = 0;
//	mmioAscend(hMmio, &ckInfo, 0);
//	// WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
//	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
//	mmioDescend(hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);//�f�[�^�`�����N�ɃZ�b�g
//	dwWavSize = ckInfo.cksize;
//	m_pWavBuffer[iIndex] = new BYTE[dwWavSize];
//	DWORD dwOffset = ckInfo.dwDataOffset;
//	mmioRead(hMmio, (HPSTR)m_pWavBuffer[iIndex], dwWavSize);
//	//�\�[�X�{�C�X�Ƀf�[�^���l�ߍ���	
//	if (FAILED(m_pXAudio->CreateSourceVoice(&m_pSourceVoice[iIndex], pwfex)))
//	{
//		//MessageBox(0, L"�\�[�X�{�C�X�쐬���s", 0, MB_OK);
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
//		//MessageBox(0, L"�\�[�X�{�C�X�ɃT�u�~�b�g���s", 0, MB_OK);
//		return;
//	}
//
//	m_pSourceVoice[index]->Start(0, XAUDIO2_COMMIT_NOW);
//}

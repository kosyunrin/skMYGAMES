#include "engine.h"
#include "sound.h"

IXAudio2* Sound::xAudio;
IXAudio2MasteringVoice* Sound::masterVoice;

void Sound::Initialize()
{
	HRESULT hr;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	XAudio2Create(&xAudio, 0);
	xAudio->CreateMasteringVoice(&masterVoice);
}

void Sound::Finalize()
{
	masterVoice->DestroyVoice();
	xAudio->Release();

	CoUninitialize();
}

void Sound::Load(const char *FileName)
{
	WAVEFORMATEX wfx = { 0 };
	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;

		hmmio = mmioOpenA((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);


		buflen = datachunkinfo.cksize;
		soundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)soundData, buflen);

		length = readlen;
		playLength = readlen / wfx.nBlockAlign;

		mmioClose(hmmio, 0);
	}

	//Generate Sound
	for (int index = 0; index < SOUNDMAX; index++)
	{
		xAudio->CreateSourceVoice(&sourceVoice[index], &wfx);
	}
}

void Sound::Unload()
{

	for (int index = 0; index < SOUNDMAX; index++)
	{
		if (sourceVoice[index])
		{
			sourceVoice[index]->Stop();
			sourceVoice[index]->DestroyVoice();
			sourceVoice[index] = NULL;
		}
	}
	if (soundData)
	{
		delete[] soundData;
		soundData = nullptr;
	}
}

void Sound::Play(bool loop)
{
	for( int index = 0; index < SOUNDMAX; index++ )
	{
		XAUDIO2_VOICE_STATE state;

		sourceVoice[index]->GetState( &state );

		if( state.BuffersQueued == 0 )
		{
			//Sound->SourceVoice->Stop();
			//Sound->SourceVoice->FlushSourceBuffers();

			XAUDIO2_BUFFER bufinfo;

			memset(&bufinfo,0x00,sizeof(bufinfo));
			bufinfo.AudioBytes = length;
			bufinfo.pAudioData = soundData;
			bufinfo.PlayBegin = 0;
			bufinfo.PlayLength = playLength;

			if(loop)
			{
				bufinfo.LoopBegin = 0;
				bufinfo.LoopLength = playLength;
				bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
			}
			sourceVoice[index]->SubmitSourceBuffer( &bufinfo, NULL );
			sourceVoice[index]->Start();

			break;
		}
	}
}

void Sound::Stop()
{
	for (int index = 0; index < SOUNDMAX; index++)
	{
		sourceVoice[index]->Stop();
	}
}

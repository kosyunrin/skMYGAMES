#pragma once
#include <xaudio2.h>

#define SOUNDMAX 5

class Sound
{
private:
	static IXAudio2* xAudio;
	static IXAudio2MasteringVoice* masterVoice;

	IXAudio2SourceVoice* sourceVoice[SOUNDMAX];
	BYTE* soundData;

	UINT length;
	UINT playLength;

public:
	static void Initialize();
	static void Finalize();

	void Load(const char *FileName);
	void Unload();
	void Play(bool loop);
	void Stop();
};

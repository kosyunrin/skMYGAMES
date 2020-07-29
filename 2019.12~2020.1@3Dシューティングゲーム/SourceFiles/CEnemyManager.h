#pragma once
#include"main.h"
#include"CObjManager.h"
#include"audio_clip.h"
#define Zombie_Sound (sizeof(SOUNDMAX)/sizeof(SOUNDMAX[0]))
#define TEXTURE (64)


struct sMUSIC
{
	const char name[TEXTURE];
};
static sMUSIC SOUNDMAX[]
{
	"asset/Music/ZBCXian.wav",
	"asset/Music/zombieAttack.wav",
	"asset/Music/zombiedie.wav",
	"asset/Music/stopAttack.wav"

};

class Music : public MusicBasic
{
public:
	Music()
	{
		Init();
	}
	~Music()
	{
		for (int i = 0; i < Zombie_Sound; i++)
		{
			Sounds[i]->Unload();
		}
	}
	virtual void Init()override
	{
		for (int i = 0; i < Zombie_Sound; i++)
		{
			Sounds[i] = std::make_unique<CAudioClip>();
			Sounds[i]->Load(SOUNDMAX[i].name);
			Sounds[i]->Play(true);
			Sounds[i]->Stop();
		}
	}
	virtual void Start(MusicPattern num)override
	{
		int x = int(num);
		switch (num)
		{
		case MusicPattern::Sound_Stop:
			break;
		case MusicPattern::Sound_Barrking:
			Sounds[x]->Start();
			break;
		case MusicPattern::Sound_Attack:
			Sounds[x]->Start();
			break;
		case MusicPattern::Sound_die:
			Sounds[x]->Start();
			break;
		case MusicPattern::Sound_StopAttack:
			Sounds[x]->Start();
			break;
		default:
			break;
		}
	}
	virtual void Stop(MusicPattern num)override
	{
		int x = int(num);
		switch (num)
		{
		case MusicPattern::Sound_Stop:
			for (int i = 0; i < Zombie_Sound; i++)
			{
				Sounds[i]->Stop();
			}
			break;
		case MusicPattern::Sound_Barrking:
			Sounds[x]->Stop();
			break;
		case MusicPattern::Sound_Attack:
			Sounds[x]->Stop();
			break;
		case MusicPattern::Sound_die:
			Sounds[x]->Stop();
			break;
		case MusicPattern::Sound_StopAttack:
			Sounds[x]->Stop();
			break;
		default:
			break;
		}
	}
private:
	std::unique_ptr<CAudioClip> Sounds[Zombie_Sound];
};

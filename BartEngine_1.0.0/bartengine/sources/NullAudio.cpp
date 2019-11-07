#include <NullAudio.h>

bool bart::NullAudio::Initialize()
{
    return true;
}

void bart::NullAudio::Clean()
{
}

unsigned bart::NullAudio::LoadSound(const std::string& aFilename)
{
    return 0;
}

void bart::NullAudio::UnloadMusic(unsigned aMusic)
{
}

void bart::NullAudio::UnloadSound(unsigned aSound)
{
}

unsigned bart::NullAudio::LoadMusic(const std::string& aFilename)
{
    return 0;
}

void bart::NullAudio::PlaySFX(unsigned aSound, int aLoop)
{
}

void bart::NullAudio::PlayMusic(unsigned aMusic, int aLoop)
{
}

void bart::NullAudio::PauseMusic(unsigned aMusic)
{
}

void bart::NullAudio::StopMusic(unsigned aMusic)
{
}

void bart::NullAudio::ResumeMusic(unsigned aMusic)
{
}

void bart::NullAudio::SetMusicVolume(unsigned aMusic, int aVolume)
{
}

int bart::NullAudio::GetSoundInCache() const
{
    return 0;
}

int bart::NullAudio::GetMusicInCache() const
{
    return 0;
}

#include <NullAudio.h>

bool bart::NullAudio::Initialize()
{
    return true;
}

void bart::NullAudio::Clean()
{
}

size_t bart::NullAudio::LoadSound(const std::string& /*aFilename*/)
{
    return 0;
}

void bart::NullAudio::UnloadMusic(size_t /*aMusic*/)
{
}

void bart::NullAudio::UnloadSound(size_t /*aSound*/)
{
}

size_t bart::NullAudio::LoadMusic(const std::string& /*aFilename*/)
{
    return 0;
}

void bart::NullAudio::PlaySFX(size_t /*aSound*/, int /*aLoop*/)
{
}

void bart::NullAudio::PlayMusic(size_t /*aMusic*/, int /*aLoop*/)
{
}

void bart::NullAudio::PauseMusic()
{
}

void bart::NullAudio::StopMusic()
{
}

void bart::NullAudio::ResumeMusic()
{
}

void bart::NullAudio::SetMusicVolume(int /*aVolume*/)
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

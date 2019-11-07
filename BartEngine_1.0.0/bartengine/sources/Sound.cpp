#include <Sound.h>
#include <Engine.h>

void bart::Sound::Load(const std::string& aFile)
{
    m_SoundId = Engine::Instance().GetAudio().LoadSound(aFile);
}

void bart::Sound::Play(int aLoop) const
{
    Engine::Instance().GetAudio().PlaySFX(m_SoundId, aLoop);
}

void bart::Sound::Unload()
{
    Engine::Instance().GetAudio().UnloadSound(m_SoundId);
}

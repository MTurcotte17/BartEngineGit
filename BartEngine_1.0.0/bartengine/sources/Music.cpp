#include <Music.h>
#include <Engine.h>

void bart::Music::Load(const std::string& aFile)
{
    m_MusicId = Engine::Instance().GetAudio().LoadMusic(aFile);
}

void bart::Music::Play(int aLoop) const
{
    Engine::Instance().GetAudio().PlayMusic(m_MusicId, aLoop);
}

void bart::Music::Pause() const
{
    Engine::Instance().GetAudio().PauseMusic(m_MusicId);
}

void bart::Music::Stop() const
{
    Engine::Instance().GetAudio().StopMusic(m_MusicId);
}

void bart::Music::Resume() const
{
    Engine::Instance().GetAudio().ResumeMusic(m_MusicId);
}

void bart::Music::SetVolumne(int aVolume)
{
    Engine::Instance().GetAudio().SetMusicVolume(m_MusicId, aVolume);
}

void bart::Music::Unload()
{
    Engine::Instance().GetAudio().UnloadMusic(m_MusicId);
}

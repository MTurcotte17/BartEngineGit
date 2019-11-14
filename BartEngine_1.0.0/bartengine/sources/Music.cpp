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
    Engine::Instance().GetAudio().PauseMusic();
}

void bart::Music::Stop() const
{
    Engine::Instance().GetAudio().StopMusic();
}

void bart::Music::Resume() const
{
    Engine::Instance().GetAudio().ResumeMusic();
}

void bart::Music::SetVolumne(const int aVolume) const
{
    Engine::Instance().GetAudio().SetMusicVolume(aVolume);
}

void bart::Music::Unload()
{
    Engine::Instance().GetAudio().UnloadMusic(m_MusicId);
}

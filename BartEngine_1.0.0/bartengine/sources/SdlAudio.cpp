#include <SdlAudio.h>
#include <HashKey.h>
#include <SDL_mixer.h>
#include <Engine.h>

bool bart::SdlAudio::Initialize()
{
    if (Mix_OpenAudio(22050, AUDIO_S16, 2, 2048) != 0)
    {
        Engine::Instance().GetLogger().Log("Cannot initialize audio mixer\n");
        return false;
    }

    return true;
}

void bart::SdlAudio::Clean()
{
    Mix_CloseAudio();
}

unsigned bart::SdlAudio::LoadSound(const std::string& aFilename)
{
    const unsigned tHashValue = HashKey::Generate(aFilename.c_str());
    if (m_SndCache.count(tHashValue) > 0)
    {
        m_SndCache[tHashValue]->Count++;
        return tHashValue;
    }

    Mix_Chunk* pChunk = Mix_LoadWAV(aFilename.c_str());
    if (pChunk == nullptr)
    {
        const char* tError = Mix_GetError();
        Engine::Instance().GetLogger().Log("%s\n", tError);
        return 0;
    }

    m_SndCache[tHashValue] = new Resource<struct Mix_Chunk>();
    m_SndCache[tHashValue]->Data = pChunk;
    m_SndCache[tHashValue]->Count = 1;

    return tHashValue;
}

void bart::SdlAudio::UnloadMusic(unsigned aMusic)
{
    if (m_MusCache.count(aMusic) > 0)
    {
        m_MusCache[aMusic]->Count--;
        if (m_MusCache[aMusic]->Count <= 0)
        {
            Mix_HaltMusic();
            delete m_MusCache[aMusic];
            m_MusCache.erase(aMusic);
        }
    }
}

void bart::SdlAudio::UnloadSound(unsigned aSound)
{
    if (m_SndCache.count(aSound) > 0)
    {
        m_SndCache[aSound]->Count--;
        if (m_SndCache[aSound]->Count <= 0)
        {
            delete m_SndCache[aSound];
            m_SndCache.erase(aSound);
        }
    }
}

unsigned bart::SdlAudio::LoadMusic(const std::string& aFilename)
{
    const unsigned int tHashValue = HashKey::Generate(aFilename.c_str());
    if (m_MusCache.count(tHashValue) > 0)
    {
        m_MusCache[tHashValue]->Count++;
        return tHashValue;
    }

    Mix_Music* pMusic = Mix_LoadMUS(aFilename.c_str());
    if (pMusic == nullptr)
    {
        const char* tError = Mix_GetError();
        Engine::Instance().GetLogger().Log("%s\n", tError);
        return 0;
    }

    m_MusCache[tHashValue] = new Resource<struct _Mix_Music>();
    m_MusCache[tHashValue]->Data = pMusic;
    m_MusCache[tHashValue]->Count = 1;

    return tHashValue;
}

void bart::SdlAudio::PlaySFX(const unsigned aSound, const int aLoop)
{
    Mix_PlayChannel(-1, m_SndCache[aSound]->Data, aLoop);
}

void bart::SdlAudio::PlayMusic(const unsigned aMusic, const int aLoop)
{
    Mix_PlayMusic(m_MusCache[aMusic]->Data, aLoop);
}

void bart::SdlAudio::PauseMusic(unsigned aMusic)
{
    Mix_PauseMusic();
}

void bart::SdlAudio::StopMusic(unsigned aMusic)
{
    Mix_HaltMusic();
}

void bart::SdlAudio::ResumeMusic(unsigned aMusic)
{
    Mix_ResumeMusic();
}

void bart::SdlAudio::SetMusicVolume(unsigned aMusic, int aVolume)
{
    Mix_VolumeMusic(aVolume);
}

int bart::SdlAudio::GetSoundInCache() const
{
    return static_cast<int>(m_SndCache.size());
}

int bart::SdlAudio::GetMusicInCache() const
{
    return static_cast<int>(m_MusCache.size());
}

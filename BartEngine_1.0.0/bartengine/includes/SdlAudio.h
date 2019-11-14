#ifndef BART_SDL_AUDIO_H
#define BART_SDL_AUDIO_H

#include <string>
#include <IAudio.h>
#include <map>
#include <Resource.h>

struct Mix_Chunk;
struct _Mix_Music;

namespace bart
{
    class SdlAudio final : public IAudio
    {
    public:
        virtual ~SdlAudio() = default;

        bool Initialize() override;
        void Clean() override;

        size_t LoadSound(const std::string& aFilename) override;
        void UnloadMusic(size_t aMusic) override;
        size_t LoadMusic(const std::string& aFilename) override;
        void UnloadSound(size_t aSound) override;

        void PlaySFX(size_t aSound, int aLoop) override;
        void PlayMusic(size_t aMusic, int aLoop) override;
        void PauseMusic() override;
        void StopMusic() override;
        void ResumeMusic() override;
        void SetMusicVolume(int aVolume) override;

        int GetSoundInCache() const override;
        int GetMusicInCache() const override;

    private:
        typedef std::map<size_t, Resource<Mix_Chunk>*> TChunkMap;
        typedef std::map<size_t, Resource<_Mix_Music>*> TMusicMap;

        TChunkMap m_SndCache;
        TMusicMap m_MusCache;
    };
}

#endif

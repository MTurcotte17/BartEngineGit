#ifndef BART_SDL_AUDIO_H
#define BART_SDL_AUDIO_H

#include <string>
#include <IAudio.h>
#include <map>
#include "Resource.h"

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

        unsigned LoadSound(const std::string& aFilename) override;
        void UnloadMusic(unsigned aMusic) override;
        unsigned LoadMusic(const std::string& aFilename) override;
        void UnloadSound(unsigned aSound) override;

        void PlaySFX(unsigned aSound, int aLoop) override;
        void PlayMusic(unsigned aMusic, int aLoop) override;
        void PauseMusic(unsigned aMusic) override;
        void StopMusic(unsigned aMusic) override;
        void ResumeMusic(unsigned aMusic) override;
        void SetMusicVolume(unsigned aMusic, int aVolume) override;

        int GetSoundInCache() const override;
        int GetMusicInCache() const override;

    private:
        typedef std::map<unsigned, Resource<Mix_Chunk>*> TChunkMap;
        typedef std::map<unsigned, Resource<_Mix_Music>*> TMusicMap;

        TChunkMap m_SndCache;
        TMusicMap m_MusCache;
    };
}

#endif

#ifndef BART_NULL_AUDIO_H
#define BART_NULL_AUDIO_H

#include <string>
#include <IAudio.h>

namespace bart
{
    class NullAudio final : public IAudio
    {
    public:
        virtual ~NullAudio() = default;

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
    };
}

#endif

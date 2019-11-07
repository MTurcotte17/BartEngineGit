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
    };
}

#endif

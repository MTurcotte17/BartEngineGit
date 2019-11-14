#ifndef BART_IAUDIO_H
#define BART_IAUDIO_H

#include <string>
#include <IService.h>

namespace bart
{
    class IAudio : public IService
    {
    public:
        virtual ~IAudio() = default;

        virtual size_t LoadMusic(const std::string& aFilename) = 0;
        virtual void UnloadMusic(size_t aMusic) = 0;
        virtual size_t LoadSound(const std::string& aFilename) = 0;
        virtual void UnloadSound(size_t aSound) = 0;

        virtual void PlayMusic(size_t aMusic, int aLoop) = 0;
        virtual void PlaySFX(size_t aSound, int aLoop) = 0;
        virtual void PauseMusic() = 0;
        virtual void StopMusic() = 0;
        virtual void ResumeMusic() = 0;
        virtual void SetMusicVolume(int aVolume) = 0;

        virtual int GetSoundInCache() const = 0;
        virtual int GetMusicInCache() const = 0;
    };
}

#endif

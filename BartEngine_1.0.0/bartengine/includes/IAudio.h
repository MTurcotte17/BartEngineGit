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

        virtual unsigned LoadMusic(const std::string& aFilename) = 0;
        virtual void UnloadMusic(unsigned aMusic) = 0;
        virtual unsigned LoadSound(const std::string& aFilename) = 0;
        virtual void UnloadSound(unsigned aSound) = 0;

        virtual void PlayMusic(unsigned aMusic, int aLoop) = 0;
        virtual void PlaySFX(unsigned aSound, int aLoop) = 0;
        virtual void PauseMusic(unsigned aMusic) = 0;
        virtual void StopMusic(unsigned aMusic) = 0;
        virtual void ResumeMusic(unsigned aMusic) = 0;
        virtual void SetMusicVolume(unsigned aMusic, int aVolume) = 0;

        virtual int GetSoundInCache() const = 0;
        virtual int GetMusicInCache() const = 0;
    };
}

#endif

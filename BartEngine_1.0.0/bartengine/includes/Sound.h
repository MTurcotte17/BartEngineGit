#ifndef BART_SOUND_H
#define BART_SOUND_H

#include <Component.h>
#include <string>

namespace bart
{
    class IAudio;

    class Sound final : public Component
    {
    public:
        virtual ~Sound() = default;
        void Load(const std::string& aFile);
        void Play(int aLoop) const;
        void Unload();

    private:
        size_t m_SoundId{0};
    };
}

#endif

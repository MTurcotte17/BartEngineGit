#ifndef BART_MUSIC_H
#define BART_MUSIC_H

#include <Component.h>
#include <string>

namespace bart
{
    class IAudio;

    class Music final : public Component
    {
    public:
        virtual ~Music() = default;
        void Load(const std::string& aFile);
        void Play(int aLoop) const;
        void Pause() const;
        void Stop() const;
        void Resume() const;
        void SetVolumne(int aVolume) const;
        void Unload();

    private:
        size_t m_MusicId{0};
    };
}

#endif

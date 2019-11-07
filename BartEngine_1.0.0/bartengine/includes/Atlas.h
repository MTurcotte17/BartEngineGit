#ifndef BART_ATLAS_H
#define BART_ATLAS_H

#include <Sprite.h>
#include <map>

using namespace std;

namespace bart
{
    class Atlas : public Sprite
    {
    public:
        virtual ~Atlas() = default;

        void AddFrame(const std::string& aName, int aX, int aY, int aWidth, int aHeight);
        void SetFrame(const std::string& aName);

    private:
        typedef map<string, Rectangle> TFrameMap;
        TFrameMap m_Frames;
    };
}

#endif

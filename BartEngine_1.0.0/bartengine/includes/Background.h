#ifndef BART_BACKGROUND_H
#define BART_BACKGROUND_H

#include <string>
#include <Rectangle.h>
#include <GraphicComponent.h>

using namespace std;

namespace bart
{
    class Background : public Component
    {
    public:
        virtual ~Background() = default;

        void Load(const std::string& aFilename);
        void Draw();
        void ScrollX(IGraphic& aGraphic, float aSpeed);
        void ScrollY(IGraphic& aGraphic, float aSpeed);
        void Scroll(bool aHorizontal, float aSpeed);
        void Unload();

    protected:
        unsigned mTexId{0};
        Rectangle m_DestinationA{};
        Rectangle m_DestinationB{};
        Rectangle m_SourceA{};
        Rectangle m_SourceB{};
    };
}

#endif

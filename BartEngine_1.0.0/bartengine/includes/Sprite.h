#ifndef BART_SPRITE_H
#define BART_SPRITE_H

#include <string>
#include <Rectangle.h>
#include <GraphicComponent.h>

using namespace std;

namespace bart
{
    class Sprite : public GraphicComponent
    {
    public:
        virtual ~Sprite() = default;

        void Load(const std::string& aFilename) override;
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        void Unload();

    protected:
        size_t mTexId{0};
        Rectangle m_Destination{};
        Rectangle m_Source{};
        float m_Angle{0.0f};
        bool m_HorizontalFlip{false};
        bool m_VerticalFlip{false};
        unsigned char m_Alpha{255};
    };
}

#endif

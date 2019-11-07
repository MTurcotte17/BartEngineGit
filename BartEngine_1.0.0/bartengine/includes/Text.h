#ifndef BART_TEXT_H
#define BART_TEXT_H

#include <GraphicComponent.h>

namespace bart
{
    class Text final : public GraphicComponent
    {
    public:
        virtual ~Text() = default;

        void Load(const string& aFontFile, int aFontSize);
        void Load(const string& aFontFile) override;
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;

        std::string GetText() const { return m_Text; }
        void SetText(const std::string& aText) { m_Text = aText; }

        void Unload();

    private:
        std::string m_Text;
        unsigned m_FontId{0};
        int m_X{0};
        int m_Y{0};
    };
}

#endif

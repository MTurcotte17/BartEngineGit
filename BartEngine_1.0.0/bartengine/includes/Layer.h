#ifndef BART_LAYER
#define BART_LAYER

#include <TiledProperty.h>
#include <Rectangle.h>

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void Draw(const Rectangle& aViewport) = 0;

        virtual void Clean() = 0;

        std::string GetName() const { return m_Name; }
        bool IsVisible() const { return m_Visible; }
        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        int GetAlpha() const { return m_Alpha; }
        float GetHorizontalOffset() const { return m_HorizontalOffset; }
        float GetVerticalOffset() const { return m_VerticalOffset; }
        void ClearProperties();
        bool GetBoolProperty(const std::string& aName);
        Color GetColorProperty(const std::string& aName);
        float GetFloatProperty(const std::string& aName);
        std::string GetStringProperty(const std::string& aName);
        int GetIntProperty(const std::string& aName);

    protected:
        void LoadCustomProperties(XMLNode* aNode);
        void LoadLayerProperties(XMLNode* aNode);

        std::string m_Name;
        bool m_Visible{false};
        int m_Width{0};
        int m_Height{0};
        unsigned char m_Alpha{255};
        float m_HorizontalOffset{0.0f};
        float m_VerticalOffset{0.0f};
        TiledProperties m_Properties;
    };
}
#endif

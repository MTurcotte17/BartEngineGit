#include <ImageLayer.h>
#include <tinyxml2.h>

bool bart::ImageLayer::Load(XMLNode* aNode, const std::string& aAssetPath)
{
    LoadLayerProperties(aNode);
    ClearProperties();

    XMLNode* tNext = aNode->FirstChild();
    while (tNext != nullptr)
    {
        std::string tNextValue = tNext->Value();
        if (tNextValue == "image")
        {
            XMLElement* tSourceElement = tNext->ToElement();
            if (tSourceElement != nullptr)
            {
                const char* tSource = tSourceElement->Attribute("source");
                if (tSource != nullptr)
                {
                    const std::string tFilename = aAssetPath + std::string(tSource);
                    const int tWidth = tSourceElement->IntAttribute("width");
                    const int tHeight = tSourceElement->IntAttribute("height");

                    m_Source.Set(0, 0, tWidth, tHeight);
                    m_Destination.Set(
                        static_cast<int>(m_HorizontalOffset),
                        static_cast<int>(m_VerticalOffset), tWidth, tHeight);
                    m_TextureId = Engine::Instance().GetGraphic().LoadTexture(tFilename);
                }
            }
        }
        else if (tNextValue == "properties")
        {
            LoadCustomProperties(tNext);
        }

        tNext = tNext->NextSibling();
    }

    return true;
}

void bart::ImageLayer::Draw(int aFromX, int aFromY, int aToX, int aToY, int aWidth, int aHeight)
{
    if (m_Visible && m_TextureId > 0)
    {
        Engine::Instance().GetGraphic().Draw(m_TextureId, m_Source, m_Destination, 0.0f, false, m_Alpha);
    }
}

void bart::ImageLayer::Clean()
{
    Engine::Instance().GetGraphic().UnloadTexture(m_TextureId);
}

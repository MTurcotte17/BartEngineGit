#include <TileLayer.h>
#include <Engine.h>
#include <sstream>
#include <tinyxml2.h>

bool bart::TileLayer::Load(XMLNode* aNode, Tileset* aTileset)
{
    LoadLayerProperties(aNode);
    ClearProperties();

    XMLNode* tNext = aNode->FirstChild();
    while (tNext != nullptr)
    {
        std::string tNextValue = tNext->Value();
        if (tNextValue == "data")
        {
            XMLElement* tDataElement = tNext->ToElement();
            const char* tEncoding = tDataElement->Attribute("encoding");

            if (tEncoding == nullptr || strcmp(tEncoding, "csv") != 0)
            {
                Engine::Instance().GetLogger().Log("Only CSV encoding is supported\n");
                return false;
            }

            const char* tData = tDataElement->GetText();
            SetData(tData, m_Width);
        }
        else if (tNextValue == "properties")
        {
            LoadCustomProperties(tNext);
        }

        tNext = tNext->NextSibling();
    }

    m_TilesetPtr = aTileset;

    return true;
}

void bart::TileLayer::Draw(const int aFromX,
                           const int aFromY,
                           const int aToX,
                           const int aToY,
                           const int aWidth,
                           const int aHeight)
{
    if (m_Visible)
    {
        if (aFromX < aToX && aFromY < aToY)
        {
            IGraphic& tGraphic = Engine::Instance().GetGraphic();

            Rectangle tDest;
            Rectangle tSrc;

            int tIndex = 0;
            int tY = 0;

            const size_t tDataSize = mLayerData.size();
            if (tDataSize > 0)
            {
                for (int y = aFromY; y < aToY; y++)
                {
                    tY = y * aHeight;
                    for (int x = aFromX; x < aToX; x++)
                    {
                        tIndex = mLayerData[y][x];
                        if (tIndex > 0)
                        {
                            m_TilesetPtr->GetTile(tIndex, &tSrc.X, &tSrc.Y, &tSrc.W, &tSrc.H);

                            tDest.X = x * aWidth + static_cast<int>(m_HorizontalOffset);
                            tDest.Y = tY + static_cast<int>(m_VerticalOffset);
                            tDest.W = tSrc.W;
                            tDest.H = tSrc.H;

                            tGraphic.Draw(m_TilesetPtr->GetTextureId(), tSrc, tDest, 0, false, m_Alpha);
                        }
                    }
                }
            }
        }
    }
}

void bart::TileLayer::SetData(const char* aData, const int aWidth)
{
    std::string tCurrentToken;
    std::istringstream tStringStream(aData);

    int tX = 0;
    int tY = 0;

    mLayerData.push_back(std::vector<int>(aWidth));

    while (std::getline(tStringStream, tCurrentToken, ','))
    {
        mLayerData[tY][tX] = std::stoi(tCurrentToken);

        tX++;

        if (tX > aWidth - 1)
        {
            tX = 0;
            tY++;

            mLayerData.push_back(std::vector<int>(aWidth));
        }
    }
}

void bart::TileLayer::Clean()
{
    mLayerData.clear();
}

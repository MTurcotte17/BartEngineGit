#include <Tileset.h>
#include <tinyxml2.h>
#include <string>
#include <Engine.h>
#include <StringHelper.h>

using namespace tinyxml2;
using namespace std;

bool bart::Tileset::Load(XMLNode* aNode, const std::string& aAssetPath)
{
    XMLDocument tDoc;
    XMLElement* tTileElement = nullptr;
    XMLNode* tImageNode = aNode->FirstChild();

    m_FirstIndex = aNode->ToElement()->IntAttribute("firstgid");

    if (tImageNode != nullptr)
    {
        tTileElement = aNode->ToElement();
    }
    else
    {
        const std::string tFileName = aAssetPath + aNode->ToElement()->Attribute("source");
        if (tDoc.LoadFile(tFileName.c_str()) == XML_SUCCESS)
        {
            tTileElement = tDoc.FirstChild()->NextSibling()->ToElement();
        }
    }

    if (tTileElement != nullptr)
    {
        m_Name = tTileElement->Attribute("name");
        m_Columns = tTileElement->IntAttribute("columns");
        m_TileWidth = tTileElement->IntAttribute("tilewidth");
        m_TileHeight = tTileElement->IntAttribute("tileheight");
        m_TileCount = tTileElement->IntAttribute("tilecount");

        XMLNode* tNext = tTileElement->FirstChild();

        while (tNext != nullptr)
        {
            std::string tNextValue = tNext->Value();
            if (tNextValue == "image")
            {
                XMLElement* tAtlasElement = tNext->ToElement();

                const char* tFilepath = tAtlasElement->Attribute("source");
                if (tFilepath == nullptr)
                {
                    Engine::Instance().GetLogger().Log("Cannot load tileset image\n");
                    return false;
                }

                std::string tImagePath = aAssetPath + std::string(tFilepath);
                m_ImageWidth = tAtlasElement->IntAttribute("width");
                m_ImageHeight = tAtlasElement->IntAttribute("height");
                m_TextureId = Engine::Instance().GetGraphic().LoadTexture(tImagePath);

                if (m_TextureId > 0)
                {
                    int tTileNumber = m_FirstIndex;
                    int tY = 0;
                    int tX = 0;

                    for (int i = 0; i < m_TileCount; i++, tTileNumber++)
                    {
                        tY = i / m_Columns;
                        tX = i - (tY * m_Columns);
                        m_SourceMap[tTileNumber] = new Rectangle();
                        m_SourceMap[tTileNumber]->Set(tX * m_TileWidth, tY * m_TileHeight, m_TileWidth, m_TileHeight);
                    }
                }
            }

            tNext = tNext->NextSibling();
        }

        return true;
    }

    Engine::Instance().GetLogger().Log("Couldn't load tileset\n");
    return false;
}

void bart::Tileset::GetTile(const int aIndex, int* aX, int* aY, int* aWidth, int* aHeight)
{
    *aX = m_SourceMap[aIndex]->X;
    *aY = m_SourceMap[aIndex]->Y;
    *aWidth = m_SourceMap[aIndex]->W;
    *aHeight = m_SourceMap[aIndex]->H;
}

void bart::Tileset::Clean()
{
    for (TRectangleMap::iterator i = m_SourceMap.begin(); i != m_SourceMap.end(); ++i)
    {
        delete i->second;
    }

    m_SourceMap.clear();
    Engine::Instance().GetGraphic().UnloadTexture(m_TextureId);
}

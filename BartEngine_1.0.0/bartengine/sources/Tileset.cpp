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

    const int tFirstIndex = aNode->ToElement()->IntAttribute("firstgid");

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
        int tColumns = tTileElement->IntAttribute("columns");
        int tTileWidth = tTileElement->IntAttribute("tilewidth");
        int tTileHeight = tTileElement->IntAttribute("tileheight");
        int tTileCount = tTileElement->IntAttribute("tilecount");

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
                size_t tTextureId = Engine::Instance().GetGraphic().LoadTexture(tImagePath);

                if (tTextureId > 0)
                {
                    m_TextureIds.push_back(tTextureId);
                    int tTileNumber = tFirstIndex;
                    int tY = 0;
                    int tX = 0;

                    for (int i = 0; i < tTileCount; i++, tTileNumber++)
                    {
                        tY = i / tColumns;
                        tX = i - (tY * tColumns);

                        m_SourceMap[tTileNumber] = new Tile();
                        m_SourceMap[tTileNumber]->Texture = tTextureId;
                        m_SourceMap[tTileNumber]->Bounds = {tX * tTileWidth, tY * tTileHeight, tTileWidth, tTileHeight};
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

bart::Tile* bart::Tileset::GetTile(const int aIndex)
{
    return m_SourceMap[aIndex];
}

void bart::Tileset::Clean()
{
    for (TTileMap::iterator i = m_SourceMap.begin(); i != m_SourceMap.end(); ++i)
    {
        delete i->second;
    }

    m_SourceMap.clear();

    for (size_t i = 0; i < m_TextureIds.size(); i++)
    {
        Engine::Instance().GetGraphic().UnloadTexture(m_TextureIds[i]);
    }
}

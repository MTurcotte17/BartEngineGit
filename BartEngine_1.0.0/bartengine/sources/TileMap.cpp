#include <TileMap.h>
#include <Engine.h>
#include <tinyxml2.h>
#include <TileLayer.h>
#include <ObjectLayer.h>
#include <ImageLayer.h>
#include <StringHelper.h>

using namespace tinyxml2;

void bart::TileMap::Clean()
{
    for (TLayerMap::iterator tItr = mMapInfo.begin(); tItr != mMapInfo.end(); ++tItr)
    {
        if (tItr->second != nullptr)
        {
            tItr->second->Clean();
            delete tItr->second;
        }
    }

    mMapInfo.clear();
    m_Factory.Clear();
    m_Tileset.Clean();
}

void bart::TileMap::GetMapPosition(const float aX, const float aY, int* aMapX, int* aMapY) const
{
    *aMapX = static_cast<int>(aX) / m_TileWidth;
    *aMapY = static_cast<int>(aY) / m_TileHeight;
}

void bart::TileMap::GetWorldPosition(const int aMapX, const int aMapY, float* aX, float* aY) const
{
    *aX = static_cast<float>(aMapX * m_TileWidth);
    *aY = static_cast<float>(aMapY * m_TileHeight);
}

void bart::TileMap::Register(const std::string& aType, BaseFactory* aFactory)
{
    m_Factory.Register(aType, aFactory);
}

void bart::TileMap::AddLayer(Layer* aLayer)
{
    const string tName = aLayer->GetName();
    mMapInfo[tName] = aLayer;
    m_LayerDepth.push_back(aLayer);
}

void bart::TileMap::LoadMap(XMLNode* aNode)
{
    XMLElement* tMapElement = aNode->ToElement();

    mMapWidth = tMapElement->IntAttribute("width");
    mMapHeight = tMapElement->IntAttribute("height");
    m_TileWidth = tMapElement->IntAttribute("tilewidth");
    m_TileHeight = tMapElement->IntAttribute("tileheight");

    const char* tBackgroundColor = tMapElement->Attribute("backgroundcolor");
    if (tBackgroundColor != nullptr)
    {
        const std::string tColor = tBackgroundColor;
        unsigned char tR, tG, tB, tA;

        StringHelper::GetColorComponents(tColor, &tR, &tG, &tB, &tA);
        Engine::Instance().GetGraphic().SetClearColor(tR, tG, tB);
    }
    else
    {
        Engine::Instance().GetGraphic().SetClearColor(137, 137, 137);
    }

    XMLNode* tMapChild = aNode->FirstChild();
    while (tMapChild != nullptr)
    {
        std::string tNodeValue = tMapChild->Value();
        if (tNodeValue == "tileset")
        {
            m_Tileset.Load(tMapChild, m_MapPath);
        }
        else
        {
            if (tNodeValue == "imagelayer")
            {
                ImageLayer* tLayer = new ImageLayer();
                tLayer->Load(tMapChild, m_MapPath);
                AddLayer(tLayer);
            }
            else if (tNodeValue == "layer")
            {
                TileLayer* tLayer = new TileLayer();
                tLayer->Load(tMapChild, &m_Tileset, m_TileWidth, m_TileHeight);
                AddLayer(tLayer);
            }
            else if (tNodeValue == "objectgroup")
            {
                ObjectLayer* tLayer = new ObjectLayer();
                tLayer->Load(tMapChild, &m_Factory);
                AddLayer(tLayer);
            }
            else
            {
                Engine::Instance().GetLogger().Log("Warning: (%s) is not supported yet, sorry\n", tNodeValue.c_str());
            }
        }

        tMapChild = tMapChild->NextSibling();
    }
}

bool bart::TileMap::Load(const std::string& aFilename)
{
    XMLDocument tDocument;
    if (tDocument.LoadFile(aFilename.c_str()) == XML_SUCCESS)
    {
        m_MapPath = "";
        const size_t tIdx = aFilename.find_last_of("/\\");
        if (tIdx > 0)
        {
            m_MapPath = aFilename.substr(0, tIdx + 1);
        }

        XMLNode* tNode = tDocument.FirstChild();
        while (tNode != nullptr)
        {
            std::string tNodeValue = tNode->Value();
            if (tNodeValue == "map")
            {
                LoadMap(tNode);
            }
            tNode = tNode->NextSibling();
        }

        return true;
    }

    Engine::Instance().GetLogger().Log("%s\n", tDocument.ErrorStr());
    return false;
}

void bart::TileMap::Draw()
{
    Draw({0, 0, mMapWidth * m_TileWidth, mMapHeight * m_TileHeight});
}

void bart::TileMap::Draw(const Rectangle& aViewport)
{
    for (size_t i = 0; i < m_LayerDepth.size(); i++)
    {
        m_LayerDepth[i]->Draw(aViewport);
    }
}

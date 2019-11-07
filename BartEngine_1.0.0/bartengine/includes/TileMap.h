#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <string>
#include <vector>
#include <Layer.h>
#include <map>
#include <Tileset.h>
#include <ObjectFactory.h>

namespace tinyxml2
{
    class XMLNode;
}

namespace bart
{
    class TileMap
    {
    public:
        TileMap() = default;
        ~TileMap() = default;

        void Clean();
        void GetMapPosition(float aX, float aY, int* aMapX, int* aMapY) const;
        void GetWorldPosition(int aMapX, int aMapY, float* aX, float* aY) const;

        bool Load(const std::string& aFilename);
        void Draw();
        void Draw(int aFromX, int aFromY, int aToX, int aToY);

        int GetMapWidth() const { return mMapWidth; }
        int GetMapHeight() const { return mMapHeight; }

        Layer* GetLayer(const std::string& aName) { return mMapInfo[aName]; }

        void Register(const std::string& aType, BaseFactory* aFactory);

    private:
        void LoadMap(XMLNode* aNode);
        void AddLayer(Layer* aLayer);

        typedef std::map<std::string, Layer*> TLayerMap;
        std::map<std::string, Layer*> mMapInfo;

        Tileset m_Tileset;

        int mMapWidth{0};
        int mMapHeight{0};

        std::string m_MapPath;
        std::vector<Layer*> m_LayerDepth;
        ObjectFactory m_Factory;
    };
}

#endif

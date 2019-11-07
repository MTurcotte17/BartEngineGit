#ifndef BART_TILESET_LAYER
#define BART_TILESET_LAYER

#include <Rectangle.h>
#include <map>
#include <string>

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    class Tileset
    {
    public:
        bool Load(XMLNode* aNode, const std::string& aAssetPath);
        void GetTile(int aIndex, int* aX, int* aY, int* aWidth, int* aHeight);
        void Clean();
        unsigned GetTextureId() const { return m_TextureId; }
        int GetTileWidth() const { return m_TileWidth; }
        int GetTileHeight() const { return m_TileHeight; }
        int GetTileCount() const { return m_TileCount; }
        int GetColumns() const { return m_Columns; }
        int GetImageWidth() const { return m_ImageWidth; }
        int GetImageHeight() const { return m_ImageHeight; }
        int GetFirstIndex() const { return m_FirstIndex; }

    private:
        typedef std::map<int, Rectangle*> TRectangleMap;
        TRectangleMap m_SourceMap;
        unsigned m_TextureId{0};
        std::string m_Name;
        int m_TileWidth{0};
        int m_TileHeight{0};
        int m_TileCount{0};
        int m_Columns{0};
        int m_ImageWidth{0};
        int m_ImageHeight{0};
        int m_FirstIndex{0};
    };
}
#endif

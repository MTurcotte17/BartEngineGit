#ifndef BART_TILESET_LAYER
#define BART_TILESET_LAYER

#include <Rectangle.h>
#include <map>
#include <string>
#include <vector>

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    struct Tile
    {
        size_t Texture;
        Rectangle Bounds;
    };

    class Tileset
    {
    public:
        bool Load(XMLNode* aNode, const std::string& aAssetPath);
        Tile* GetTile(int aIndex);
        void Clean();

    private:
        typedef std::map<int, Tile*> TTileMap;
        TTileMap m_SourceMap;
        std::vector<size_t> m_TextureIds;
    };
}
#endif

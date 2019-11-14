#ifndef BART_TILE_LAYER
#define BART_TILE_LAYER

#include <Layer.h>
#include <vector>
#include <Tileset.h>
#include <TiledProperty.h>

namespace bart
{
    struct TileInfo
    {
        int Index{0};
        bool HorizontalFlip{false};
        bool VerticalFlip{false};
        bool DiagonalFlip{false};
    };

    class TileLayer final : public Layer
    {
    public:
        virtual ~TileLayer() = default;
        bool Load(XMLNode* aNode, Tileset* aTileset, int aTileWidth, int aTileHeight);
        void Draw(const Rectangle& aViewport) override;
        void Clean() override;

        int GetValueAt(const int aX, const int aY) const { return mLayerData[aY][aX]->Index; }
        void SetValueAt(const int aX, const int aY, const int aValue) { mLayerData[aY][aX]->Index = aValue; }
        int IsColliding(const Rectangle& aCollider, int* aX, int* aY);
        int IsColliding(const Rectangle& aCollider);

    private:
        void SetData(const char* aData);

        typedef std::vector<std::vector<TileInfo*>> TTileMap;
        TTileMap mLayerData;
        Tileset* m_TilesetPtr{nullptr};
        int m_TileWidth{0};
        int m_TileHeight{0};
    };
}
#endif

#ifndef BART_TILE_LAYER
#define BART_TILE_LAYER

#include <Layer.h>
#include <vector>
#include <Tileset.h>
#include <TiledProperty.h>

namespace bart
{
    class TileLayer final : public Layer
    {
    public:
        virtual ~TileLayer() = default;
        bool Load(XMLNode* aNode, Tileset* aTileset);
        void Draw(int aFromX, int aFromY, int aToX, int aToY, int aWidth, int aHeight) override;
        void Clean() override;
        int GetValueAt(const int aX, const int aY) const { return mLayerData[aY][aX]; }

    private:
        void SetData(const char* aData, int aWidth);

        std::vector<std::vector<int>> mLayerData;
        Tileset* m_TilesetPtr{nullptr};
    };
}
#endif

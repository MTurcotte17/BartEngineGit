#include <TileLayer.h>
#include <Engine.h>
#include <sstream>
#include <tinyxml2.h>
#include <MathHelper.h>
#include <iostream>

const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

bool bart::TileLayer::Load(XMLNode* aNode, Tileset* aTileset, const int aTileWidth, const int aTileHeight)
{
    m_TileWidth = aTileWidth;
    m_TileHeight = aTileHeight;

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
            SetData(tData);
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

void bart::TileLayer::Draw(const Rectangle& aViewport)
{
    if (m_Visible)
    {
        const int tFromX = MathHelper::Clamp(aViewport.X / m_TileWidth, 0, m_Width);
        const int tFromY = MathHelper::Clamp(aViewport.Y / m_TileHeight, 0, m_Height);
        const int tToX = MathHelper::Clamp((aViewport.X + aViewport.W) / m_TileWidth, tFromX, m_Width);
        const int tToY = MathHelper::Clamp((aViewport.Y + aViewport.H) / m_TileHeight, tFromY, m_Height);

        if (tFromX < tToX && tFromY < tToY)
        {
            IGraphic& tGraphic = Engine::Instance().GetGraphic();

            Rectangle tDest;
            int tIndex = 0;
            int tY = 0;

            const size_t tDataSize = mLayerData.size();
            if (tDataSize > 0)
            {
                for (int y = tFromY; y < tToY; y++)
                {
                    tY = y * m_TileHeight;
                    for (int x = tFromX; x < tToX; x++)
                    {
                        tDest.X = x * m_TileWidth + static_cast<int>(m_HorizontalOffset);
                        tDest.Y = tY + static_cast<int>(m_VerticalOffset);

                        tIndex = mLayerData[y][x]->Index;
                        bool tInvalidTile = false;

                        if (tIndex > 0)
                        {
                            Tile* tTile = m_TilesetPtr->GetTile(tIndex);

                            if (tTile != nullptr)
                            {
                                tDest.W = tTile->Bounds.W;
                                tDest.H = tTile->Bounds.H;

                                if (mLayerData[y][x]->DiagonalFlip)
                                {
                                    if (mLayerData[y][x]->HorizontalFlip && mLayerData[y][x]->VerticalFlip)
                                    {
                                        tGraphic.Draw(
                                            tTile->Texture, tTile->Bounds, tDest, -90.0f, false, true, m_Alpha);
                                    }
                                    else if (mLayerData[y][x]->VerticalFlip)
                                    {
                                        tGraphic.Draw(
                                            tTile->Texture, tTile->Bounds, tDest, -90.0f, false, false, m_Alpha);
                                    }
                                    else if (mLayerData[y][x]->HorizontalFlip)
                                    {
                                        tGraphic.Draw(
                                            tTile->Texture, tTile->Bounds, tDest, 90.0f, false, false, m_Alpha);
                                    }

                                    else
                                    {
                                        tGraphic.Draw(
                                            tTile->Texture, tTile->Bounds, tDest, -90.0f, true, false, m_Alpha);
                                    }
                                }
                                else
                                {
                                    tGraphic.Draw(
                                        tTile->Texture, tTile->Bounds, tDest, 0.0f, mLayerData[y][x]->HorizontalFlip,
                                        mLayerData[y][x]->VerticalFlip, m_Alpha);
                                }
                            }
                            else
                            {
                                tInvalidTile = true;
                            }
                        }
                        else if (tIndex < 0)
                        {
                            tInvalidTile = true;
                        }

                        if (tInvalidTile)
                        {
                            // Unsupported map is a red rectangle in game:
                            tGraphic.SetColor(255, 0, 0, 255);
                            tGraphic.Fill(tDest);
                        }
                    }
                }
            }
        }
    }
}

int bart::TileLayer::IsColliding(const Rectangle& aCollider, int* aX, int* aY)
{
    const int tLeftTile = MathHelper::Clamp(aCollider.X / m_TileWidth, 0, m_Width);
    const int tRightTile = MathHelper::Clamp((aCollider.X + aCollider.W) / m_TileWidth, 0, m_Width);
    const int tTopTile = MathHelper::Clamp(aCollider.Y / m_TileHeight, 0, m_Height);
    const int tBottomTile = MathHelper::Clamp((aCollider.Y + aCollider.H) / m_TileHeight, 0, m_Height);

    for (int i = tLeftTile; i <= tRightTile; i++)
    {
        for (int j = tTopTile; j <= tBottomTile; j++)
        {
            if (i < m_Width && j < m_Height)
            {
                if (mLayerData[j][i]->Index != 0)
                {
                    *aX = i;
                    *aY = j;
                    return mLayerData[j][i]->Index;
                }
            }
        }
    }

    *aX = -1;
    *aY = -1;
    return 0;
}

int bart::TileLayer::IsColliding(const Rectangle& aCollider)
{
    int tX, tY;
    return IsColliding(aCollider, &tX, &tY);
}

void bart::TileLayer::SetData(const char* aData)
{
    std::string tCurrentToken;
    std::istringstream tInput(aData);

    int tX = 0;
    int tY = 0;

    mLayerData.push_back(std::vector<TileInfo*>(m_Width));

    while (std::getline(tInput, tCurrentToken, ','))
    {
        if (!tCurrentToken.empty())
        {
            TileInfo* tInfo = new TileInfo();

            try
            {
                tInfo->Index = std::stoul(tCurrentToken);
                tInfo->HorizontalFlip = (tInfo->Index & FLIPPED_HORIZONTALLY_FLAG);
                tInfo->VerticalFlip = (tInfo->Index & FLIPPED_VERTICALLY_FLAG);
                tInfo->DiagonalFlip = (tInfo->Index & FLIPPED_DIAGONALLY_FLAG);
                tInfo->Index &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
            }
            catch (std::exception exp)
            {
                Engine::Instance().GetLogger().Log("Corrupted map detected (layer: %s)\n", m_Name.c_str());
            }

            mLayerData[tY][tX] = tInfo;
            tX++;

            if (tX >= m_Width && tY < m_Height - 1)
            {
                tX = 0;
                tY++;

                mLayerData.push_back(std::vector<TileInfo*>(m_Width));
            }
        }
        else
        {
            Engine::Instance().GetLogger().Log("Invalid map detected (layer: %s)\n", m_Name.c_str());
        }
    }
}

void bart::TileLayer::Clean()
{
    for (TTileMap::iterator itr = mLayerData.begin(); itr != mLayerData.end(); ++itr)
    {
        for (TileInfo* tInfo : (*itr))
        {
            delete tInfo;
        }
    }

    mLayerData.clear();
    m_Properties.Clear();
}

#ifndef DEMO_MAP_H
#define DEMO_MAP_H

#include <Entity.h>
#include <TileMap.h>
#include <Camera.h>

using namespace bart;

class DemoMap final : public Entity
{
public:
    DemoMap();
    virtual ~DemoMap() = default;

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }

    void Draw() override;
    void Update(float aDeltaTime) override;
    void Start() override;
    void Destroy() override;

private:
    TileMap m_Map;
    Camera m_Camera;
};

#endif

#ifndef LEVEL_ONE_MAP_H
#define LEVEL_ONE_MAP_H

#include <Entity.h>
#include <TileMap.h>
#include <Camera.h>

using namespace bart;

class LevelOneMap final : public Entity
{
public:
	LevelOneMap();
	virtual ~LevelOneMap() = default;

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	TileMap* GetMap() { return &m_Map; }



private:
	TileMap m_Map;
	Camera m_Camera;
};
#endif

#ifndef LINE_BOX_H
#define LINE_BOX_H

#include <Entity.h>
#include <Text.h>
#include <Atlas.h>

using namespace bart;

class LineBox final : public Entity
{
public:
    virtual ~LineBox() = default;
    LineBox();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return false; }
    void Draw() override;
    void Start() override;
    void Destroy() override;

    void OnLineClear(int aCount);

private:
    Text* m_LineText{nullptr};
    Transform* m_Transform{nullptr};

    int m_LineCount{0};
};

#endif

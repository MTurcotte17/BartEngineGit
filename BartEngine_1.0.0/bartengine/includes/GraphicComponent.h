#ifndef BART_GRAPHICCOMPONENT_H
#define BART_GRAPHICCOMPONENT_H

#include <string>
#include <Engine.h>
#include <Transformable.h>

using namespace std;

namespace bart
{
    class GraphicComponent : public Transformable
    {
    public:
        virtual ~GraphicComponent() = default;
        virtual void Load(const string& aFile) = 0;
        virtual void Draw() = 0;
    };
}

#endif

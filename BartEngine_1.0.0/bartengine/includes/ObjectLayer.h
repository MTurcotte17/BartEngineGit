#ifndef BART_OBJECT_LAYER
#define BART_OBJECT_LAYER

#include <Layer.h>
#include <ObjectFactory.h>

namespace bart
{
    class ObjectLayer final : public Layer
    {
    public:
        virtual ~ObjectLayer() = default;
        bool Load(XMLNode* aNode, ObjectFactory* aFactory);
        void Clean() override;
    };
}
#endif

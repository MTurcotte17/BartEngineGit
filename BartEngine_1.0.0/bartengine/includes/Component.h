#ifndef BART_COMPONENT_H
#define BART_COMPONENT_H

namespace bart
{
    class Entity;

    class Component
    {
    public:
        virtual ~Component() = default;

        Entity* m_ParentObject{nullptr};
    };
}

#endif

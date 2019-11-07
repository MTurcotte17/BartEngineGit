#ifndef REF_COUNTED_H
#define REF_COUNTED_H

namespace bart
{
    template <class T>
    class Resource
    {
    public:
        T* Data;
        int Count;
    };
}

#endif

#ifndef BART_HASH_KEY_H
#define BART_HASH_KEY_H

#include <string>

namespace bart
{
    class HashKey
    {
    public:
        HashKey();
        explicit HashKey(unsigned int aValue);
        explicit HashKey(const char* aValue);
        HashKey(const HashKey& aValue);

        void Set(unsigned int aValue);
        bool Valid() const;
        unsigned int GetHash() const { return m_HashValue; }

        static unsigned Generate(const std::string& aValue);

    private:
        unsigned int m_HashValue{0};
    };
}

#endif

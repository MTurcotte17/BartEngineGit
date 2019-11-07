#include <HashKey.h>

#define INVALID_HASH 0x00000000
#define HASH_INIT 0x811C9DC5
#define HASH_PRIME 0x01000193

bart::HashKey::HashKey()
{
}

bart::HashKey::HashKey(const unsigned int aValue) : m_HashValue(aValue)
{
}

bart::HashKey::HashKey(const char* aValue)
{
    m_HashValue = Generate(aValue);
}

bart::HashKey::HashKey(const HashKey& aValue) : m_HashValue(aValue.m_HashValue)
{
}

void bart::HashKey::Set(const unsigned int aValue)
{
    m_HashValue = aValue;
}

bool bart::HashKey::Valid() const
{
    return (m_HashValue != INVALID_HASH);
}

unsigned int bart::HashKey::Generate(const std::string& aValue)
{
    const unsigned char* tString = reinterpret_cast<const unsigned char*>(aValue.c_str());

    if (!tString || !tString[0])
    {
        return INVALID_HASH;
    }

    unsigned int tHash = HASH_INIT;

    while (*tString)
    {
        tHash *= HASH_PRIME;
        char tChar = *tString++;

        if (tChar == '\\')
        {
            tChar = '/';
        }

        if ((tChar >= 'a') && (tChar <= 'z'))
        {
            tChar -= 'a' - 'A';
        }

        tHash ^= static_cast<unsigned int>(tChar);
    }

    return tHash;
}

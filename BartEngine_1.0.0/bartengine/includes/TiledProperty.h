#ifndef BART_TILED_PROPERTY
#define BART_TILED_PROPERTY

#include <string>
#include <map>
#include <Color.h>

namespace tinyxml2
{
    class XMLNode;
}

using namespace tinyxml2;

namespace bart
{
    enum EPropertyType { PT_BOOL, PT_COLOR, PT_FLOAT, PT_INT, PT_STRING };

    class TileProperty
    {
    public:
        virtual ~TileProperty() = default;
        EPropertyType GetType() const { return m_Type; }

    protected:
        EPropertyType m_Type{PT_STRING};
    };

    class BoolProperty final : public TileProperty
    {
    public:
        BoolProperty();
        virtual ~BoolProperty() = default;
        bool Value{false};
    };

    class ColorProperty final : public TileProperty
    {
    public:
        ColorProperty();
        virtual ~ColorProperty() = default;
        void SetFromHex(const std::string& aHexValue);
        Color Value{};
    };

    class FloatProperty final : public TileProperty
    {
    public:
        FloatProperty();
        virtual ~FloatProperty() = default;
        float Value{0.0f};
    };

    class StringProperty final : public TileProperty
    {
    public:
        StringProperty();
        virtual ~StringProperty() = default;
        std::string Value;
    };

    class IntProperty final : public TileProperty
    {
    public:
        IntProperty();
        virtual ~IntProperty() = default;
        int Value{0};
    };

    class TiledProperties
    {
    public:
        void Load(XMLNode* aNode);
        bool GetBool(const std::string& aName);
        Color GetColor(const std::string& aName);
        float GetFloat(const std::string& aName);
        std::string GetString(const std::string& aName);
        int GetInt(const std::string& aName);
        void Add(const std::string& aName, TileProperty* aProperty);
        void Clear();

    private:
        typedef std::map<std::string, TileProperty*> TPropertyMap;
        TPropertyMap m_PropertyMap;
    };
}

#endif

#include <TiledProperty.h>
#include <Color.h>
#include <tinyxml2.h>
#include <StringHelper.h>

bart::BoolProperty::BoolProperty()
{
    m_Type = PT_BOOL;
}

bart::ColorProperty::ColorProperty()
{
    m_Type = PT_COLOR;
}

void bart::ColorProperty::SetFromHex(const std::string& aHexValue)
{
    unsigned char tR, tG, tB, tA;
    StringHelper::GetColorComponents(aHexValue, &tR, &tG, &tB, &tA);
    Value.Set(tR, tG, tB, tA);
}

bart::FloatProperty::FloatProperty()
{
    m_Type = PT_FLOAT;
}

bart::StringProperty::StringProperty()
{
    m_Type = PT_STRING;
}

bart::IntProperty::IntProperty()
{
    m_Type = PT_INT;
}

void bart::TiledProperties::Load(XMLNode* aNode)
{
    XMLNode* tPropNode = aNode->FirstChild();
    while (tPropNode != nullptr)
    {
        XMLElement* tParamElement = tPropNode->ToElement();
        const char* tName = tParamElement->Attribute("name");
        const char* tType = tParamElement->Attribute("type");

        if (tName != nullptr)
        {
            std::string tKey = std::string(tName);
            std::string tTypeStr;

            if (tType == nullptr)
            {
                tTypeStr = "string";
            }
            else
            {
                tTypeStr = std::string(tType);
            }

            if (tTypeStr == "bool")
            {
                BoolProperty* tBoolProperty = new BoolProperty();
                tBoolProperty->Value = tParamElement->BoolAttribute("value");
                Add(tName, tBoolProperty);
            }
            else if (tTypeStr == "color")
            {
                const char* tColorHex = tParamElement->Attribute("value");

                if (tColorHex != nullptr)
                {
                    ColorProperty* tColorProperty = new ColorProperty();
                    tColorProperty->SetFromHex(std::string(tColorHex));
                    Add(tName, tColorProperty);
                }
            }
            else if (tTypeStr == "float")
            {
                FloatProperty* tFloatProperty = new FloatProperty();
                tFloatProperty->Value = tParamElement->FloatAttribute("value");
                Add(tName, tFloatProperty);
            }
            else if (tTypeStr == "file")
            {
                const char* tFileName = tParamElement->Attribute("value");

                if (tFileName != nullptr)
                {
                    StringProperty* tFileProperty = new StringProperty();
                    tFileProperty->Value = std::string(tFileName);
                    Add(tName, tFileProperty);
                }
            }
            else if (tTypeStr == "int")
            {
                IntProperty* tIntProperty = new IntProperty();
                tIntProperty->Value = tParamElement->BoolAttribute("value");
                Add(tName, tIntProperty);
            }
            else if (tTypeStr == "string")
            {
                const char* tString = tParamElement->Attribute("value");

                if (tString != nullptr)
                {
                    StringProperty* tStringProperty = new StringProperty();
                    tStringProperty->Value = std::string(tString);
                    Add(tName, tStringProperty);
                }
            }
        }

        tPropNode = tPropNode->NextSibling();
    }
}

bool bart::TiledProperties::TiledProperties::GetBool(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_BOOL)
        {
            return static_cast<BoolProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return "";
}

bart::Color bart::TiledProperties::TiledProperties::GetColor(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_COLOR)
        {
            return static_cast<ColorProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return Color::Black;
}

float bart::TiledProperties::TiledProperties::GetFloat(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_FLOAT)
        {
            return static_cast<FloatProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return 0.0f;
}

std::string bart::TiledProperties::TiledProperties::GetString(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_STRING)
        {
            return static_cast<StringProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return "";
}

int bart::TiledProperties::TiledProperties::GetInt(const std::string& aName)
{
    if (m_PropertyMap.count(aName) > 0)
    {
        if (m_PropertyMap[aName]->GetType() == PT_INT)
        {
            return static_cast<IntProperty*>(m_PropertyMap[aName])->Value;
        }
    }

    return 0;
}

void bart::TiledProperties::TiledProperties::Add(const std::string& aName, TileProperty* aProperty)
{
    if (m_PropertyMap.count(aName) == 0)
    {
        m_PropertyMap[aName] = aProperty;
    }
}

void bart::TiledProperties::Clear()
{
    for (TPropertyMap::iterator i = m_PropertyMap.begin(); i != m_PropertyMap.end(); ++i)
    {
        delete i->second;
    }

    m_PropertyMap.clear();
}

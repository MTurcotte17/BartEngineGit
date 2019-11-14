#include <Layer.h>
#include <tinyxml2.h>
#include <Engine.h>

void bart::Layer::ClearProperties()
{
    m_Properties.Clear();
}

bool bart::Layer::GetBoolProperty(const std::string& aName)
{
    return m_Properties.GetBool(aName);
}

bart::Color bart::Layer::GetColorProperty(const std::string& aName)
{
    return m_Properties.GetColor(aName);
}

float bart::Layer::GetFloatProperty(const std::string& aName)
{
    return m_Properties.GetFloat(aName);
}

std::string bart::Layer::GetStringProperty(const std::string& aName)
{
    return m_Properties.GetString(aName);
}

int bart::Layer::GetIntProperty(const std::string& aName)
{
    return m_Properties.GetInt(aName);
}

void bart::Layer::LoadCustomProperties(XMLNode* aNode)
{
    m_Properties.Load(aNode);
}

void bart::Layer::LoadLayerProperties(XMLNode* aNode)
{
    XMLElement* tLayerElement = aNode->ToElement();
    m_Name = tLayerElement->Attribute("name");
    m_Width = tLayerElement->IntAttribute("width");
    m_Height = tLayerElement->IntAttribute("height");
    m_Visible = tLayerElement->BoolAttribute("visible", true);
    m_HorizontalOffset = tLayerElement->FloatAttribute("offsetx", 0.0f);
    m_VerticalOffset = tLayerElement->FloatAttribute("offsety", 0.0f);

    const float tAlpha = tLayerElement->FloatAttribute("opacity", 1.0f);
    m_Alpha = static_cast<unsigned char>(255.0f * tAlpha);
}

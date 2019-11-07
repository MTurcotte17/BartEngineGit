#include <ObjectLayer.h>
#include <tinyxml2.h>

bool bart::ObjectLayer::Load(XMLNode* aNode, ObjectFactory* aFactory)
{
    ClearProperties();
    LoadLayerProperties(aNode);

    XMLNode* tNext = aNode->FirstChild();
    while (tNext != nullptr)
    {
        std::string tNextValue = tNext->Value();
        if (tNextValue == "object")
        {
            XMLElement* tObjectElement = tNext->ToElement();
            const char* tName = tObjectElement->Attribute("name");
            const char* tType = tObjectElement->Attribute("type");
            m_Visible = tObjectElement->BoolAttribute("visible", true);

            if (tName != nullptr && tType != nullptr)
            {
                const int tX = tObjectElement->IntAttribute("x");
                const int tY = tObjectElement->IntAttribute("y");
                const int tW = tObjectElement->IntAttribute("width");
                const int tH = tObjectElement->IntAttribute("height");
                const float tAngle = tObjectElement->FloatAttribute("rotation");

                TiledProperties tProps;
                XMLNode* tParamNode = tNext->FirstChild();
                if (tParamNode != nullptr)
                {
                    tProps.Load(tParamNode);
                }

                aFactory->Create(tType, tName, {tX, tY, tW, tH}, tAngle, &tProps);
                tProps.Clear();
            }
        }
        else if (tNextValue == "properties")
        {
            LoadCustomProperties(tNext);
        }

        tNext = tNext->NextSibling();
    }

    return true;
}

void bart::ObjectLayer::Clean()
{
}

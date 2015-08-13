#include "XMLParser.h"
int XMLParser::map_id = -1;
string XMLParser::parseXML(const char *key, const int index){
    const char *fileName = "config/strings.xml";
    string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename(fileName);
    tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
    XMLError errorId = pDoc->LoadFile(filePath.c_str());
    CCLOG(filePath.c_str());
    if (errorId != 0) {
        //xml¸ñÊ½´íÎó
        return "";
    }
    XMLElement *rootEle = pDoc->RootElement();
    XMLElement *keyEle = rootEle->FirstChildElement(key);

    while (keyEle)
    {
        XMLElement *surfaceChild = keyEle->FirstChildElement();
        string content;
        const XMLAttribute *attributeOfSurface = keyEle->FirstAttribute();
        int count = 0;
        while (surfaceChild) 
        {
            count++; 
            if (count == index){ 
                content = surfaceChild->GetText();
                return content;
            }
            surfaceChild = surfaceChild->NextSiblingElement(); 
        }
        keyEle = keyEle->NextSiblingElement();
    }
    return "";
}
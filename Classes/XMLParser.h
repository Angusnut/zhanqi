#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
using namespace tinyxml2;
using namespace std;
class XMLParser{
public:static string parseXML(const char *key, const int index);
};
#endif
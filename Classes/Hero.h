#ifndef _HERO_H
#define _HERO_H
#include <string>
#include "cocos2d.h"
USING_NS_CC;
using std::string;
class Hero{
public:
	string name;
	string file;
	Sprite* sprite;
    static int mapindex;
	int index;//------the index in the vector<sprite* >
	Hero(string s, string f);
	Hero();
};
#endif
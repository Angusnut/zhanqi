#ifndef NAME_ID_H  
#define NAME_ID_H  

#include "GameSprite.h"
#include <vector>
#include "cocos2d.h"


using namespace std;
USING_NS_CC;

class name_id
{
public:
	string name_list[100];
	int len;
	name_id();
	int get_id(string name);
	string get_name(int id);
};

#endif  
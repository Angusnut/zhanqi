

#include "GameSprite.h"
#include <vector>
#include "cocos2d.h"
#include "sqlite3.h"
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "name_id.h"
using namespace std;

class archive
{
public:
	sqlite3* pDB;
	int map_id;
	archive();
	void save_archive(vector<GameSprite*> herolist,int temp_map_id, int ok);
	vector<GameSprite*> open_archive(int number);
	int get_map();


};


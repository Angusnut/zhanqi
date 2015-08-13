
#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__
#include "GameSprite.h"
#include <vector>
#include "cocos2d.h"
#include "sqlite-amalgamation-3071000/sqlite3.h"
#include "name_id.h"
USING_NS_CC;
class archive
{
public:
	static sqlite3* pDB;
	static int map_id;
	archive();
	void save_archive(vector<GameSprite*> herolist,int temp_map_id, int ok,int flag);
	static vector<GameSprite*> open_archive(int number);
	static int get_map();
    static int flag_number;
    static int get_flag();

};
#endif


#include "archive.h"


using namespace std;

archive::archive()
{
    pDB = NULL; //数据库指针4
	map_id = 0;
	char *errMsg; //错误信息
	std::string sqlStr; //sql指令
	int result; //sql_exec返回指令

	result = sqlite3_open("news.db", &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("fali errCode:%d errMsg:%s", result, errMsg);
	}

	result = sqlite3_exec(pDB, "create table Tabel_1(ID integer primary key autoincrement, name int, life double, magic double, x double ,y double ,map int)", NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		CCLOG("fail code:%d errMsg:%s", result, errMsg);
	}

	sqlite3_close(pDB);
}

void archive::save_archive(vector<GameSprite*> herolist,int temp_map_id, int ok)
{
	map_id = 0;
    pDB = NULL; //数据库指针4

	char *errMsg; //错误信息
	std::string sqlStr; //sql指令
	int result; //sql_exec返回指令

	result = sqlite3_open("news.db", &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("fali errCode:%d errMsg:%s", result, errMsg);
	}
	if (ok) result = sqlite3_exec(pDB, "delete from Tabel_1;", NULL, NULL, NULL);
	result = sqlite3_exec(pDB, "create table Tabel_1(ID integer primary key autoincrement, name int, life double, magic double, x double ,y double ,map int)", NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		CCLOG("fail code:%d errMsg:%s", result, errMsg);
	}

	//insert data
	for (int i = 0; i < herolist.size(); i++)
	{
		SpriteType temp_type = herolist[i]->get_type();
		string name = temp_type.get_name();
		name_id temp_name_id= name_id();
		int name_id = temp_name_id.get_id(name);

		double life = temp_type.get_life();
		double magic = temp_type.get_magic();
		double x = temp_type.get_x();
		double y = temp_type.get_y();
		int map = temp_map_id;

		char sql_temp[512];
		sprintf_s(sql_temp, 500, "insert into Tabel_1(name,life,magic,x,y,map) values(%d,%lf,%lf,%lf,%lf,%d)", name_id, life, magic, x, y, map);

		CCLOG("%d,%lf,%lf,%lf,%lf,%d", name_id, life, magic, x, y, map);
		result = sqlite3_exec(pDB, sql_temp, NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
		{
			CCLOG("fail errCode:%d errMsg:%s", result, errMsg);
		}
	}


	sqlite3_close(pDB);
}

vector<GameSprite*> archive::open_archive(int number)
{
	pDB = NULL; //数据库指针4

	char *errMsg; //错误信息
	std::string sqlStr; //sql指令
	int result; //sql_exec返回指令

	result = sqlite3_open("news.db", &pDB);

	if (result != SQLITE_OK)
	{
		CCLOG("fali errCode:%d errMsg:%s", result, errMsg);
	}
	vector<GameSprite*> temp_Sprite;

	char **re;//查询结果
	int r, c;//行、列
	sqlite3_get_table(pDB, "select * from Tabel_1", &re, &r, &c, NULL);//4
	log("row is %d,column is %d", r, c);

	for (int i = 1+number; i <= r/2+number; i++)//5
	{
		int name = atoi(re[i*c + 1]);
		double life = atof(re[i*c + 2]);
		double magic = atof(re[i*c + 3]);
		double x = atof(re[i*c + 4]);
		double y = atof(re[i*c + 5]);
		int map = atoi(re[i*c + 6]);
		map_id = map;
		name_id temp_name_id = name_id();
		string name_string = temp_name_id.get_name(name);

		GameSprite* temp1 = GameSprite::create(name_string,1);
	  
		temp1->get_type().change_life(life);
		temp1->get_type().change_magic(magic);
		temp1->get_type().set_position(x, y);

		temp_Sprite.push_back(temp1);
	 
	}
	sqlite3_free_table(re);

	sqlite3_close(pDB);
	return temp_Sprite;
}

int archive::get_map()
{
	return map_id;
}
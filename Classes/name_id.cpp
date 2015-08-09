#include "name_id.h"
#include <stdlib.h>
#include <stdio.h>
#include "GameSprite.h"
#include <vector>
#include "cocos2d.h"

name_id::name_id()
{
	int i = 0;
		name_list[i] = "caocao";
		i++;

		name_list[i] = "xiahoudun";
		i++;


		name_list[i] = "xiahouyuan";
		i++;


		name_list[i] = "zhangliao";
		i++;

		name_list[i] = "xuchu";
		i++;


		name_list[i] = "dianwei";
		i++;


		name_list[i] = "caoren";
		i++;


		name_list[i] = "guojia";
		i++;


		name_list[i] = "zhangliao";
		i++;


		name_list[i] = "zhenbi";
		i++;


		name_list[i] = "caiwenji";
		i++;

		name_list[i] = "liubei";
		i++;


		name_list[i] = "zhangfei";
		i++;


		name_list[i] = "guanyu";
		i++;


		name_list[i] = "machao";
		i++;

		name_list[i] = "huangzhong";
		i++;


		name_list[i] = "zhaoyun";
		i++;


		name_list[i] = "weiyan";
		i++;


		name_list[i] = "zhugeliang";
		i++;


		name_list[i] = "guanyinping";
		i++;


		name_list[i] = "zhangxingcai";
		i++;




		name_list[i] = "sunquan";
		i++;


		name_list[i] = "sunce";
		i++;


		name_list[i] = "taishici";
		i++;

		name_list[i] = "zhouyu";
		i++;

		name_list[i] = "lusu";
		i++;

		name_list[i] = "luxun";
		i++;


		name_list[i] = "chengpu";
		i++;


		name_list[i] = "huanggai";
		i++;


		name_list[i] = "daqiao";
		i++;


		name_list[i] = "xiaoqiao";
		i++;


		name_list[i] = "lvbu";
		i++;


		name_list[i] = "diaochan";
		i++;


		name_list[i] = "yuanshao";
		i++;


		name_list[i] = "yuanshu";
		i++;


		name_list[i] = "liubiao";
		i++;


		name_list[i] = "liuzhang";
		i++;


		name_list[i] = "mateng";
		i++;


		name_list[i] = "zhanglu";
		i++;


		name_list[i] = "gongsunzan";
		i++;

		name_list[i] = "dongzhuo";
		i++;
		len = i;
}
int name_id::get_id(string name)
{
	for (int i = 0; i < len; i++)
	{
		if (name == name_list[i]) return i;
	}
	return -1;
}

string name_id::get_name(int id)
{
	return name_list[id];
}
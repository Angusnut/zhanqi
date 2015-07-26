#ifndef __GRID_H__
#define __GRID_H__

#include "string"
#include "iostream"
#include "GameSprite.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
//using std::String;
//using std::cout;
//using std::endl;
class Grid{
public:
	/*construct function
	*@param: 4 points, leftup, rightupm leftdown, rightdown
	*@return: no need
	*/
	Grid(Point, Point, Point, Point, string);
	/*put hero in this grid
	*@param: hero to be put
	*@return: boolean
	*/
	bool put(GameSprite*);
	/*remove hero in this grid
	*@param: NULL
	*@return: boolean
	*/
	bool remove();
	/*if there is hero in this grid
	*@param: NULL
	*@return: boolean
	*/
	bool is_empty();
	/*get the hero in this grid
	*@param: NULL
	*@return: Hero
	*/
	GameSprite* get_hero();
	/*get the terrain in this grid
	*@param: NULL
	*@return: string
	*/
	string get_terrain();
	bool set_terrain(string s);
	/*if this point is in this grid
	*@param: point to de detected
	*@return: boolean
	*/
	bool in_this_grid(Point p);
	/*get the main point of the grid
	*@param: NULL
	*@return: Point
	*/
	Point get_left_up();
	Point get_left_down();
	Point get_right_up();
	Point get_right_down();
private:
	Point lu, ru, ld, rd;
	GameSprite* hero;
	string terrain;
};

#endif
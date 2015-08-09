#ifndef __G_MAP_H__
#define __G_MAP_H__

#include "Grid.h"
#include "vector"
#include "iostream"
#include "GamePlayLayer.h"
#include "cocos2d.h"
#include "fstream"
#include "map"
USING_NS_CC;
using namespace std;

typedef Point position;

class G_Map{
public:
	/*construct function
	*@param: two int for width and length of the map, two int for size of each grid
	*@return: no need
	*/
	G_Map(int, int, int, int);
	~G_Map();

	/*is the point is in this world
	*@param: point
	*@return: boolean, true for yes, false for no
	*/
	bool is_valid(Point p);


	/*is the position valid is in this world
	*@param: position
	*@return: boolean, true for yes, false for no
	*/
	bool is_valid_pos(position p);


	/*is the world is empty now
	*@param: no
	*@return: boolean, true for yes, false for no
	*/
	bool is_empty();

	/*get the grid of a point
	*@param: position
	*@return: Point which shows the grid
	*/
	position get_pos_of_point(Point p);


	/*get the center point of a position
	*@param: position
	*@return: Point which shows the grid
	*/
	Point get_center_of_pos(position p);


	vector<vector<Grid> > get_grids();



	/*get the hero on a pos
	*@param: position
	*@return: the Hero
	*/
	GameSprite* get_hero_on_pos(position p);


	/*put a hero on one grid
	*@param: hero
	*@return: boolean, true for success, false for no
	*/
	bool put_hero_on_pos(GameSprite* h, position p);


	/*move a hero from one pos to another
	*@param: hero
	*@return: boolean, true for success, false for not a valid position or no hero on the position start
	*/
	bool move(position ps, position pe);


	/*remove a hero from a pos
	*@param: position
	*@return: boolean, true for success, false for not a valid position or no hero on the position
	*/
	bool remove(position p);


	/*get the terrain of a position
	*@param: position
	*@return: string which hints the terrain
	*/
	std::string get_terrain(position p);


	/*set the terrain of a position
	*@param: position
	*@return: boolean, true for success, false for no
	*/
	bool set_terrain(position p, string t);

	/*get the adajacent pos
	*@param: position
	*@return: position, if is not a valid pos, return (-1, -1)
	*/
	position get_right_pos(position p);
	position get_left_pos(position p);
	position get_up_pos(position p);
	position get_down_pos(position p);

	/*blend a pos for effects
	*@param: position
	*@return: bool, if success
	*/
	bool blend_pos(position p);
	bool unblend_pos(position p);
	bool a_blend_pos(position p);
	bool a_unblend_pos(position p);
	GamePlayLayer* get_layer();

	/*is the pos of the world empty
	*@param: position
	*@return: boolean, true for yes, false for no or not a valid position
	*/
	bool is_pos_empty(position p);

	/*get the pos of a hero can move
	*@param: position
	*@return: vector contains all the position
	*/
	vector<position> get_movable_pos(position p);

	/*search the pos of a rider
	*@param: position, vector to be recorded
	*@return: 
	*/
	void search_pos(position p, vector<position>& , int depth = 2, bool init = false);
	void search_a_pos(position p, vector<position>&, int depth = 2, bool init = false);

	/*get the pos of a hero can attack
	*@param: position
	*@return: vector contains all the position
	*/
	vector<position> get_attackable_pos(position p);


	/*attack
	*@param: position start and end
	*@return: 
	*/
	bool attack(position ps, position pe);
	int get_width();
	int get_height();
	//ofstream of;
private:
	vector< vector<Grid> > grids;
	int cols, rows, ghei, gwid;
	int width, height;
	int width_diff, height_diff;
	GamePlayLayer* gplayer;
	map<position, Sprite* > mapper;
	map<position, Sprite* > a_mapper;
	map<int, BloodProgress* > bloods;
	map<position, bool> is_searched;
};

#endif
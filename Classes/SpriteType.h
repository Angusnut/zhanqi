#include <cstring>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class SpriteType   //ｾｫﾁ鯊獎ﾍ  
{
private:
	//ｻｾﾊﾔ
	string name; //ﾃ錥ﾖ
	double fight_type;//ﾖﾖﾀ爛ｬ1ﾇｹ2ﾆ・ｹｭ
	double current_life;//ｵｱﾇｰﾉ愑・
	double max_life;//ﾉ愑・ﾏﾏﾞ
	double current_magic;//ｵｱﾇｰﾄｧｷｨ
	double max_magic;//ﾄｧｷｨﾉﾏﾏﾞ
	double D_attack;//ﾎ・晥･ｻ｡
	double P_attack;//ﾄｧｷｨｹ･ｻ｡
	double D_defense;//ﾎ・昞ﾀﾓ｡
	double P_defense;//ﾄｧｷｨｷﾀﾓ｡

	//ﾗ鋧ﾔ

	double initial_D_attack;//ﾎ・晥･ｻ・
	double initial_P_attack;//ﾄｧｷｨｹ･ｻ・
	double initial_D_defense;//ﾎ・昞ﾀﾓ・
	double initial_P_defense;//ﾄｧｷｨｷﾀﾓ・

	double x;//xﾗ・
	double y;//yﾗ・

public:
	SpriteType();
	SpriteType(string name_, double fight_type_, double life_, double magic_, double D_attack_, double P_attack_, double D_defense_, double P_defense_);//ｴ貊ｾﾊﾔ
	void set_position(double x_, double y_);//ｴ贐・

	//ｷｵｻﾘﾋ靹ｵ
	double get_x();
	double get_y();
	string get_name();
	double get_fight_type();
	double get_life();
	double get_magic();
	double get_D_attack();
	double get_P_attack();
	double get_D_defense();
	double get_P_defense();

	//ｸﾄｱ萢靹ｵ
	void change_value(double percent);//ｸﾝｵﾘﾐﾎｸﾄｱ・

	//ﾆ萢鈹ﾔｵ･ﾏ鋕ﾄｱ・
	void change_fight_type(double fight_type_);
	void change_life(double life_);
	void change_magic(double magic_);
	void change_D_attack(double D_attack_);
	void change_P_attack(double P_attack_);
	void change_D_defense(double D_defense_);
	void change_P_defense(double P_defense_);
};


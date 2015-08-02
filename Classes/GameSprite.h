#ifndef GAME_SPRITE_H  
#define GAME_SPRITE_H  

#include "cocos2d.h"  
#include "SpriteType.h" 
#include "SpriteState.h" 
#include <cstring>
#include "HeroAnimation.h"
#include "BloodProgress.h"
using namespace std;
USING_NS_CC;

class GameSprite : public Sprite
{
public:
	GameSprite();
	GameSprite(string name_);
	void init(Point point, SpriteType type);//ﾎｻﾖﾃ｣ｬｾｫﾁ鯊獎ﾍ
	void change_attribute(int number);//ｸﾝｵﾘﾐﾎｸﾄｱ萍ﾔ
	SpriteType& get_type();
	//ﾒﾔﾏﾂﾎｪﾍﾏｵﾄﾄ｣ｰ・ｿﾉﾉｾｼ・
	void update(float dt);          //ｴｻ・ 
    void attackAnimation(int, int);
	void deadAnimation(); 
	static GameSprite* create(string, int);
	BloodProgress* get_blood();
	//void loadAnimation(SpriteType type);
protected:
	Point moveDirection;    //ﾒﾆｶｯｷｽﾏ・ 
	Point velocity;     //ﾒﾆｶｯﾏｿ  
	SpriteType type;    //ｾｫﾁ鯊獎ﾍ   
	SpriteState state; //ｾｫﾁ鰊ｴﾌｬ
	BloodProgress* blood;
};

#endif  

/*
ｸﾝｵﾘﾐﾎｸﾄｱ萍ﾔ
number ｱ桄ｾｵﾘﾐﾎ
1ﾆｽｵﾘ｣ｺｶﾔﾆ・ﾔﾔｿ｣ｬﾆ萢軏ｻｱ茱ｻ
2ﾁﾖｵﾘ｣ｺｶﾔﾆ・ﾔｲｻｱ茱ｬﾇｹｱｿ｣ｬｹｭｱｻｱ・
3ﾉｽｵﾘ｣ｺｶﾔﾆ・ﾔｼｬｹｭｱｿ｣ｬﾇｹｱｻｱ・
4ﾋｮｵﾘ｣ｺｶﾔﾆ・ﾔｼｬﾇｹｱｬｹｭｱｻｱ・

1ﾇｹ2ﾆ・ｹｭ

*/

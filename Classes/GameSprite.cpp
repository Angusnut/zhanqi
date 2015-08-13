#include "GameSprite.h"

void GameSprite::change_attribute(int number)
{
	if (number == 1)
	{
		if (type.get_fight_type() == 2) type.change_value(1.20);
	}

	if (number == 2)
	{
		if (type.get_fight_type() == 1) type.change_value(1.20);
	}

	if (number == 3)
	{
		if (type.get_fight_type() == 3) type.change_value(1.20);
		if (type.get_fight_type() == 2) type.change_value(0.80);
	}

	if (number == 4)
	{
		if (type.get_fight_type() == 1) type.change_value(0.80);
		if (type.get_fight_type() == 2) type.change_value(0.80);
	}
}


/*
ｸﾝﾃ錥ﾖﾉ嵭ﾉｶﾔﾓｦﾎ菴ｫﾊｾﾝ
ﾊ菠・菴ｫｺｺﾓ・ｴﾒｴｿﾉ
ﾈ逎ｺﾉ嵭ﾉｲﾜｲﾙ GameSprite("caocao");
*/

GameSprite::GameSprite()
{
	//CCTexture2D *texture = Director::getInstance()->getTextureCache()->addImage("rev1.png");

	type = SpriteType("sample", 1, 0, 0, 0, 0, 0, 0);
	state = SpriteState::NONE;
    double random(double, double);
    srand(unsigned(time(0)));

}
GameSprite::GameSprite(string name_)
{
	type = SpriteType(name_, 1, 1200, 200, 0, 0, 0, 0);

	//ﾎｺｹ・
	if (name_ == "caocao")
	{
		type = SpriteType(name_, 2, 1200, 200, 82, 92, 80, 90);
	}

	if (name_ == "xiahoudun")
	{
		type = SpriteType(name_, 2, 1200, 200, 93, 70, 90, 70);
	}

	if (name_ == "xiahouyuan")
	{
		type = SpriteType(name_, 3, 1200, 200, 90, 75, 85, 73);
	}

	if (name_ == "zhangliao")
	{
		type = SpriteType(name_, 2, 1200, 200, 92, 70, 92, 76);
	}

	if (name_ == "xuzhu")
	{
		type = SpriteType(name_, 1, 1200, 200, 97, 30, 82, 20);
	}

	if (name_ == "dianwei")
	{
		type = SpriteType(name_, 1, 1200, 200, 98, 20, 88, 25);
	}

	if (name_ == "caoren")
	{
		type = SpriteType(name_, 1, 1200, 200, 82, 76, 91, 83);
	}

	if (name_ == "guojia")
	{
		type = SpriteType(name_, 3, 1200, 200, 53, 98, 37, 99);
	}

	if (name_ == "zhangliao")
	{
		type = SpriteType(name_, 2, 1200, 200, 92, 70, 92, 76);
	}

	if (name_ == "zhenbi")
	{
		type = SpriteType(name_, 3, 1200, 200, 20, 85, 35, 80);
	}

	if (name_ == "caiwenji")
	{
		type = SpriteType(name_, 3, 1200, 200, 15, 88, 55, 87);
	}
	//ﾊ・
	if (name_ == "liubei")
	{
		type = SpriteType(name_, 1, 1200, 200, 84, 78, 82, 83);
	}

	if (name_ == "zhangfei")
	{
		type = SpriteType(name_, 1, 1200, 200, 99, 25, 88, 23);
	}

	if (name_ == "guanyu")
	{
		type = SpriteType(name_, 2, 1200, 200, 98, 77, 89, 76);
	}

	if (name_ == "machao")
	{
		type = SpriteType(name_, 2, 1200, 200, 97, 60, 90, 55);
	}

	if (name_ == "huangzhong")
	{
		type = SpriteType(name_, 3, 1200, 200, 96, 66, 84, 68);
	}

	if (name_ == "zhaoyun")
	{
		type = SpriteType(name_, 2, 1200, 200, 97, 79, 100, 84);
	}

	if (name_ == "weiyan")
	{
		type = SpriteType(name_, 1, 1200, 200, 92, 63, 81, 61);
	}

	if (name_ == "zhugeliang")
	{
		type = SpriteType(name_, 3, 1200, 200, 62, 100, 65, 99);
	}

	if (name_ == "guanyinping")
	{
		type = SpriteType(name_, 2, 1200, 200, 77, 53, 75, 60);
	}

	if (name_ == "zhangxingcai")
	{
		type = SpriteType(name_, 3, 1200, 200, 76, 40, 78, 45);
	}

	//ﾎ篁・

	if (name_ == "sunquan")
	{
		type = SpriteType(name_, 1, 1200, 200, 75, 83, 88, 82);
	}

	if (name_ == "sunce")
	{
		type = SpriteType(name_, 2, 1200, 200, 97, 50, 81, 40);
	}

	if (name_ == "taishici")
	{
		type = SpriteType(name_, 2, 1200, 200, 97, 62, 85, 66);
	}

	if (name_ == "zhouyu")
	{
		type = SpriteType(name_, 3, 1200, 200, 82, 97, 76, 97);
	}

	if (name_ == "lusu")
	{
		type = SpriteType(name_, 3, 1200, 200, 52, 93, 82, 91);
	}

	if (name_ == "luxun")
	{
		type = SpriteType(name_, 3, 1200, 200, 77, 96, 87, 93);
	}

	if (name_ == "chengpu")
	{
		type = SpriteType(name_, 1, 1200, 200, 83, 77, 93, 82);
	}

	if (name_ == "huanggai")
	{
		type = SpriteType(name_, 1, 1200, 200, 87, 82, 91, 80);
	}

	if (name_ == "daqiao")
	{
		type = SpriteType(name_, 3, 1200, 200, 33, 87, 40, 85);
	}

	if (name_ == "xiaoqiao")
	{
		type = SpriteType(name_, 3, 1200, 200, 32, 86, 42, 86);
	}

	//ﾈｺﾐﾛ
	if (name_ == "lvbu")
	{
		type = SpriteType(name_, 2, 1200, 200, 100, 38, 98, 22);
	}

	if (name_ == "diaochan")
	{
		type = SpriteType(name_, 3, 1200, 200, 62, 89, 65, 87);
	}

	if (name_ == "yuanshao")
	{
		type = SpriteType(name_, 3, 1200, 200, 77, 75, 91, 74);
	}

	if (name_ == "yuanshu")
	{
		type = SpriteType(name_, 1, 1200, 200, 73, 72, 88, 79);
	}
    if (name_ == "dongzhuo")
    {
        type = SpriteType(name_, 1, 1200, 200, 73, 72, 85, 88);
    }
	if (name_ == "liubiao")
	{
		type = SpriteType(name_, 3, 1200, 200, 58, 83, 54, 81);
	}

	if (name_ == "liuzhang")
	{
		type = SpriteType(name_, 1, 1200, 200, 44, 73, 85, 82);
	}

	if (name_ == "mateng")
	{
		type = SpriteType(name_, 2, 1200, 200, 87, 53, 89, 70);
	}

	if (name_ == "zhanglu")
	{
		type = SpriteType(name_, 1, 1200, 200, 60, 84, 86, 82);
	}

	if (name_ == "gongsunzan")
	{
		type = SpriteType(name_, 2, 1200, 200, 87, 70, 88, 79);
	}


	state = SpriteState::IDLE;

}

//ｳｼｻｯ
void GameSprite::init(Point point, SpriteType type)
{
	Sprite::init();
	this->setPosition(point);
	this->type = type;
	moveDirection = Point::ZERO;
	velocity = Point::ZERO;
	//loadAnimation(type);
	this->scheduleUpdate();
}

//ｸ・ﾂ
void GameSprite::update(float dt)
{
	Point distance = velocity * dt;         //ｸﾝﾏｿﾒﾆｶｯ  
	setPosition(getPosition() + distance);
}
void GameSprite::attackAnimation(int tag, int flag){
    CCLOG("%d", flag);
    CCLOG(this->get_type().get_name().c_str());
    Animate *animation1, *animation2;
    this->stopAllActions();
    animation1 = HeroAnimation::setAnimate(flag*4 + 1, flag*4 + 4, this->get_type().get_name(), "attack");  
    if (tag == 1){
        animation2 = HeroAnimation::setAnimate(9, 12, this->get_type().get_name());
    }
    else {
        animation2 = HeroAnimation::setAnimate(5, 8, this->get_type().get_name());
    }
    CCLOG(this->get_type().get_name().c_str());
    Sequence *seq = Sequence::create(animation1, animation2, NULL);
    this->runAction(seq);
    CCLOG("random : %d", rand);
    string s = "";
    s += "voice/attack";
    s += int(random(1, 6)) + '0';
    s += ".wav";
    SimpleAudioEngine::sharedEngine()->preloadEffect(s.c_str());
    SimpleAudioEngine::sharedEngine()->playEffect(s.c_str(), false);//开始播放背景音效，false表示不循环
}
double random(double start, double end)
{
    return start + (end - start)*rand() / (RAND_MAX + 1.0);
}
void GameSprite::deadAnimation(string str){
    Animate *animation;
    this->stopAllActions();
    animation = HeroAnimation::setAnimate(1, 4, this->get_type().get_name(), "dead");
    this->runAction(animation);
    string s = "voice/die_" + str + ".wav";
    CCLOG(s.c_str());
    SimpleAudioEngine::sharedEngine()->preloadEffect(s.c_str());
    SimpleAudioEngine::sharedEngine()->playEffect(s.c_str(), false);   
}
SpriteType& GameSprite::get_type() {
	return type;
}

GameSprite* GameSprite::create(string heroName, int player){
	GameSprite *sprite = new GameSprite(heroName);
    Animate *animation;
    if (player == 1){
        animation = HeroAnimation::setAnimate(9, 12, heroName);
    }
    if (player == 2){
        animation = HeroAnimation::setAnimate(5, 8, heroName);
    }
    sprite->setScale(1.4f, 1.4f);
    sprite->runAction(animation);//播放动画
    if (sprite && sprite->initWithFile("singlePoint.png")){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
BloodProgress* GameSprite::get_blood() {
	return blood;
}
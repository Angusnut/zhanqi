#ifndef __GameStartScene_H__
#define __GameStartScene_H__
#pragma once
#include "cocos2d.h"
#include "G_Map.h"
#include "Help.h"
#include "GamePlayLayer.h" 
#include "SimpleAudioEngine.h"
#include "name_id.h"
#include "archive.h"

using namespace CocosDenshion;
class GameStartScene : public cocos2d::CCScene
{
private:
    string s;
    string mapName;
    position p1;
	int map_id;
    int AIflag;
    int tgflag;
public:
    ~GameStartScene();
    bool init();
	G_Map* MAP; 
    void saveGame(cocos2d::Ref* pSender);
    void loadGame(cocos2d::Ref* pSender);
    void help(cocos2d::Ref* pSender);
	void switchPlayer(cocos2d::Ref* pSender);
    void backToMenu(cocos2d::Ref* pSender);
    void tuoguan(cocos2d::Ref* pSender);
    void removeHint(float);
	void updateGame();
    void getArray(cocos2d::CCObject* obj);
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void gameControl(float);
	void clickedHero();
	void anotherClick();
	bool moveHero();
	void cancel();
	bool chooseAttack();
	bool attack();
	void unblendLastTouch();
	void unblendLastAPos();
	void popHeroTag(Point);
	void removeExistTag();
	bool noEmptyPos(vector<position>);
	void judgeWin();
	void gameWonByPlayer(int);
	void startAI(float);
	void initAI(int);
	void AI();
	void AIStart(position, vector<position> );
	void AIMove(position, vector<position> );
	void AIAttack(position p);
	void endAI();
	void update(float delta);
    bool loadMap();
    void addSprite(string);
	void initGlobal();
    static string restart;
	Point calVec(position, vector<position>);
	position getAIMovePos(position, vector<position> );
	position AIMoveMostEfficient(position, vector<position>);
	int attackableCount(position, int&);
	void new_addSprite();
    vector<GameSprite*> herolist_1;
	vector<GameSprite*> herolist_2;
	CREATE_FUNC(GameStartScene);
};
#endif

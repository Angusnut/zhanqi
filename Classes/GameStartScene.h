#ifndef __GameStartScene_H__
#define __GameStartScene_H__
#pragma once
#include "cocos2d.h"
#include "G_Map.h"
#include "Help.h"
#include "GamePlayLayer.h" 
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class GameStartScene : public cocos2d::CCScene
{
private:
    string s;
    string mapName;
    position p1;
public:
    GameStartScene(void);
	~GameStartScene(void);
	G_Map MAP = G_Map(18, 12, 64, 64); 
    void saveGame(cocos2d::Ref* pSender);
    void loadGame(cocos2d::Ref* pSender);
    void help(cocos2d::Ref* pSender);
    void backToMenu(cocos2d::Ref* pSender);
	bool init();
    void getArray(cocos2d::CCObject* obj);
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void clickHero(float);
    vector<GameSprite*> herolist;
	CREATE_FUNC(GameStartScene);
};
#endif

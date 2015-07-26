#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "vector"
USING_NS_CC;
class GamePlayLayer : public cocos2d::CCLayer
{
public:
	GamePlayLayer(void);
	~GamePlayLayer(void);

	bool init();
	CREATE_FUNC(GamePlayLayer);

	// 1¡¢µØÍ¼
	// ·½¿éµØÍ¼
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXTiledMap*, _tileMap, TileMap);
	// ±³¾°²ã
	CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _background, Background);
	// ÕÚÕÖ²ã
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _mask, Mask);
	// Ç°¾°²ã
	//CC_SYNTHESIZE_RETAIN(cocos2d::CCTMXLayer*, _foreground, Foreground);

	//CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _pPlayerSprite, PlayerSprite);

	void setViewPointCenter(cocos2d::Point position);

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void setPlayerPosition(cocos2d::Point position);
    static int object_id;
	std::vector<Sprite* > blends;
	CCTMXTiledMap *pTileMap;
	int width_diff, height_diff;
};
